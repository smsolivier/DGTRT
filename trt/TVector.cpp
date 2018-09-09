#include "TVector.hpp"

#define FLAT(angle, i) angle*_space->GetVSize() + i 

namespace trt 
{ 

TVector::TVector(FESpace* space, int Nangles)
	: Vector(space->GetVSize()*Nangles) {
	_space = space; 
	_Nangles = Nangles; 
}

double& TVector::operator()(int angle, int i) {
	CHECK(angle < _Nangles, "angle index out of range. angle = " << angle
		<< ", total = " << _Nangles);
		CHECK(i < _space->GetVSize(), "space index out of range, i = " 
			<< i << ", size = " << _space->GetVSize());   
	return (*this)[FLAT(angle, i)]; 
}

double TVector::operator()(int angle, int i) const {
	CHECK(angle < _Nangles, "angle index out of range. angle = " << angle
		<< ", total = " << _Nangles); 
	CHECK(i < _space->GetVSize(), "space index out of range,  i = " 
		<< i << ", size = " << _space->GetVSize()); 
	return (*this)[FLAT(angle, i)]; 
}

void TVector::GetAngle(int angle, Vector& psi_n) const {
	psi_n.Resize(_space->GetVSize()); 
	for (int i=0; i<_space->GetVSize(); i++) {
		psi_n[i] = (*this)(angle, i); 
	} 
}

void TVector::SetAngle(int angle, const Vector& psi_n) {
	for (int i=0; i<_space->GetVSize(); i++) {
		(*this)(angle, i) = psi_n[i]; 
	}
}

} // end namespace trt 