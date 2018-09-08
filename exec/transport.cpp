#include "TRT.hpp"

using namespace trt; 
using namespace std; 

LuaReader lua; 

double Sigma_t(double x) {
	return lua.ScalarFunction("Sigma_t", x); 
}
double Sigma_s(double x) {
	return lua.ScalarFunction("Sigma_s", x); 
}
double Source(double x, double mu) {
	return lua.ScalarFunction("Source", x, mu); 
}
double Inflow(double x, double mu) {
	return lua.ScalarFunction("Inflow", x, mu); 
}

int main(int argc, char* argv[]) {
	lua.Parse(argc, argv, "transport.lua");

	int Ne = lua.Int("Ne"); 
	int Nangles = lua.Int("Nangles"); 
	int p = lua.FEOrder();  
	double xb = lua.Double("xb"); 

	FunctionOpacity sig_t(Sigma_t); 
	FunctionOpacity sig_s(Sigma_s); 
	FunctionStateCoefficient source(Source); 
	FunctionStateCoefficient inflow(Inflow); 

	L2Space l2(Ne, xb, p); 
	TransportOperator transport(&l2, Nangles, &sig_s, &sig_t, &source, &inflow); 

	TVector psi(&l2, Nangles); 
	transport.SourceIteration(psi, lua.Int("niter", 25), lua.Double("tol", 1e-6));
	GridFunction phi(&l2); 
	transport.ComputeScalarFlux(psi, phi); 

	Writer writer; 
	writer.Add(phi, "phi"); 
	writer.Write(); 
}