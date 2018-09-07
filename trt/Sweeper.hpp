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
		const Vector& phi, TVector& psi) const; 
	/// sweep from left to right (mu > 0) 
	void SweepLR(double mu, Coefficient* sig_s, 
		Coefficient* sig_t, Coefficient* q, const Vector& phi, Vector& psi_n) const; 
	void SweepRL(double mu, Coefficient* sig_s, 
		Coefficient* sig_t, Coefficient* q, const Vector& phi, Vector& psi_n) const; 
private:
	/// store FE space for psi 
	FESpace* _space; 
	/// store quadrature object for angular integration 
	Quadrature _quad; 
	/// store the inflow function 
	Coefficient* _inflow; 
}; 

} // end namespace trt 