#pragma once 

#include "Array.hpp"
#include "Matrix.hpp"
#include "Vector.hpp"

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
	/// return the derivative of *this 
	Poly1D Derivative() const {
		Array<double> c; 
		for (int i=1; i<_c.Size(); i++) {
			c.Append(i * _c[i]); 
		}
		return Poly1D(c); 
	}

	/// print the polynomial to the ofstream 
	std::ostream& Print(std::ostream& out=std::cout) const {
		out << _c[0] << " "; 
		if (_c.Size() > 1) {
			if (_c[1] >= 0) out << "+ "; 
			else out << "- "; 
			out << fabs(_c[1]) << "x" << " "; 
		}
		for (int i=2; i<_c.Size(); i++) {
			if (_c[i] >= 0) out << "+ "; 
			else out << "- "; 
			out << fabs(_c[i]) << "x^" << i << " "; 
		}
		out << std::endl; 
		return out; 
	}
private:
	/// store the polynomial coefficients 
	Array<double> _c; 
}; 

/// represent a collection of basis functions (in reference space) of an arbitrary polynomial order 
class Basis {
public:
	/// constructor 
	/** \param order polynomial order */ 
	Basis(int order); 
	/// access to ith basis function 
	const Poly1D& operator[](int i) const {return _p[i]; }
	/// access to ith derivative 
	const Poly1D& Derivative(int i) const {return _dp[i]; }
	/// return the number of basis functions 
	int Size() const {return _p.Size(); }
private:
	/// polynomial order 
	int _order;
	/// polynomials 
	Array<Poly1D> _p; 
	/// derivatives of polynomials 
	Array<Poly1D> _dp;  
}; 

} // end namespace trt 