#include "TRT.hpp"

using namespace trt; 
using namespace std; 

int main() {
	Poly1D p({1, 2, 1});
	TEST(EQUAL(p.Eval(2), 9), "evaluate polynomial");

	Poly1D dp = p.Derivative(); 
	dp.Print(); 
}