#include "TRT.hpp"

using namespace trt; 
using namespace std; 

double F(double x) {return x*x; }

int main() {
	ConstantCoefficient constant(5.); 
	TEST(EQUAL(constant.Eval(10), 5.), "constant coefficient eval"); 

	FunctionCoefficient* func = new FunctionCoefficient(F); 
	TEST(EQUAL(func->Eval(5), 25.), "function coefficient eval"); 

	Coefficient* f = func; 
	Node left(0, -1, INTERIOR); 
	Node right(10, -1, INTERIOR); 
	L2Segment l2(left, right, 1); 
	ElTrans& trans = l2.GetTrans(); 
	// TEST(EQUAL(f->Eval(trans, .5), 25.), "eval with transformation"); 
}