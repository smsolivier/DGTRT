#include "TRT.hpp"

using namespace trt; 
using namespace std; 

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
	ConstantCoefficient Sig_t(1.); 
	ConstantCoefficient Sig_s(.1); 
	FunctionStateCoefficient q(QMMS); 
	FunctionStateCoefficient inflow(Inflow); 
	int Nangles = 4; 
	L2Space l2(Ne, 1, p); 
	TransportOperator transport(&l2, Nangles, &Sig_s, &Sig_t, &q, &inflow); 
	TVector psi(&l2, Nangles); 
	transport.SourceIteration(psi, 100, 1e-6); 
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

	for (int p=1; p<6; p++) {
		if (p == 4) Ne /= 5;
		double E1 = Error(Ne, p); 
		double E2 = Error(Ne*2, p); 

		double order = log(E1/E2)/log(2); 

		TEST(fabs(order - (p+1)) < 1e-1, 
			"p = " << p << ", E1 = " << E1 << ", E2 = " 
			<< E2 << ", order = " << order); 
	}
}