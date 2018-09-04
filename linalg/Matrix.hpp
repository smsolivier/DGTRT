#pragma once 

#include "Error.hpp"
#include "Array.hpp"
#include "Vector.hpp"

namespace trt {

/// store a matrix 
class Matrix {
public:
	/// constructor. defaults to square 
	Matrix(int m, int n=-1); 
	/// copy constructor 
	Matrix(const Matrix& m); 
	/// copy assignment 
	Matrix& operator=(const Matrix& m); 

	/// return the number of rows 
	int Height() const {return _m; }
	/// return the number of columns 
	int Width() const {return _n; }
	/// const access to data 
	const double* Data() const {return &_data[0]; }
	/// direct access to the data 
	double* Data() {return &_data[0]; }
	/// index into matrix. Hides COLUMN MAJOR bs behind the scenes for stupid LAPACK
	double& operator()(int i, int j); 
	/// const index into matrix 
	double operator()(int i, int j) const; 

	/// solve the system \f$ Ax = b \f$ using lapack's dgesv (LU factor and solve) 
	void Solve(const Vector& b, Vector& x) const; 

	/// print to output 
	std::ostream& Print(std::ostream& out=std::cout) const; 	
private:
	/// store the data 
	Array<double> _data; 
	/// number of rows 
	int _m; 
	/// number of cols 
	int _n; 
}; 

} // end namespace trt 
