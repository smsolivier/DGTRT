#include "Matrix.hpp"

using namespace std; 

#define FLAT(i,j) i + j*Width()

extern "C" void dgesv_(int* n, int* nrhs, double* a, int* lda, int* ipiv, 
	double* b, int* ldb, int* info ); 

extern "C" void dgemv_(char* TRANS, int* M, int* N, double* ALPHA, double* A, 
	int* LDA, double* X, int* INCX, double* beta, double* Y, int* INCY); 

namespace trt 
{

Matrix::Matrix(int m, int n) {
	Resize(m, n); 
}

Matrix::Matrix(const Matrix& m) {
	_m = m.Height(); 
	_n = m.Width(); 
	_data.Resize(_m*_n); 
	for (int i=0; i<_m*_n; i++) {
		_data[i] = m.Data()[i]; 
	}
}

Matrix& Matrix::operator=(const Matrix& m) {
	if (_m == 0 && _n == 0) {
		_m = m.Height(); 
		_n = m.Width(); 
		_data.Resize(_m*_n); 
	}

	for (int i=0; i<_m*_n; i++) {
		_data[i] = m.Data()[i]; 
	}

	return *this; 
}

void Matrix::Resize(int m, int n) {
	CHECK(m > 0, "m = " << m); CHECK(n > 0 || n==-1, "n = " << n); 
	_m = m; 
	_n = n; 
	if (_n == -1) _n = _m; 

	_data.Resize(_m * _n); 
	for (int i=0; i<_m*_n; i++) {
		_data[i] = 0.; 
	}	
}

double& Matrix::operator()(int i, int j) {
	CHECK(i<Height(), "index out of range. i = " << i << ", height = " << Height()); 
	CHECK(j<Width(), "index out of range. j = " << j << ", width = " << Width()); 

	return _data[FLAT(i,j)]; 
}

double Matrix::operator()(int i, int j) const {
	CHECK(i<Height(), "index out of range. i = " << i << ", height = " << Height()); 
	CHECK(j<Width(), "index out of range. j = " << j << ", width = " << Width()); 

	return _data[FLAT(i,j)]; 
}

void Matrix::Solve(const Vector& b, Vector& x) const {
	for (int i=0; i<x.Size(); i++) {
		x[i] = b[i]; 
	}

	Matrix lu((*this)); 

	int N = x.Size(); 
	int one = 1; 
	int ipiv[x.Size()]; 
	int info; 
	dgesv_(&N, &one, lu.Data(), &N, &ipiv[0], &x[0], &N, &info); 

	if (info > 0) ERROR("LAPACK issue"); 
}

void Matrix::operator*=(double val) {
	for (int i=0; i<_data.Size(); i++) {
		_data[i] *= val; 
	}
}

void Matrix::operator+=(const Matrix& mat) {
	CHECK(mat.Height()==Height(), "height mismatch. mat = " 
		<< mat.Height() << ", this = " << Height()); 
	CHECK(mat.Width()==Width(), "width mismatch. mat = " 
		<< mat.Width() << ", this = " << Width()); 	

	for (int i=0; i<_data.Size(); i++) {
		_data[i] += mat.Data()[i]; 
	}
}

void Matrix::Add(const Matrix& a, Matrix& sum) const {
	CHECK((a.Height()==Height()) && (Height()==sum.Height()), "height mismatch. a = " 
		<< a.Height() << ", this = " << Height() << ", sum = " << sum.Height()); 
	CHECK((a.Width()==Width()) && (Width()==sum.Width()), "width mismatch"); 

	for (int i=0; i<_data.Size(); i++) {
		sum.Data()[i] = _data[i] + a.Data()[i]; 
	}
}

void Matrix::Mult(double alpha, const Vector& x, double beta, Vector& b) const {
	CHECK(x.Size() == Width(), "size mismatch"); 
	CHECK(b.Size() == Height(), "size mismatch"); 

	char trans = 'N'; 
	int M = Height(); 
	int N = Width(); 
	int LDA = M; 
	int INCX = 1; 
	int INCY = 1; 

	Matrix copy(*this); 
	Vector xc(x); 

	dgemv_(&trans, &M, &N, &alpha, copy.Data(), &LDA, &xc[0], &INCX, &beta, &b[0], &INCY); 

}

ostream& Matrix::Print(ostream& out) const {
	for (int i=0; i<Height(); i++) {
		for (int j=0; j<Width(); j++) {
			out << (*this)(i,j) << " "; 
		}
		out << endl; 
	}
	return out; 
}

} // end namespace trt 