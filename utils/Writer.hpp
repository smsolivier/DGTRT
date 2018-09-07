#pragma once 

#include "Error.hpp"
#include "GridFunction.hpp"
#include "Array.hpp"

namespace trt 
{

/// stores pointers to GridFunctions and writes them to file 
class Writer {
public:
	/// constructor. provide base name for output files 
	Writer(std::string name="solution"); 
	/// add a solution variable to the output list 
	void Add(GridFunction& gf, std::string name); 
	/// set the output frequency for time dependent calculations 
	void SetFreq(int f) {_f = f; }
	/// write to file 
	/** \param force writes regardless of frequency if true */ 
	void Write(bool force=false); 
private:
	/// output frequency
	int _f; 
	/// store pointers to GridFunctions 
	Array<GridFunction*> _gf; 
	/// store their corresponding names 
	Array<std::string> _names; 
	/// store the base name 
	std::string _base_name; 
	/// number of times Write has been called 
	int _count; 
	/// number of files written 
	int _writes; 
}; 

} // end namespace trt 