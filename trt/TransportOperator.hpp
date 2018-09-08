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
	/// perform source iteration 
	/** \param[in,out] initial guess for psi. final solution returned in psi 
		\param[in] niter maximum number of iterations 
		\param[in] tol relative tolerance before stopping 
	*/ 
	void SourceIteration(TVector& psi, int niter, double tol) const; 
	/// compute the scalar flux 
	void ComputeScalarFlux(const TVector& psi, Vector& phi) const; 
private:
	/// store the FESpace 
	FESpace* _space;
	/// number of angles 
	int _Nangles; 
	/// abs cross section 
	Opacity* _sig_a; 
	/// scattering cross section  
	Opacity* _sig_s; 
	/// total cross section 
	Coefficient* _sig_t;
	/// source 
	Coefficient* _q; 
	/// inflow function 
	Coefficient* _inflow; 
	/// Sn angular quadrature object 
	Quadrature _quad; 
	/// sweeper to invert each source iteration 
	Sweeper _sweeper; 
}; 

} // end namespace trt 