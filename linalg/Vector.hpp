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
	/// set all elements to a value 
	void operator=(double val); 
	/// divide all entries by val 
	void operator/=(double val); 
	/// multiply all entries by val 
	void operator*=(double val); 
	/// dot product 
	double operator*(const Vector& v) const; 
	/// outer product 
	void OuterProduct(const Vector& v, Matrix& mat) const; 
	/// return the subvector corresponding to the ordering in vdofs 
	void GetSubVector(const Array<int>& vdofs, Vector& subv) const; 
	/// add a vector to this 
	void operator+=(const Vector& v); 
	/// subtract from this 
	void Subtract(const Vector& v, Vector& diff) const; 
}; 

} // end namespace trt 