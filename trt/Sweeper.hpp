#pragma once 

#include "TVector.hpp"
#include "Matrix.hpp"
#include "Vector.hpp"
#include "Quadrature.hpp"
#include "Coefficient.hpp" 

namespace trt 
{

/// performs direct inversion of transport equation 
class Sweeper {
public:
	/// constructor 
	Sweeper(FESpace* space, Quadrature& quad, Coefficient* inflow) 
		: _quad(quad), _space(space) {_inflow = inflow; }
	/// perform a sweep for all angles 
	void Solve(Coefficient* sig_s, Coefficient* sig_t, Coefficient* q, 
		TVector* dq, const Vector& phi, TVector& psi) const; 
	/// sweep from left to right (mu > 0) 
	void SweepLR(double mu, Coefficient* sig_s, Coefficient* sig_t, 
		Coefficient* q, Vector* dq, const Vector& phi, Vector& psi_n) const;
	/// sweep from right to left (mu < 0)  
	void SweepRL(double mu, Coefficient* sig_s, Coefficient* sig_t, 
		Coefficient* q, Vector* dq, const Vector& phi, Vector& psi_n) const; 

	/// sweep without the discrete source 
	void SweepLR(double mu, Coefficient* sig_s, Coefficient* sig_t, 
		Coefficient* q, const Vector& phi, Vector& psi_n) const {
		SweepLR(mu, sig_s, sig_t, q, NULL, phi, psi_n); 
	}
	/// sweep without discrete source 
	void SweepRL(double mu, Coefficient* sig_s, Coefficient* sig_t, 
		Coefficient* q, const Vector& phi, Vector& psi_n) const {
		SweepRL(mu, sig_s, sig_t, q, NULL, phi, psi_n); 
	}
private:
	/// store FE space for psi 
	FESpace* _space; 
	/// store quadrature object for angular integration 
	Quadrature _quad; 
	/// store the inflow function 
	Coefficient* _inflow; 
}; 

} // end namespace trt 