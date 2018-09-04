#include "Lua.hpp"
#include "lua.hpp"

#define LUAERROR {ERROR("field name " << field_name << " not found in Lua script"); }

namespace fem 
{

LuaReader::LuaReader(std::string filename) {
	_state = luaL_newstate(); 
	luaL_openlibs(_state); 
	SetLuaFile(filename); 
}

LuaReader::LuaReader() {
	_state = luaL_newstate(); 
	luaL_openlibs(_state); 
}

void LuaReader::SetLuaFile(std::string filename) {
	// look for files in exec, test, lua, current directories 

	// current directory 
	if (!luaL_dofile(_state, filename.c_str())) {
		return; 
	} 
	// exec directory 
	else if (!luaL_dofile(_state, (EXEC_DIR + filename).c_str())) {
		return; 
	} 
	// test directory 
	else if (!luaL_dofile(_state, (TEST_DIR + filename).c_str())) {
		return; 
	} 
	// lua directory 
	else if (!luaL_dofile(_state, (LUA_DIR + filename).c_str())) {
		return; 
	} 
	// not found :( 
	else {
		ERROR("lua file not found in exec, test, lua, or current directory"); 
	}
}

void LuaReader::Parse(int argc, char* argv[], std::string def) {
	if (argc > 1) SetLuaFile(argv[1]); 
	else {
		if (def != "none") SetLuaFile(def); 
		else ERROR("lua file not set"); 
	}
}

bool LuaReader::Bool(const char* field_name) const {
	lua_getglobal(_state, field_name); 
	if (lua_isnil(_state, -1)) {
		return false; 
	}

	const bool result = static_cast<bool>(lua_toboolean(_state, -1)); 
	lua_pop(_state, 1); 

	return result; 
}

int LuaReader::Int(const char* field_name) const {
	lua_getglobal(_state, field_name); 
	if (lua_isnil(_state, -1)) LUAERROR; 

	int ret = static_cast<int>(lua_tonumber(_state, -1)); 
	lua_pop(_state, 1); 

	return ret; 
}

int LuaReader::Int(const char* field_name, int def) const {
	lua_getglobal(_state, field_name); 
	if (lua_isnil(_state, -1)) {
		return def; 
	}

	int ret = static_cast<int>(lua_tonumber(_state, -1)); 
	lua_pop(_state, 1); 

	return ret; 
}

double LuaReader::Double(const char* field_name) const {
	lua_getglobal(_state, field_name); 
	if (lua_isnil(_state, -1)) LUAERROR; 

	const double result = static_cast<double>(lua_tonumber(_state, -1)); 
	lua_pop(_state, 1); 

	return result; 
}

double LuaReader::Double(const char* field_name, double def) const {
	lua_getglobal(_state, field_name); 
	if (lua_isnil(_state, -1)) return def; 

	const double result = static_cast<double>(lua_tonumber(_state, -1)); 
	lua_pop(_state, 1); 

	return result; 
}

std::string LuaReader::String(const char* field_name, std::string def) const {
	lua_getglobal(_state, field_name); 
	if (lua_isnil(_state, -1)) {
		return def; 
	}

	std::string ret = lua_tostring(_state, -1); 
	lua_pop(_state, 1); 

	return ret; 
}

std::string LuaReader::String(const char* field_name) const {
	lua_getglobal(_state, field_name); 
	if (lua_isnil(_state, -1)) LUAERROR; 

	std::string ret = lua_tostring(_state, -1); 
	lua_pop(_state, 1); 

	return ret; 
}

double LuaReader::ScalarFunction(const char* field_name, const Point& x) const {
	double result; 

	lua_getglobal(_state, field_name); 
	if (lua_isnil(_state, -1)) LUAERROR; 

	lua_pushnumber(_state, x[0]); 
	lua_pushnumber(_state, x[1]); 
#if DIM==3 
	lua_pushnumber(_state, x[2]); 
#else 
	lua_pushnumber(_state, 0.); 
#endif

	lua_call(_state, 3, 1); 
	result = static_cast<double>(lua_tonumber(_state, -1)); 
	lua_pop(_state, 1); 
	lua_settop(_state, 0); 

	return result; 
}

void LuaReader::VectorFunction(const char* field_name, 
	const Point& x, Vector& v) const {

	lua_getglobal(_state, field_name); 
	if (lua_isnil(_state, -1)) LUAERROR; 

	lua_pushnumber(_state, x[0]); 
	lua_pushnumber(_state, x[1]); 
#if DIM==3 
	lua_pushnumber(_state, x[2]); 
#else 
	lua_pushnumber(_state, 0.); 
#endif

	lua_call(_state, 3, 3); 
	v[0] = lua_tonumber(_state, -3); 
	v[1] = lua_tonumber(_state, -2); 
	if (v.GetSize() == 3) 
		v[2] = lua_tonumber(_state, -1); 
	lua_pop(_state, 3); 
	lua_settop(_state, 0); 
}

}