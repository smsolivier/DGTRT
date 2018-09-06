#pragma once 

namespace trt 
{

enum BoundaryConditions {
	INTERIOR, 
	DIRICHLET, 
	NEUMANN 
}; 

/// represent an FEM node 
class Node {
public:
	/// constructor 
	/** \param x node location 
		\param gid global id 
		\param bc boundary condition type 
	*/ 
	Node(double x, int gid, int bc) : _x(x), _gid(gid), _bc(bc) { }
	/// set the global id 
	void SetGlobalID(int id) {_gid = id; }
	/// return the global id 
	int GlobalID() const {return _gid; }
	/// return the boundary type 
	int BC() const {return _bc; }
	/// return node location 
	double X() const {return _x; }
private:
	/// location in physical space 
	double _x; 
	/// global id of this node 
	int _gid; 
	/// boundary type 
	int _bc; 
}; 

} // end namespace trt 