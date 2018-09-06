#pragma once 

#include "Element.hpp"
#include "Matrix.hpp"
#include "Error.hpp"
#include "Coefficient.hpp"

namespace trt 
{

/// abstract class for bilinear forms 
class BilinearIntegrator {
public:
	/// default constructor 
	BilinearIntegrator() { }
	/// assemble a local matrix 
	virtual void Assemble(Element& el, Matrix& elmat) {
		ERROR("not implemented"); 
	} 
}; 

/// integrate a mass matrix \f$ \int B_i B_j dx \f$ 
class MassIntegrator : public BilinearIntegrator {
public:
	/// default constructor 
	MassIntegrator() {_c = NULL; }
	/// constructor with coefficient 
	MassIntegrator(Coefficient* c) {_c = c; }
	/// assemble local mass matrix 
	void Assemble(Element& el, Matrix& elmat); 
private:
	/// coefficient 
	Coefficient* _c; 
	/// store shape evaluations 
	Vector _shape; 
	/// store outer product of shape functions 
	Matrix _op; 
}; 

/// integrate weak convection matrix \f$ \int -B_j \frac{dB_i}{dx} dx \f$ 
class WeakConvectionIntegrator : public BilinearIntegrator {
public:
	/// constructor 
	WeakConvectionIntegrator() {_c = NULL; }
	/// constructor with coefficient 
	WeakConvectionIntegrator(Coefficient* c) {_c = c; }
	/// assemble local matrix 
	void Assemble(Element& el, Matrix& elmat); 
private:
	/// store coefficient 
	Coefficient* _c; 
	/// store shape evals 
	Vector _shape; 
	/// store grad shape evals 
	Vector _gshape; 
	/// outer product 
	Matrix _op; 
}; 

} // end namespace trt 