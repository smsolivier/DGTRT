#include "FESpace.hpp"
#include "L2Segment.hpp"

namespace trt 
{

FESpace::FESpace(int Ne, double xb, int order) {

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