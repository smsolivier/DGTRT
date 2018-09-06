#pragma once 

#include "FESpace.hpp"
#include "Array.hpp"

namespace trt 
{

/// store psi. strides in space then angle 
class TVector : public Array<double> {
public:
	/// constructor 
	TVector(const FESpace* space, int Nangles); 
	/// 2D indexing 
	double& operator()(int angle, int i); 
	/// const indexing 
	double operator()(int angle, int i) const; 
	/// get an angle 
	void GetAngle(int angle, Vector& psi_n) const; 
	/// return the FESpace 
	const FESpace* GetSpace() const {return _space; }
private:
	/// Finite element space this is build on 
	const FESpace* _space; 
	/// number of angles 
	int _Nangles; 
}; 

} // end namespace trt 