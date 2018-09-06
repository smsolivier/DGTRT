#pragma once 

#include "Error.hpp"
#include "ElTrans.hpp"

namespace trt 
{

/// abstract class for evaluating things 
class Coefficient {
public:
	/// interface for evaluating derived classes in physical space 
	virtual double Eval(double xphys) const {
		ERROR("abstract class is not callable. use a pointer to a derived class"); 
	}
	/// interface for evaluating with a transformation
	double Eval(ElTrans& trans, double xref) const {
		return Eval(trans.Transform(xref)); 
	}
}; 

/// evaluates to a constant value 
class ConstantCoefficient : public Coefficient {
public:
	/// constructor 
	ConstantCoefficient(double c) {_c = c; }
	/// evaluate 
	double Eval(double xphys) {return _c; }
private:
	/// constant value 
	double _c; 
}; 

/// evaluate a function 
class FunctionCoefficient : public Coefficient {
public:
	/// constructor 
	FunctionCoefficient(double (*f)(double x)) {_f = f; }
	/// evaluate 
	double Eval(double xphys) {return _f(xphys); }
private:
	/// store the function 
	double (*_f)(double); 
}; 

} // end namespace trt 