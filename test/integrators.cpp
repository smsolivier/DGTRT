#include "TRT.hpp"

using namespace trt; 
using namespace std; 

int main() {
	Node left(0, -1, INTERIOR); 
	Node right(2, -1, INTERIOR); 
	L2Segment l2(left, right, 1); 

	MassIntegrator mi; 
	Matrix elmat; 
	mi.Assemble(l2, elmat);
	TEST(EQUAL(elmat(0,0), 2./3) &&
		EQUAL(elmat(0,1), 1./3) && 
		EQUAL(elmat(1,0), 1./3) && 
		EQUAL(elmat(1,1), 2./3)
		, "mass integrator"); 

	WeakConvectionIntegrator wci; 
	wci.Assemble(l2, elmat); 
	TEST(EQUAL(elmat(0,0), .5) && 
		EQUAL(elmat(0,1), .5) && 
		EQUAL(elmat(1,0), -.5) && 
		EQUAL(elmat(1,1), -.5), 
		"weak convection integrator")
}