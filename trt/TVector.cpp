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

} // end namespace trt 