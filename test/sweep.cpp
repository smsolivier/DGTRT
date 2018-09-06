#include "TRT.hpp"

using namespace trt; 
using namespace std; 

// #define LR

double exact(double x) {
#ifdef LR 
	return exp(-x); 
#else 
	return exp(-(1-x)); 
#endif
}

double Error(int Ne, int p) {
	double xb = 1; 

	L2Space l2(Ne, 1, p); 
	Quadrature sn_quad(8); 
	Sweeper sweeper(&l2, sn_quad); 

	ConstantCoefficient sig_s(0); 
	ConstantCoefficient sig_t(1); 

	Vector phi(l2.GetVSize()); 
	Vector psi(l2.GetVSize()); 

#ifdef LR
	sweeper.SweepLR(1, &sig_s, &sig_t, &sig_s, phi, psi); 
#else 
	sweeper.SweepRL(-1, &sig_s, &sig_t, &sig_s, phi, psi); 
#endif

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