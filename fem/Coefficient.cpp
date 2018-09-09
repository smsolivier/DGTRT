#include "Coefficient.hpp"

namespace trt 
{

double GridFunctionCoefficient::Eval(ElTrans& trans, double xref) const {
	Element& el = trans.GetElement(); 
	double val = el.Interpolate(xref, *_gf);
	CHECKFINITE(val); 
	return val; 
}

} // end namespace trt 