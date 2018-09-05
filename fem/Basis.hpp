#pragma once 

#include "Array.hpp"

namespace trt 
{

/// represent a polynomial of one variable 
class Poly1D {
public:
	/// constructor 
	/** provide coefficients in ascending powers */ 
	Poly1D(Array<double> c) {_c = c; }
	/// evaluate at a point 
	double Eval(double x) const {
		double sum = _c[0]; 
		double pow = 1; 
		for (int i=1; i<_c.Size(); i++) {
			pow *= x; 
			sum += pow * _c[i]; 
		}
		return sum; 
	}
	Poly1D Derivative() const {
		Array<double> c; 
		for (int i=1; i<_c.Size(); i++) {
			c.Append(i * _c[i]); 
		}
		return c; 
	}

	std::ostream& Print(std::ostream& out=std::cout) const {
		out << _c[0] << " "; 
		if (_c.Size() > 2) {
			if (_c[1] >= 0) out << "+ "; 
			else out << "- "; 
			out << _c[1] << "x" << " "; 
		}
		for (int i=2; i<_c.Size(); i++) {
			if (_c[i] >= 0) out << "+ "; 
			else out << "- "; 
			out << _c[i] << "x^" << i << " "; 
		}
		out << std::endl; 
		return out; 
	}
private:
	Array<double> _c; 
}; 

class Basis {
public:

}; 

} // end namespace trt 