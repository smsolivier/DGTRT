#include "BilinearIntegrator.hpp"
#include "Quadrature.hpp"
#include "ElTrans.hpp"

namespace trt 
{

void MassIntegrator::Assemble(Element& el, Matrix& elmat) {
	elmat.Resize(el.NumNodes()); 
	Quadrature quad(INTEGRATION_ORDER); 

	ElTrans& trans = el.GetTrans(); 
	double c = 1; 
	for (int n=0; n<quad.NumPoints(); n++) {
		el.CalcShape(quad.Point(n), _shape); 
		_shape.OuterProduct(_shape, _op); 
		if (_c) c = _c->Eval(trans, quad.Point(n)); 
		_op *= c * trans.Jacobian(quad.Point(n)) * quad.Weight(n); 
		elmat += _op; 
	}
}

void WeakConvectionIntegrator::Assemble(Element& el, Matrix& elmat) {
	elmat.Resize(el.NumNodes()); 
	Quadrature quad(INTEGRATION_ORDER); 

	ElTrans& trans = el.GetTrans(); 
	double c = 1; 
	for (int n=0; n<quad.NumPoints(); n++) {
		el.CalcShape(quad.Point(n), _shape); 
		el.CalcPhysGradShape(quad.Point(n), _gshape); 
		_gshape.OuterProduct(_shape, _op); 
		if (_c) c = _c->Eval(trans, quad.Point(n)); 
		_op *= -c * trans.Jacobian(quad.Point(n)) * quad.Weight(n); 
		elmat += _op; 
	}
}

} // end namespace trt 