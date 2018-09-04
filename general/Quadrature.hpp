#pragma once 

#include "Error.hpp"
#include "Array.hpp"

namespace trt 
{

/// arbitrary order Gauss Legendre quadrature 
class Quadrature {
public:
	/// constructor 
	/** \param p integration order 
		\param a lower limit of integration 
		\param b upper limit of integration 
	*/ 
	Quadrature(int p, double a=0, double b=1); 
	/// return the number of integration points 
	int NumPoints() const {return _x.Size(); }
	/// return the ith integration point 
	double Point(int i) const {return _x[i]; }
	/// return the ith weight 
	double Weight(int i) const {return _w[i]; }
	/// return the integration order 
	int Order() const {return _p; }
private:
	/// integration order 
	int _p; 
	/// lower limit 
	double _a; 
	/// upper limit 
	double _b; 
	/// integration points 
	Array<double> _x; 
	/// integration weights 
	Array<double> _w; 
}; 

} // end namespace trt 