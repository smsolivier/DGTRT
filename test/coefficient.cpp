#include "TRT.hpp"

using namespace trt; 
using namespace std; 

double F(double x) {return x*x; }

int main() {
	Node left(0, 0, -1, INTERIOR); 
	Node right(10, 1, -1, INTERIOR); 
	L2Segment l2(left, right, 1); 
	ElTrans& trans = l2.GetTrans(); 

	ConstantCoefficient constant(5.); 
	TEST(EQUAL(constant.Eval(trans, .5), 5.), "constant coefficient eval"); 

	FunctionCoefficient* func = new FunctionCoefficient(F); 
	TEST(EQUAL(func->Eval(trans, .5), 25.), "function coefficient eval"); 

	Coefficient* f = func; 
	TEST(EQUAL(f->Eval(trans, .5), 25.), "eval with transformation"); 

	L2Space space(10, 1, 1); 
	GridFunction phi(&space); 
	for (int i=0; i<phi.Size(); i++) {
		phi[i] = i; 
	}

	GridFunctionCoefficient gfc(phi); 
	TEST(EQUAL(gfc.Eval(space.GetElement(1).GetTrans(), 0), 2.), 
		"grid function coefficient"); 

	// subtract coefficient 
	Coefficient* c1 = new ConstantCoefficient(1.); 
	Coefficient* c2 = new ConstantCoefficient(2.); 
	Coefficient* subtract = new SubtractCoefficient(c1, c2); 
	TEST(EQUAL(subtract->Eval(trans, .5), -1.), "subtract coefficient"); 

	// change c1 address 
	delete c1; 
	c1 = new ConstantCoefficient(3.); 
	TEST(EQUAL(subtract->Eval(trans, .5), 1.), 
		"subtract with changed memory location"); 
	delete c2; 
	delete c1; 
	delete subtract; 
}