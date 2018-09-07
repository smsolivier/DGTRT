#include "Quadrature.hpp"

using namespace trt; 
using namespace std; 

double F(double x) {return x*x*x; }

void integrate(Quadrature& q) {
	double sum = 0.; 
	for (int i=0; i<q.NumPoints(); i++) {
		cout << q.Point(i) << endl; 
		sum += F(q.Point(i)) * q.Weight(i); 
	}
	TEST(EQUAL(sum, 1./4*pow(2,4)), "order = " << q.Order());	
}

int main() {

	for (int n=2; n<=20; n++) {
		Quadrature q(n, 0, 2); 
		integrate(q); 
	}

	Quadrature q(32, 0, 2); 
	integrate(q); 

	Quadrature r(64, 0, 2); 
	integrate(r); 

	Quadrature s(100, 0, 2); 
	integrate(s); 
}