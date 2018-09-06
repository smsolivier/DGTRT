#include "TRT.hpp"

using namespace trt; 
using namespace std; 

double exact(double x) {
	return exp(-x); 
}

double Error(int Ne, int p) {
	double xb = 1; 

	L2Space l2(Ne, xb, p); 
	Vector psi(l2.GetVSize()); 
	WeakConvectionIntegrator wci; 
	MassIntegrator mi; 
	for (int e=0; e<Ne; e++) {
		Matrix mass, convection; 
		Element& el = l2.GetElement(e); 
		Vector rhs(el.NumNodes()); 
		mi.Assemble(el, mass); 
		wci.Assemble(el, convection); 
		Matrix A(el.NumNodes()); 
		mass.Add(convection, A); 
		if (e>0) {
			Element& pel = l2.GetElement(e-1); 
			rhs[0] += psi[pel.GetNode(pel.NumNodes()-1).GlobalID()]; 
		} else {
			rhs[0] += 1.; 
		}
		A(el.NumNodes()-1, el.NumNodes()-1) += 1; 

		Vector psi_local(el.NumNodes()); 
		A.Solve(rhs, psi_local); 
		for (int i=0; i<psi_local.Size(); i++) {
			psi[el.GetNode(i).GlobalID()] = psi_local[i]; 
		}
	}

	// compute error 
	double E = 0; 
	Quadrature quad(INTEGRATION_ORDER); 
	Vector shape; 
	for (int e=0; e<Ne; e++) {
		Element& el = l2.GetElement(e); 
		ElTrans& trans = el.GetTrans(); 
		for (int n=0; n<quad.NumPoints(); n++) {
			double x = quad.Point(n); 
			E += pow(el.Interpolate(x, psi) 
				- exact(trans.Transform(x)), 2) * trans.Jacobian(x); 
		}
	}

	ofstream out("psi.txt"); 
	for (int i=0; i<Ne; i++) {
		Element& el = l2.GetElement(i); 
		out << el.GetTrans().Transform(.5) << " " << el.Interpolate(.5, psi) << endl; 
	}
	out.close();

	return sqrt(E); 
}

int main(int argc, char* argv[]) {
	int Ne = 8; 
	if (argc > 1) Ne = atoi(argv[1]); 

	for (int p=1; p<7; p++) {
		if (p == 4) Ne /= 4;
		double E1 = Error(Ne, p); 
		double E2 = Error(Ne*2, p); 

		double order = log(E1/E2)/log(2); 

		TEST(fabs(order - (p+1)) < 1e-1, 
			"p = " << p << ", E1 = " << E1 << ", E2 = " 
			<< E2 << ", order = " << order); 
	}

}