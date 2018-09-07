#pragma once 

#include "Element.hpp"
#include "Vector.hpp"
#include "Coefficient.hpp"

namespace trt 
{

/// abstract class for linear forms 
class LinearIntegrator {
public:
	/// default constructor 
	LinearIntegrator() { }
	/// assemble a local right hand side vector 
	virtual void Assemble(Element& el, Vector& elvec) {
		ERROR("not implemented for the parent class"); 
	}
}; 

/// domain integrator \f$ B_i q dx \f$ 
class DomainIntegrator : public LinearIntegrator {
public:
	/// constructor 
	DomainIntegrator() {_c = NULL; }
	/// construct with coefficient 
	DomainIntegrator(Coefficient* c) {_c = c; }
	/// assemble 
	void Assemble(Element& el, Vector& elvec); 
private:
	/// store the function to integrate 
	Coefficient* _c; 
	/// store shape function evaluations 
	Vector _shape; 
}; 

} // end namespace trt 