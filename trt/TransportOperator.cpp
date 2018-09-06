#include "TransportOperator.hpp"

namespace trt 
{

TransportOperator::TransportOperator(const FESpace* space, int Nangles, 
	Opacity* sig_s, Opacity* sig_t, Coefficient* q) : _quad(Nangles) {
	_space = space; 
	_Nangles = Nangles; 
	_sig_s = sig_s; 
	_sig_t = sig_t; 
	_q = q; 
}

void TransportOperator::SourceIteration(TVector& psi, int niter, double tol) const {
	int n; 
	double res = 0; 
	for (n=0; n<niter; n++) {
		
	}
}

void TransportOperator::ComputeScalarFlux(const TVector& psi, Vector& phi) const {
	phi.Resize(_space->GetVSize()); 
	phi = 0.; 
	Vector psi_n; 
	for (int n=0; n<_quad.NumPoints(); n++) {
		psi.GetAngle(n, psi_n); 
		psi_n *= _quad.Weight(n); 
		phi += psi_n; 
	}
}



} // end namespace trt 