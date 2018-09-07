#pragma once 

#include "Error.hpp"
#include "ElTrans.hpp"
#include "Coefficient.hpp"

namespace trt 
{

/// abstract representation of space and temperature dependent opacity 
class Opacity : public Coefficient {
public:
	/// set the temperature Vector for evaluating temperature dependence 
	void SetTemperature(const Vector& T) {_T = T; } 
protected:
	/// store the tempearture Vector 
	Vector _T; 
}; 

/// constant opacity 
class ConstantOpacity : public Opacity {
public:
	/// constructor 
	ConstantOpacity(double c) {_c = c; }
	/// evaluate 
	double Eval(double xphys) const {return _c; }
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
	double Eval(ElTrans& trans, double xref) const; 
private:
	/// store function of space, temperature 
	double (*_f)(double x, double T); 
}; 

} // end namespace trt 