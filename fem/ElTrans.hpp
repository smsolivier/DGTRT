#pragma once 

#include "Element.hpp"

namespace trt 
{

class Element; 

/// reference to physical space transformation 
class ElTrans {
public:
	/// constructor 
	ElTrans(Element* el); 
	/// evaluate jacobian in reference space 
	double Jacobian(double xref);  
	/// transform reference to physical space 
	double Transform(double xref); 
private:
	/// store the element 
	Element* _el; 
}; 

} // end namespace trt 