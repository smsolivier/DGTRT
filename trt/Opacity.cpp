#include "Opacity.hpp"

namespace trt 
{

double FunctionOpacity::Eval(ElTrans& trans, double xref) const {
	if (_f) {
		CHECK(_T.Size()>0, "T not initialized. size = " << _T.Size()); 
		// interpolate temperature 
		Element& el = trans.GetElement(); 
		double T = el.Interpolate(xref, _T); 
		if (T <= 0) ERROR("negative temperature found. T = " << T); 
		return _f(trans.Transform(xref), T); 		
	} else {
		return _g(trans.Transform(xref)); 
	}
}

} // end namespace trt 