#pragma once 

#include "Error.hpp"
#include "ElTrans.hpp"

namespace trt 
{

/// abstract representation of space and temperature dependent opacity 
class Opacity {
public:
	/// evaluate 
	/** \param xphys point in physical space 
		\param temperature 
	*/ 
	virtual double Eval(double xphys, double T) const {
		ERROR("base class is not callable. use pointer to derived class"); 
	}
}; 

/// constant opacity 
class ConstantOpacity : public Opacity {
public:
	/// constructor 
	ConstantOpacity(double c) {_c = c; }
	/// evaluate 
	double Eval(double xphys, double T) const {return _c; }
private:
	/// constant value 
	double _c; 
}; 

/// function opacity 
class FunctionOpacity : public Opacity {
public:
	/// constructor 
	FunctionOpacity(double (*f)(double x, double T)) {_f = f; }
	/// evaluate 
	double Eval(double xphys, double T) const {return _f(xphys, T); }
private:
	/// store function of space, temperature 
	double (*_f)(double x, double T); 
}; 

} // end namespace trt 