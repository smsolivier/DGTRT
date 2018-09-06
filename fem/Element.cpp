#include "Element.hpp"

namespace trt 
{

Element::Element(Node left, Node right, int order) 
	: _basis(order), _left(left), _right(right) {
	_order = order; 

	_trans = new ElTrans(this); 
}

Element::~Element() {
	delete _trans; 
}

void Element::CalcPhysGradShape(double x, Vector& gshape) const {
	CalcGradShape(x, gshape); 
	gshape /= _trans->Jacobian(x); 
}

const Node& Element::GetNode(int i) const {return *_nodes[i]; }
Node& Element::GetNode(int i) {return *_nodes[i]; }

double Element::Interpolate(double x, const Vector& u) const {
	Vector shape; 
	Array<int> dofs; 
	CalcShape(x, shape); 
	GetVDofs(dofs); 
	Vector vals; 
	u.GetSubVector(dofs, vals); 
	return vals * shape; 
}

void Element::GetVDofs(Array<int>& vdofs) const {
	for (int i=0; i<NumNodes(); i++) {
		vdofs.Append(_nodes[i]->GlobalID()); 
	}
}

} // end namespace trt 