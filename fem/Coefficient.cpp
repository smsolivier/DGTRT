#include "Coefficient.hpp"

namespace trt 
{

double GridFunctionCoefficient::Eval(ElTrans& trans, double xref) const {
	Element& el = trans.GetElement(); 
	return el.Interpolate(xref, *_gf); 
}

} // end namespace trt 