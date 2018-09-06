#include "Vector.hpp"

namespace trt 
{

Vector::Vector(int N, double val) : Array<double>(N, val) {

}

void Vector::operator/=(double val) {
	for (int i=0; i<Size(); i++) {
		(*this)[i] /= val; 
	}
}

void Vector::operator*=(double val) {
	for (int i=0; i<Size(); i++) {
		(*this)[i] *= val; 
	}
}

double Vector::operator*(const Vector& v) const {
	CHECK(v.Size()==Size(), "size mismatch. v = " << v.Size()
		<< ", this = " << Size());
	double sum = 0; 
	for (int i=0; i<Size(); i++) {
		sum += v[i] * (*this)[i]; 
	} 
	return sum; 
}

void Vector::OuterProduct(const Vector& v, Matrix& mat) const {
	CHECK(v.Size()>0, "size incorrect. size = " << v.Size()); 
	CHECK(Size()>0, "size incorrect. size = " << Size()); 
	mat.Resize(Size(), v.Size()); 

	for (int i=0; i<Size(); i++) {
		for (int j=0; j<v.Size(); j++) {
			mat(i,j) = (*this)[i] * v[j]; 
		}
	}
}

void Vector::GetSubVector(const Array<int>& vdofs, Vector& subv) const {
	subv.Resize(vdofs.Size()); 
	for (int i=0; i<vdofs.Size(); i++) {
		subv[i] = (*this)[vdofs[i]]; 
	}
}

void Vector::operator+=(const Vector& v) {
	CHECK(v.Size() == Size(), "sizes must match"); 

	for (int i=0; i<Size(); i++) {
		(*this)[i] += v[i]; 
	}
}

} // end namespace trt 