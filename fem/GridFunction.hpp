#pragma once 

#include "FESpace.hpp"
#include "Vector.hpp"
#include "Coefficient.hpp"

namespace trt 
{

/// represent a solution vector on an FESpace 
class GridFunction : public Vector {
public:
	/// constructor 
	GridFunction(FESpace* space) : Vector(space->GetVSize()) {
		_space = space; 
	}
	/// return the FESpace associated with the solution vector 
	FESpace* GetSpace() const {return _space; }
	/// return the L2 error 
	double L2Error(Coefficient* exact); 
private:
	/// space associated with the solution vector 
	FESpace* _space; 
}; 

} // end namespace trt 