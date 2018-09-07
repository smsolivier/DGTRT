#include "FESpace.hpp"
#include "L2Segment.hpp"
#include "Quadrature.hpp"

namespace trt 
{

FESpace::FESpace(int Ne, double xb, int order) {

}

double FESpace::L2Error(Vector& u, Coefficient* exact) {
	double E = 0; 
	Quadrature quad(INTEGRATION_ORDER); 
	Vector shape; 
	for (int e=0; e<GetNumElements(); e++) {
		Element& el = GetElement(e); 
		ElTrans& trans = el.GetTrans(); 
		for (int n=0; n<quad.NumPoints(); n++) {
			double x = quad.Point(n); 
			E += pow(el.Interpolate(x, u) - exact->Eval(trans.Transform(x)), 2)
				* trans.Jacobian(x) * quad.Weight(n); 
		}
	}
	return sqrt(E); 
}

L2Space::L2Space(int Ne, double xb, int order) : FESpace(Ne, xb, order) {
	double h = xb/Ne; 
	for (int i=0; i<Ne; i++) {
		int lbc; 
		int rbc; 
		if (i==0) {lbc = DIRICHLET; rbc = INTERIOR; }
		else if (i==Ne-1) {rbc = DIRICHLET; lbc = INTERIOR; }
		else {lbc = rbc = INTERIOR; }
		Node left(i*h, -1, lbc); 
		Node right((i+1)*h, -1, rbc); 
		_els.Append(new L2Segment(left, right, order)); 
	}

	// assign ids to nodes and copy pointers over 
	int count = 0; 
	for (int e=0; e<Ne; e++) {
		for (int i=0; i<_els[e]->NumNodes(); i++) {
			_els[e]->GetNode(i).SetGlobalID(count++); 	
			_nodes.Append(&_els[e]->GetNode(i)); 
		}
	}
}

} // end namespace trt 