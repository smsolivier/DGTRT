#pragma once 

#include "Error.hpp"
#include "ElTrans.hpp"
#include "GridFunction.hpp"

namespace trt 
{

class GridFunction; 

/// abstract class for evaluating things 
class Coefficient {
public:
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
	double Eval(ElTrans& trans, double xref) const {
		double val = _f(trans.Transform(xref)); 
		CHECKFINITE(val); 
		return val; 
	}
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
		double val = _f(trans.Transform(xref), _state); 
		CHECKFINITE(val); 
		return val; 
	}
private:
	/// store the 2D function 
	double (*_f)(double, double); 
}; 

/// evaluate a GridFunction as a coefficient 
class GridFunctionCoefficient : public Coefficient {
public:
	/// constructor 
	GridFunctionCoefficient(GridFunction& gf) { _gf = &gf; }
	/// evaluate the grid function coefficient 
	double Eval(ElTrans& trans, double xref) const; 
private:
	/// store the grid function
	GridFunction* _gf; 
}; 

/// subtract a coefficient from another one 
class SubtractCoefficient : public Coefficient {
public:
	/// constructor. evaluates c1 - c2 
	SubtractCoefficient(Coefficient* c1, Coefficient* c2) {
		_c1 = c1; 
		_c2 = c2; 
	}
	/// evaluate the two coefficients and subtract 
	double Eval(ElTrans& trans, double xref) const {
		double val = _c1->Eval(trans, xref) - _c2->Eval(trans, xref);
		CHECKFINITE(val); 
		return val; 
	}
private:
	Coefficient* _c1; 
	Coefficient* _c2; 
}; 

/// add two coefficients together 
class AddCoefficient : public Coefficient {
public:
	/// constructor. adds c1 and c2 
	AddCoefficient(Coefficient* c1, Coefficient* c2) {
		_c1 = c1; 
		_c2 = c2; 
	}
	/// evaluate 
	double Eval(ElTrans& trans, double xref) const {
		double val = _c1->Eval(trans, xref) + _c2->Eval(trans, xref);
		CHECKFINITE(val); 
		return val; 
	}
private:
	Coefficient* _c1; 
	Coefficient* _c2; 
}; 

} // end namespace trt 