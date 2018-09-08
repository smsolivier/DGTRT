#pragma once 

#include "Element.hpp"

namespace trt 
{

/// abstract class for finite element spaces 
class FESpace {
public:
	/// constructor 
	/** \param Ne number of elements 
		\param order polynomial order 
	*/ 
	FESpace(int Ne, double xb, int order); 
	/// return the number of unknowns 
	int GetVSize() const {return _nodes.Size(); }
	/// return the number of elements 
	int GetNumElements() const {return _els.Size(); }
	/// return the number of nodes 
	int GetNumNodes() const {return _nodes.Size(); }
	/// access to element e
	Element& GetElement(int e) {return *_els[e]; }
	/// access to node i 
	const Node& GetNode(int i) const {return *_nodes[i]; }
protected:
	/// store the elements in the FESpace 
	Array<Element*> _els; 
	/// store their nodes 
	Array<Node*> _nodes; 
}; 

/// Discontinuous Galerkin finite element space 
class L2Space : public FESpace {
public:
	/// constructor 
	L2Space(int Ne, double xb, int order); 
}; 

} // end namespace trt 