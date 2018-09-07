#pragma once 

#include "Error.hpp"
#include "Basis.hpp"
#include "ElTrans.hpp"
#include "Node.hpp"

namespace trt 
{

class ElTrans; 

/// abstract class for elements 
class Element {
public:
	/// constructor 
	/** \param xl left end point 
		\param xr right end point 
		\param order polynomial order 
		\param bcl left boundary condition 
		\param bcr right boundary condition 
	*/ 
	Element(Node left, Node right, int order); 
	/// destructor 
	~Element(); 
	/// evaluate all basis functions at an integration point 
	virtual void CalcShape(double x, Vector& shape) const {
		ERROR("not implemented"); 
	}
	/// evaluate derivative of all basis functions at an integration point 
	virtual void CalcGradShape(double x, Vector& shape) const {
		ERROR("not implemented"); 
	}
	/// evaluate derivatives in physical space (divide by Jacobian) 
	void CalcPhysGradShape(double x, Vector& shape) const; 
	/// return the number of nodes in this element 
	int NumNodes() const {return _nodes.Size(); }
	/// return the ith FEM node 
	const Node& GetNode(int i) const;  
	/// return the ith FEM node 
	Node& GetNode(int i); 
	/// return the element transformation 
	ElTrans& GetTrans() {return *_trans; }

	/// interpolate to a point 
	double Interpolate(double x, const Vector& u) const; 
	/// get the ids of all nodes in the element 
	void GetVDofs(Array<int>& vdofs) const; 
	/// return the polynomial order of this element 
	int GetOrder() const {return _order; }
protected:
	/// left end point node 
	Node& _left; 
	/// right end point node 
	Node& _right; 
	/// polynomial order 
	int _order; 
	/// left boundary condition 
	int _bcl; 
	/// right boundary condition 
	int _bcr; 
	/// basis object 
	Basis _basis; 
	/// element transformation for *this 
	ElTrans* _trans; 
	/// store FEM nodes 
	Array<Node*> _nodes; 
}; 

} // end namespace trt 