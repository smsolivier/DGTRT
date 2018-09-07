#include "Opacity.hpp"

namespace trt 
{

double FunctionOpacity::Eval(ElTrans& trans, double xref) const {
	// interpolate temperature 
	Element& el = trans.GetElement(); 
	double T = el.Interpolate(xref, _T); 
	return _f(trans.Transform(xref), T); 
}

} // end namespace trt 