#pragma once 

#include "TVector.hpp"
#include "Matrix.hpp"
#include "Vector.hpp"

namespace trt 
{

/// performs direct inversion of transport equation 
class Sweeper {
public:
	/// constructor 
	Sweeper(const FESpace* space); 

}; 

} // end namespace trt 