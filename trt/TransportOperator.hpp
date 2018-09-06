#pragma once 

#include "Opacity.hpp"
#include "Coefficient.hpp"
#include "FESpace.hpp"
#include "TVector.hpp"
#include "Quadrature.hpp"

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
	TransportOperator(const FESpace* space, int Nangles, 
		Opacity* sig_s, Opacity* sig_t, Coefficient* q); 
	/// perform source iteration 
	void SourceIteration(TVector& psi, int niter, double tol) const; 
	/// compute the scalar flux 
	void ComputeScalarFlux(const TVector& psi, Vector& phi) const; 
private:
	/// store the FESpace 
	const FESpace* _space;
	/// number of angles 
	int _Nangles; 
	/// abs cross section 
	Opacity* _sig_a; 
	/// scattering cross section  
	Opacity* _sig_s; 
	/// total cross section 
	Opacity* _sig_t;
	/// source 
	Coefficient* _q; 
	/// Sn angular quadrature object 
	Quadrature _quad; 
}; 

} // end namespace trt 