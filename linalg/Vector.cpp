#include "Vector.hpp"

namespace trt 
{

Vector::Vector(int N, double val) {
	Resize(N, val); 
}

Vector::Vector(const Vector& x) {
	_data.Resize(x.Size()); 
	for (int i=0; i<x.Size(); i++) {
		_data[i] = x[i]; 
	}
}

void Vector::Resize(int N, double val) {
	_data.Resize(N); 	
	for (int i=0; i<N; i++) {
		_data[i] = val; 
	}	
}

std::ostream& Vector::Print(std::ostream& out) const {
	for (int i=0; i<Size(); i++) {
		out << _data[i] << " "; 
	}
	out << std::endl; 
	return out; 
}

} // end namespace trt 