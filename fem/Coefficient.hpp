#pragma once 

#include "Error.hpp"
#include "ElTrans.hpp"

namespace trt 
{

/// abstract class for evaluating things 
class Coefficient {
public:
	/// interface for evaluating derived classes in physical space 
	// virtual double Eval(double xphys) const {
		// ERROR("abstract class is not callable. use a pointer to a derived class"); 
	// }
	/// interface for evaluating with a transformation
	virtual double Eval(ElTrans& trans, double xref) const {
		ERROR("abstract class is not callable"); 
	}
	/// set the state 
	void SetState(double state) {_state = state; }
protected:
	/// store a constant parameter that can be used in evaluating 2D functions 
	double _state; 
}; 

/// evaluates to a constant value 
class ConstantCoefficient : public Coefficient {
public:
	/// constructor 
	ConstantCoefficient(double c) {_c = c; }
	/// evaluate 
	double Eval(ElTrans& trans, double xref) const {return _c; }
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
	double Eval(ElTrans& trans, double xref) const {return _f(trans.Transform(xref)); }
private:
	/// store the function 
	double (*_f)(double); 
}; 

/// evaluate a 2D function through setting the state 
class FunctionStateCoefficient : public Coefficient {
public:
	/// constructor 
	FunctionStateCoefficient(double (*f)(double, double)) {_f = f; }
	/// evaluate 
	double Eval(ElTrans& trans, double xref) const {
		return _f(trans.Transform(xref), _state); 
	}
private:
	/// store the 2D function 
	double (*_f)(double, double); 
}; 

} // end namespace trt 