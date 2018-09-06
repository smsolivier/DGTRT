extern "C" void dgesv_(int* n, int* nrhs, double* a, int* lda, int* ipiv, 
	double* b, int* ldb, int* info ); 

#include <iostream> 
#include "Error.hpp"
#include "Matrix.hpp"
#include "Vector.hpp"

using namespace std;
using namespace trt;  

int main() { 

	Matrix m(3, 3); 
	m(0,0) = 1; 
	m(0,1) = -1; 
	m(1,1) = 5; 
	m(2,1) = .2; 
	m(2,2) = 3; 

	Vector v(3, 1); 
	Vector x(3); 

	m.Solve(v, x); 
	TEST(EQUAL(x[0], 1.2), "lapack solve"); 

	Matrix a(3, 3); 
	for (int i=0; i<9; i++) {
		a.Data()[i] = i; 
	}
	Matrix sum(3,3); 
	a.Add(m, sum); 
	TEST(EQUAL(sum(0,0), 1.) &&
		EQUAL(sum(0,1), 2.) && 
		EQUAL(sum(0,2), 6.) && 
		EQUAL(sum(1,0), 1.) && 
		EQUAL(sum(1,1), 9.) && 
		EQUAL(sum(1,2), 7.) && 
		EQUAL(sum(2,0), 2.) && 
		EQUAL(sum(2,1), 5.2) && 
		EQUAL(sum(2,2), 11), 
		"matrix sum"); 
}