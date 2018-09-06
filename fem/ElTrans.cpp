#include "ElTrans.hpp"

#include "Vector.hpp"

namespace trt 
{

ElTrans::ElTrans(Element* el) {
	_el = el; 
}

double ElTrans::Jacobian(double x) {
	double sum = 0; 
	Vector gshape; 
	_el->CalcGradShape(x, gshape); 
	for (int i=0; i<_el->NumNodes(); i++) {
		sum += gshape[i] * _el->GetNode(i).X(); 
	}
	return sum; 
}

double ElTrans::Transform(double x) {
	double sum = 0; 
	Vector shape; 
	_el->CalcShape(x, shape); 
	for (int i=0; i<_el->NumNodes(); i++) {
		sum += shape[i] * _el->GetNode(i).X(); 
	}
	return sum; 
}

} // end namespace trt 