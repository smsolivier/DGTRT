#include "TransportOperator.hpp"
#include "Timer.hpp"

using namespace std; 

namespace trt 
{

TransportOperator::TransportOperator(FESpace* space, int Nangles, 
	Opacity* sig_s, Opacity* sig_t, Coefficient* q, Coefficient* inflow) 
	: _quad(Nangles, -1, 1), _sweeper(space, _quad, inflow) {
	_space = space; 
	_Nangles = Nangles; 
	_sig_s = sig_s; 
	_sig_t = sig_t; 
	_sig_a = new SubtractCoefficient(_sig_t, _sig_s); 
	_q = q; 
	_inflow = inflow; 

	_cv = 1; 
	_a = 1; 
	_c = 1; 
}

int TransportOperator::SourceIteration(Coefficient* sig_t, 
	Coefficient* sig_s, Coefficient* q, TVector* dq, int niter, 
	double tol, TVector& psi, bool LOUD) const {
	int n; 
	double res = 0; 
	Vector phi(_space->GetVSize()); 
	TVector psi_old(_space, _Nangles); 
	TVector diff(_space, _Nangles); 
	for (n=0; n<niter; n++) {
		psi_old = psi; 
		ComputeScalarFlux(psi, phi);
		_sweeper.Solve(sig_s, sig_t, q, dq, phi, psi); 
		psi.Subtract(psi_old, diff); 
		res = sqrt(diff * diff); 
		if (res < tol) {
			n++; 
			break; 
		}
	}

	if (LOUD) {
		if (res < tol) {
			cout << "SI converged in " << n << " iterations" << endl; 
		} 
	}
	if (res > tol) {
		WARNING("SI not converged. final tol = " << res); 
	}
	return n; 
}

void TransportOperator::NewtonIteration(const TVector& psi_p, 
	const Vector& T_p, int n_outer, double t_outer, int n_inner, 
	double t_inner, double dt, TVector& psi, Vector& T) {

	T = T_p;
	Vector T_old(_space->GetVSize());  
	TVector dq(_space, _Nangles); 
	GridFunction scattering_gf(_space); 
	ConstantCoefficient cdt(1/(_c*dt)); 
	AddCoefficient sig_t_tilde(_sig_t, &cdt); 
	GridFunction phi(_space); 
	Vector diff(_space->GetVSize()); 
	int n; 
	double res; 
	int inner; 
	Timer timer;  
	timer.Start(); 
	for (n=0; n<n_outer; n++) {
		_sig_t->SetTemperature(T); 
		_sig_s->SetTemperature(T);

		FormSource(dt, psi_p, T_p, T, dq); 
		FormScattering(dt, T, scattering_gf); 
		GridFunctionCoefficient scattering_c(scattering_gf); 
		inner = SourceIteration(&sig_t_tilde, &scattering_c, _q, &dq, 
			n_inner, t_inner, psi); 

		ComputeScalarFlux(psi, phi); 
		T_old = T; 
		UpdateTemperature(dt, T_old, T_p, phi, T); 

		T.Subtract(T_old, diff); 
		res = sqrt(diff*diff); 
		if (res < t_outer) {
			n++; 
			break; 
		}
	}
	timer.Stop(); 

	if (res < t_outer) {
		double time = timer.GetDuration(); 
		cout << "outer = " << n << ", inner = " << inner << ", " << time/n << " s/iter" << endl; 
	} else {
		WARNING("Newton did not converge. final tol = " << res); 
	}
}

void TransportOperator::BackwardEuler(const TVector& psi_p, int niter, double tol, double dt, TVector& psi) {
	ConstantCoefficient cdt(1./(_c*dt)); 
	AddCoefficient sig_t_tilde(_sig_t, &cdt); 
	TVector dq(_space, _Nangles); 
	dq = psi_p; 
	dq *= 1./(_c*dt); 
	int inner = SourceIteration(&sig_t_tilde, _sig_s, _q, &dq, niter, tol, psi, true); 
}

void TransportOperator::ComputeScalarFlux(const TVector& psi, Vector& phi) const {
	phi = 0.; 
	Vector psi_n; 
	phi.Resize(_space->GetVSize()); 
	for (int n=0; n<_quad.NumPoints(); n++) {
		psi.GetAngle(n, psi_n); 
		psi_n *= _quad.Weight(n); 
		phi += psi_n; 
	}
}

void TransportOperator::FormSource(double dt, const TVector& psi_p, 
	const Vector& T_p, const Vector& Ts, TVector& dq) const {
	GridFunction sigma_a(_space); 
	sigma_a.Project(_sig_a);  
	for (int n=0; n<_Nangles; n++) {
		for (int i=0; i<_space->GetVSize(); i++) {
			double plank = _a*_c*pow(Ts[i], 4)/2; 
			double dplank = 2*_a*_c*pow(Ts[i], 3); 
			double alpha = 1 + 2*dt/_cv*sigma_a[i]*dplank; 
			dq(n, i) = 1./(dt*_c)*psi_p(n, i) + sigma_a[i]*(
				plank + dplank/alpha*(T_p[i] - Ts[i] - 
					2* dt/_cv*sigma_a[i]*plank)); 
		}
	}
	CHECK(dq.IsFinite(), "issue with source vector");
}

void TransportOperator::FormScattering(double dt, const Vector& Ts,
	Vector& scattering) const {
	GridFunction sigma_a(_space);  
	GridFunction sigma_s(_space); 
	sigma_a.Project(_sig_a); 
	sigma_s.Project(_sig_s);  
	for (int i=0; i<_space->GetVSize(); i++) {
		double dplank = 2*_a*_c*pow(Ts[i], 3); 
		double nu = 2*sigma_a[i] * dplank * dt; 
		nu /= _cv + 2*dt*sigma_a[i]*dplank; 
		scattering[i] = sigma_s[i] + nu*sigma_a[i]; 
	}
	CHECK(scattering.IsFinite(), "issue with scattering vector"); 
}

void TransportOperator::UpdateTemperature(double dt, const Vector& T_old, 
	const Vector& T_p, const Vector& phi, Vector& T) const {
	GridFunction sigma_a(_space); 
	sigma_a.Project(_sig_a);  
	for (int i=0; i<_space->GetVSize(); i++) {
		double plank = _a*_c*pow(T_old[i], 4)/2; 
		double dplank = 2*_a*_c*pow(T_old[i], 3); 
		double alpha = 1 + 2*dt/_cv*sigma_a[i]*dplank; 
		T[i] = T_old[i] + (T_p[i] - T_old[i] + dt/_cv*sigma_a[i]*(phi[i] - 2*plank))/alpha; 
	}
	CHECK(T.IsFinite(), "issue with temperature vector"); 
}

} // end namespace trt 