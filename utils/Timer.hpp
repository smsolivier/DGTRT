#pragma once 

#include <chrono> 
#include <fstream> 

namespace trt 
{

/// stopwatch class that wraps std::chrono 
class Timer {
public:
	/// constructor 
	Timer() { } 
	/// start the clock 
	void Start(); 
	/// stop the clock 
	void Stop(); 
	/// return the duration 
	double GetDuration() const {return _el.count(); }
private:
	/// store the start time 
	std::chrono::time_point<std::chrono::system_clock> _start; 
	/// store the elapsed time 
	std::chrono::duration<double> _el; 
};

std::ostream& operator<<(std::ostream& out, const Timer& t);   

} // end namespace trt 