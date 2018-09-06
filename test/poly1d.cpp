#include "TRT.hpp"

using namespace trt; 
using namespace std; 

int main() {
	Poly1D p({1, 2, 1});
	TEST(EQUAL(p.Eval(2), 9), "evaluate polynomial");

	Poly1D dp = p.Derivative(); 
	TEST(EQUAL(dp.Eval(2), 6.), "evaluate derivative"); 

	Basis b(2);
	bool pass = true; 
	Array<double> x({0., .5, 1.}); 
	for (int i=0; i<3; i++) {
		for (int j=0; j<3; j++) {
			if (i==j) {
				if (!EQUAL(b[i].Eval(x[j]), 1.)) pass = false; 
			} else {
				if (!EQUAL(b[i].Eval(x[j]), 0.)) pass = false; 
			}
		}
	}
	TEST(pass, "basis construction"); 
}