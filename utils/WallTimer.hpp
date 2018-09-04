#pragma once 

#include <chrono> 

namespace fem 
{

/// singleton class for wall timer using std::chrono
class WallTimer {
public:
	/// returns a static instance so only one can exist in the program 
	static WallTimer& instance() {
		static WallTimer wt; 
		return wt; 
	}
	/// destructor: prints wall time 
	~WallTimer(); 
private:
	/// private constructor prevents instantiating more than one WallTimer 
	WallTimer(); 
	/// store start time 
	std::chrono::time_point<std::chrono::system_clock> _start; 
	/// store the elapsed time 
	std::chrono::duration<double> _el; 
	/// true if initialized 
	bool _init; 
}; 

} // end namespace fem 