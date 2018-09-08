#include "GridFunction.hpp"
#include "Quadrature.hpp"

namespace trt 
{

double GridFunction::L2Error(Coefficient* exact) {
	double E = 0; 
	Quadrature quad(INTEGRATION_ORDER); 
	Vector shape; 
	for (int e=0; e<_space->GetNumElements(); e++) {
		Element& el = _space->GetElement(e); 
		ElTrans& trans = el.GetTrans(); 
		for (int n=0; n<quad.NumPoints(); n++) {
			double x = quad.Point(n); 
			E += pow(el.Interpolate(x, (*this)) - exact->Eval(trans, x), 2)
				* trans.Jacobian(x) * quad.Weight(n); 
		}
	}
	return sqrt(E); 
}

void GridFunction::Project(double (*f)(double)) {
	for (int n=0; n<_space->GetNumNodes(); n++) {
		(*this)[n] = f(_space->GetNode(n).X()); 
	}
}

} // end namespace trt 