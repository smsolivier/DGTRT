#include "TVector.hpp"

#define FLAT(angle, i) angle*_space->GetVSize() + i 

namespace trt 
{ 

TVector::TVector(const FESpace* space, int Nangles)
	: Array<double>(space->GetVSize()*Nangles) {
	_space = space; 
	_Nangles = Nangles; 
}

double& TVector::operator()(int angle, int i) {
	return (*this)[FLAT(angle, i)]; 
}

double TVector::operator()(int angle, int i) const {
	return (*this)[FLAT(angle, i)]; 
}

void TVector::GetAngle(int angle, Vector& psi_n) const {
	psi_n.Resize(_space->GetVSize()); 
	for (int i=0; i<_space->GetVSize(); i++) {
		psi_n[i] = (*this)(angle, i); 
	} 
}

} // end namespace trt 