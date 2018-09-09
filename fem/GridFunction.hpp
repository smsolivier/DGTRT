#pragma once 

#include "FESpace.hpp"
#include "Vector.hpp"
#include "Coefficient.hpp"

namespace trt 
{

class Coefficient; 

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
	/// evaluate a function and store in this 
	void Project(double (*f)(double)); 
	/// evaluate at a coefficient at every node 
	void Project(Coefficient* c); 
	/// assign all elements to a value 
	void operator=(double val) {Vector::operator=(val); }
private:
	/// space associated with the solution vector 
	FESpace* _space; 
}; 

} // end namespace trt 