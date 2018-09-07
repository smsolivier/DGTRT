#include "TransportOperator.hpp"

using namespace std; 

namespace trt 
{

TransportOperator::TransportOperator(FESpace* space, int Nangles, 
	Coefficient* sig_s, Coefficient* sig_t, Coefficient* q, Coefficient* inflow) 
	: _quad(Nangles, -1, 1), _sweeper(space, _quad, inflow) {
	_space = space; 
	_Nangles = Nangles; 
	_sig_s = sig_s; 
	_sig_t = sig_t; 
	_q = q; 
	_inflow = inflow; 
}

void TransportOperator::SourceIteration(TVector& psi, int niter, double tol) const {
	int n; 
	double res = 0; 
	Vector phi(_space->GetVSize()); 
	TVector psi_old(_space, _Nangles); 
	TVector diff(_space, _Nangles); 
	for (n=0; n<niter; n++) {
		psi_old = psi; 
		ComputeScalarFlux(psi, phi);
		_sweeper.Solve(_sig_s, _sig_t, _q, phi, psi); 
		psi.Subtract(psi_old, diff); 
		res = sqrt(diff * diff); 
		if (res < tol) {
			n++; 
			break; 
		}
	}

	if (res < tol) {
		cout << "SI converged in " << n << " iterations" << endl; 
	} else {
		WARNING("SI not converged. final tol = " << res); 
	}
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



} // end namespace trt 