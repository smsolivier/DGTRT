#include "TRT.hpp"

using namespace trt; 
using namespace std; 

#define DQ 

double sig_a; 
double sig_t; 
double sig_s; 

double QMMS(double x, double mu) {
	return .5*(mu*M_PI*cos(M_PI*x) + sig_a*sin(M_PI*x)); 
}

double Inflow(double x, double mu) {
	return 0.; 
}

double Exact(double x) {return sin(M_PI*x); }

double Error(int Ne, int p) {
	ConstantOpacity Sig_t(1.); 
	ConstantOpacity Sig_s(.1); 
#ifndef DQ 
	FunctionStateCoefficient q(QMMS); 
#else 
	FunctionStateCoefficient q(Inflow);
#endif
	FunctionStateCoefficient inflow(Inflow); 
	int Nangles = 4; 
	L2Space l2(Ne, 1, p); 
#ifdef DQ
	TVector* dq = new TVector(&l2, Nangles); 
	Quadrature quad(Nangles, -1, 1); 
	for (int n=0; n<Nangles; n++) {
		double mu = quad.Point(n); 
		for (int i=0; i<l2.GetNumNodes(); i++) {
			const Node& node = l2.GetNode(i); 
			(*dq)(n, node.GlobalID()) = QMMS(node.X(), mu); 
		}
	}
#endif
	TransportOperator transport(&l2, Nangles, &Sig_s, &Sig_t, &q, &inflow); 
	TVector psi(&l2, Nangles); 
#ifndef DQ 
	transport.SourceIteration(psi, 100, 1e-12); 
#else 
	transport.SourceIteration(&Sig_t, &Sig_s, &q, dq, 100, 1e-12, psi); 
#endif
	GridFunction phi(&l2); 
	transport.ComputeScalarFlux(psi, phi); 

	ofstream out("phi.txt"); 
	for (int e=0; e<l2.GetNumElements(); e++) {
		Element& el = l2.GetElement(e); 
		double u = el.Interpolate(.5, phi); 
		double xphys = el.GetTrans().Transform(.5); 
		out << xphys << " " << u << endl; 
	}
	out.close(); 

	FunctionCoefficient exact(Exact); 
	return phi.L2Error(&exact); 
}

int main() {
	sig_t = 1; 
	sig_s = .1; 
	sig_a = sig_t - sig_s; 	

	int Ne = 10; 

	for (int p=1; p<7; p++) {
		if (p == 4) Ne /= 5;
		double E1 = Error(Ne, p); 
		double E2 = Error(Ne*2, p); 

		double order = log(E1/E2)/log(2); 

		TEST(fabs(order - (p+1)) < 1e-1, 
			"p = " << p << ", E1 = " << E1 << ", E2 = " 
			<< E2 << ", order = " << order); 
	}
}