#pragma once 
#include "General.hpp"
#include "Vector.hpp"

struct lua_State; 

namespace fem 
{

/// read in and access a Lua script 
class LuaReader {
public:
	/// constructor 
	/** \param filename name of lua script */ 
	LuaReader(std::string filename); 
	/// default constructor 
	LuaReader(); 
	/// set the lua script file name 
	void SetLuaFile(std::string filename); 
	/// parse argc and argv for Lua file name 
	/** \param argc number of command line arguments 
		\param argv command line arguments array 
		\param def default lua script to load if Lua script not specified 
	*/ 
	void Parse(int argc, char* argv[], std::string def="none"); 

	/// return a vector valued function named field_name 
	void VectorFunction(const char* field_name, const Point& x, Vector& v) const; 
	/// return a scalar valued function name field_name 
	double ScalarFunction(const char* field_name, const Point& x) const; 
	/// return a double named field_name from lua script 
	double Double(const char* field_name) const; 
	/// return a double with default value if not found 
	double Double(const char* field_name, double def) const; 
	/// return a required integer named field_name 
	int Int(const char* field_name) const; 
	/// return an optional integer name field_name. Returns def if not found 
	int Int(const char* field_name, int def) const; 
	/// read a string field_name from lua script 
	std::string String(const char* field_name) const; 
	/// read an optional string return def if not found 
	std::string String(const char* field_name, std::string def) const; 
	/// return a bool value. Returns false if not found 
	bool Bool(const char* field_name) const; 

	// common definitions 
	/// get the mesh file name. Lua keyword = mesh_file 
	std::string MeshFile() const {return String("mesh_file"); }
	/// return the number of mesh refinements. Lua keyword = nref 
	int MeshRefinements() const {return Int("nref", 0); }
	/// evaluate source_function from lua script. Lua keyword = source_function 
	double SourceFunction(const Point& x) {
		return ScalarFunction("source_function", x); 
	}
	/// evaluate initial conditions. Lua keyword = initial_function 
	double InitialConditions(const Point& x) {
		return ScalarFunction("initial_function", x); 
	}
	/// return the output name from lua script. Lua keyword = output_file 
	std::string OutputFile() const {return String("output_file", "solution"); }
	/// return the end time. Lua keyword = end_time 
	double EndTime() const {return Double("end_time"); }
	/// return the time step. Lua keyword = time_step 
	double TimeStep() const {return Double("time_step"); }
	/// return the writer frequency. Lua keyword write_freq 
	int WriteFreq() const {return Int("write_freq", 1); }
	/// return the fe order. Lua keyword = fe_order 
	int FEOrder() const {return Int("fe_order", 1); }

private:
	/// lua parser 
	lua_State* _state; 
}; 

} // end namespace fem 