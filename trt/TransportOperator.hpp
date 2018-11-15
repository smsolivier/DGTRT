#pragma once 

#include "Coefficient.hpp"
#include "FESpace.hpp"
#include "TVector.hpp"
#include "Quadrature.hpp"
#include "Sweeper.hpp"
#include "Opacity.hpp"

namespace trt 
{

/// driver for transport solver 
class TransportOperator {
public:
	/// constructor 
	/** \param finite element space for transport 
		\param Nangles number of angles (S_?) 
		\param sig_s scattering cross section 
		\param sig_t total cross section 
		\param q source 
	*/ 
	TransportOperator(FESpace* space, int Nangles, 
		Opacity* sig_s, Opacity* sig_t, Coefficient* q, Coefficient* inflow); 
	/// source iteration but with opacities from constructor 
	void SourceIteration(TVector& psi, int niter, double tol) const {
		SourceIteration(_sig_t, _sig_s, _q, NULL, niter, tol, psi); 
	}
	/// perform source iteration with a discrete source 
	/** \param[in] sig_t total interaction (term that multiplies psi on LHS) 
		\param[in] sig_s scattering (phi term that is lagged) 
		\param[in] q fixed source on rhs 
		\param[in] dq discrete source term. can be null 
		\param[in] niter maximum number of iterations 
		\param[in] tol relative tolerance before stopping 
		\param[in,out] initial guess for psi. final solution returned in psi 
		\param[in] LOUD print iteration info to terminal 
	*/ 
	int SourceIteration(Coefficient* sig_t, Coefficient* sig_s, 
		Coefficient* q, TVector* dq, int niter, double tol, 
		TVector& psi, bool LOUD=false) const; 
	/// perform one newton temperature iteration 
	/** \param[in] psi_p angular flux from previous iteration 
		\param[in] T_p temperature from previous iteration 
		\param[in] n_outer max number of newton iterations 
		\param[in] t_outer newton iteration tolerance 
		\param[in] n_inner max number of source iterations
		\param[in] t_inner source iteration tolerance 
		\param[in] dt time step size 
		\param[out] psi converged angular flux 
		\param[out] T converged temperature 
	*/ 
	void NewtonIteration(const TVector& psi_p, const Vector& T_p, 
		int n_outer, double t_outer, int n_inner, double t_inner, double dt,
		TVector& psi, Vector& T); 
	/// perform one time step 
	/** \param[in] psi_p angular flux from previous time step 
		\param[in] niter maximum number of source iterations to try 
		\param[in] tol iterative tolerance to stop at 
		\param[in] dt time step size 
		\param[out] psi angular flux at next time step 
	*/ 
	void BackwardEuler(const TVector& psi_p, int niter, double tol, double dt, TVector& psi); 
	/// compute the scalar flux 
	void ComputeScalarFlux(const TVector& psi, Vector& phi) const; 
	/// set the radiation temperature thing (a) 
	void SetA(double a) {_a = a; }
private:
	/// form the source term for backward euler Newton Iteration 
	void FormSource(double dt, const TVector& psi_p, const Vector& T_p, 
		const Vector& Ts, TVector& dq) const; 
	/// form the scattering coefficient for backward euler Newton iteration 
	void FormScattering(double dt, const Vector& Ts, 
		Vector& scattering) const; 
	/// update the temperature vector 
	void UpdateTemperature(double dt, const Vector& T_old, 
		const Vector& T_p, const Vector& phi, Vector& T) const; 

	/// store the FESpace 
	FESpace* _space;
	/// number of angles 
	int _Nangles; 
	/// abs cross section 
	Coefficient* _sig_a; 
	/// scattering cross section  
	Opacity* _sig_s; 
	/// total cross section 
	Opacity* _sig_t;
	/// source function 
	Coefficient* _q; 
	/// inflow function 
	Coefficient* _inflow; 
	/// heat capacity 
	double _cv; 
	/// speed of light 
	double _c; 
	/// radiation temperature thing 
	double _a; 
	/// Sn angular quadrature object 
	Quadrature _quad; 
	/// sweeper to invert each source iteration 
	Sweeper _sweeper; 
}; 

} // end namespace trt 