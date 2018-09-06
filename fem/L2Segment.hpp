#pragma once 

#include "Element.hpp"

namespace trt 
{

/// 1D discontinuous galerkin element 
class L2Segment : public Element {
public:
	/// constructor 
	L2Segment(Node left, Node right, int order); 
	/// evaluate basis functions 
	void CalcShape(double x, Vector& shape) const; 
	/// evaluate derivatives of basis functions 
	void CalcGradShape(double x, Vector& gshape) const; 
}; 

} // end namespace trt 