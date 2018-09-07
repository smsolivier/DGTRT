#pragma once 

#include "FESpace.hpp"
#include "Vector.hpp"

namespace trt 
{

/// store psi. strides in space then angle 
class TVector : public Vector {
public:
	/// constructor 
	TVector(FESpace* space, int Nangles); 
	/// 2D indexing 
	double& operator()(int angle, int i); 
	/// const indexing 
	double operator()(int angle, int i) const; 
	/// set all values 
	void operator=(double val) {Vector::operator=(val); }
	/// get an angle 
	void GetAngle(int angle, Vector& psi_n) const; 
	/// set an angle 
	void SetAngle(int angle, const Vector& psi_n); 
	/// return the FESpace 
	FESpace* GetSpace() const {return _space; }
private:
	/// Finite element space this is build on 
	FESpace* _space; 
	/// number of angles 
	int _Nangles; 
}; 

} // end namespace trt 