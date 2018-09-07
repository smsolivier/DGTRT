#include "WallTimer.hpp"
#include <iostream> 

using namespace std; 

namespace trt
{

WallTimer::WallTimer() {
	if (!_init) {
		_init = true; 
		_start = chrono::system_clock::now(); 
	}
}
WallTimer::~WallTimer() {
	if (getenv("NWTIMER") != NULL) return; 
	_el = chrono::system_clock::now() - _start; 
	if (_el.count() > 60) {
		std::cout << "Wall Time = " << _el.count()/60. << " minutes" << std::endl; 
	} else {
		std::cout << "Wall Time = " << _el.count() << " seconds" << std::endl; 
	}
}

} // end namespace trt 