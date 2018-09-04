#pragma once 

#include "Array.hpp"
#include <fstream> 

namespace trt 
{

/// class for storing a vector of doubles 
class Vector {
public:
	/// constructor 
	/** \param N size of vector
		\param val initial value for all elements 
	*/ 
	Vector(int N, double val=0); 
	/// copy constructor 
	Vector(const Vector& x); 
	/// set the size 
	void Resize(int size, double val=0); 
	/// return the size of the vector 
	int Size() const {return _data.Size(); }
	/// access the data 
	double& operator[](int index) {return _data[index]; }
	/// const access to the data 
	double operator[](int index) const {return _data[index]; }
	/// const direct access to the data 
	const double* Data() const {return &_data[0]; }
	/// direct access to the data 
	double* Data() {return &_data[0]; }

	/// print to stream 
	std::ostream& Print(std::ostream& out=std::cout) const; 
private:
	/// store the data 
	Array<double> _data; 
}; 

} // end namespace trt 