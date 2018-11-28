#include "TRT.hpp"

using namespace trt; 
using namespace std; 

LuaReader lua; 

double Sigma_t(double x, double T) {
	return lua.ScalarFunction("Sigma_t", x, T); 
}
double Sigma_s(double x, double T) {
	return lua.ScalarFunction("Sigma_s", x, T); 
}
double Source(double x, double mu) {
	return lua.ScalarFunction("Source", x, mu); 
}
double Inflow(double x, double mu) {
	return lua.ScalarFunction("Inflow", x, mu); 
}
double Cv(double x, double T) {
	return lua.ScalarFunction("cv", x, T); 
}

int main(int argc, char* argv[]) {
	lua.Parse(argc, argv, "marshak.lua");

	int Ne = lua.Int("Ne"); 
	int Nangles = lua.Int("Nangles"); 
	int p = lua.FEOrder();  
	double xb = lua.Double("xb"); 
	double Tend = lua.Double("Tend", 1.); 
	double dt = lua.Double("dt", 1e-2); 
	int Nt = Tend/dt; 
	Writer writer; 

	FunctionOpacity sig_t(Sigma_t); 
	FunctionOpacity sig_s(Sigma_s); 
	FunctionOpacity cv(Cv); 
	FunctionStateCoefficient source(Source); 
	FunctionStateCoefficient inflow(Inflow); 

	L2Space l2(Ne, xb, p); 
	TransportOperator transport(&l2, Nangles, &sig_s, &sig_t, &source, &inflow, &cv); 
	transport.SetA(lua.Double("a", 1)); 

	TVector psi(&l2, Nangles); 
	TVector psi_p(&l2, Nangles); 
	GridFunction phi(&l2); 
	GridFunction T(&l2); 
	GridFunction T_p(&l2); 
	T = lua.Double("Tinit"); 
	writer.Add(phi, "phi");
	writer.Add(T, "T");  
	writer.SetFreq(lua.Int("freq", 1)); 

	for (int t=0; t<Nt; t++) {
		psi_p = psi; 
		T_p = T; 
		transport.NewtonIteration(psi_p, T_p, lua.Int("n_outer"), lua.Double("t_outer"), 
			lua.Int("n_inner"), lua.Double("t_inner"), dt, psi, T); 
		transport.ComputeScalarFlux(psi, phi); 

		writer.Write(); 
	}
}