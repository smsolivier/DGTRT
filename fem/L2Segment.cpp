#include "L2Segment.hpp"

namespace trt 
{

L2Segment::L2Segment(Node left, Node right, int order) : Element(left, right, order) {
	int N = _basis.Size(); 
	double h = (right.X() - left.X())/(N-1); 
	double href = 1./(N-1); 
	for (int i=0; i<N; i++) {
		int bc; 
		if (i==0) bc = left.BC(); 
		else if (i==N-1) bc = right.BC(); 
		else bc = INTERIOR; 
		_nodes.Append(new Node(i*h + left.X(), i*href, -1, bc)); 
	}
}

void L2Segment::CalcShape(double x, Vector& shape) const {
	shape.Resize(NumNodes()); 
	for (int i=0; i<NumNodes(); i++) {
		shape[i] = _basis[i].Eval(x); 
	}
}

void L2Segment::CalcGradShape(double x, Vector& gshape) const {
	gshape.Resize(NumNodes()); 
	for (int i=0; i<NumNodes(); i++) {
		gshape[i] = _basis.Derivative(i).Eval(x); 
	}
}

} // end namespace trt 