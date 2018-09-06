#pragma once 

#include "Array.hpp"
#include "Matrix.hpp"
#include <fstream> 

namespace trt 
{

class Matrix; 

/// class for storing a vector of doubles 
class Vector : public Array<double> {
public:
	/// constructor 
	/** \param N size of vector
		\param val initial value for all elements 
	*/ 
	Vector(int N, double val=0); 
	/// default constructor 
	Vector() { }
	/// divide all entries by val 
	void operator/=(double val); 
	/// dot product 
	double operator*(const Vector& v) const; 
	/// outer product 
	void OuterProduct(const Vector& v, Matrix& mat) const; 
	/// return the subvector corresponding to the ordering in vdofs 
	void GetSubVector(const Array<int>& vdofs, Vector& subv) const; 

}; 

} // end namespace trt 