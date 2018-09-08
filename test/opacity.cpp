#include "TRT.hpp"

using namespace trt; 
using namespace std; 

double Func(double x, double T) {
	return x*T; 
}

double Sine(double x) {
	return 2; 
}

int main() {
	FunctionOpacity fo(Func);
	L2Space l2(10, 10, 1); 
	GridFunction T(&l2); 
	T.Project(Sine);  
	fo.SetTemperature(T); 

	Element& el = l2.GetElement(0); 
	cout << fo.Eval(el.GetTrans(), 1) << endl; 
}