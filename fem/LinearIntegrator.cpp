#include "LinearIntegrator.hpp"
#include "Quadrature.hpp"

namespace trt 
{

void DomainIntegrator::Assemble(Element& el, Vector& elvec) {
	elvec.Resize(el.NumNodes()); 
	Quadrature quad(INTEGRATION_ORDER); 

	ElTrans& trans = el.GetTrans(); 
	double c = 1; 
	for (int n=0; n<quad.NumPoints(); n++) {
		el.CalcShape(quad.Point(n), _shape); 
		if (_c) c = _c->Eval(trans, quad.Point(n)); 
		_shape *= c * quad.Weight(n) * trans.Jacobian(quad.Point(n)); 
		elvec += _shape; 
	}
}

} // end namespace trt 