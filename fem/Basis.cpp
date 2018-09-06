#include "Basis.hpp"

namespace trt 
{

Basis::Basis(int order) {
	_order = order;  

	int N = _order + 1; // number of basis functions 
	Vector x(N); 
	double h = 1./(N-1); 
	for (int i=0; i<N; i++) {
		x[i] = i*h; 
	}

	for (int k=0; k<N; k++) {
		Matrix A(N); 
		for (int i=0; i<N; i++) {
			for (int j=0; j<N; j++) {
				A(i,j) = pow(x[i], j); 
			}
		}
		Vector b(N); 
		b[k] = 1; 

		Vector c(N); 
		A.Solve(b, c); 
		_p.Append(Poly1D(c)); 
	}

	for (int i=0; i<N; i++) {
		_dp.Append(_p[i].Derivative()); 
	}
}

} // end namespace trt 