#pragma once 

#include "Opacity.hpp"
#include "Coefficient.hpp"

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
private:
	/// store the FESpace 
	const FESpace* _space;
	/// number of angles 
	int _Nangles; 
	/// abs cross section 
	Opacity* _sig_a; 
	/// scattering cross section  
	Opacity* _sig_s; 
	/// source 
	Coefficient* _q; 
}; 

} // end namespace trt 