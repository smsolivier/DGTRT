#pragma once 

#include "FESpace.hpp"
#include "Vector.hpp"

namespace trt 
{

/// represent a solution vector on an FESpace 
class GridFunction : public Vector {
public:
	/// constructor 
	GridFunction(const FESpace* space) : Vector(space->GetVSize()) {
		_space = space; 
	}
	/// return the FESpace associated with the solution vector 
	const FESpace* GetSpace() const {return _space; }

private:
	/// space associated with the solution vector 
	const FESpace* _space; 
}; 

} // end namespace trt 