#include "Timer.hpp"

using namespace std; 

namespace trt 
{

void Timer::Start() {
	_start = chrono::system_clock::now(); 
}

void Timer::Stop() {
	_el = chrono::system_clock::now() - _start; 
}

ostream& operator<<(ostream& out, const Timer& t) {
	double count = t.GetDuration(); 
	out << count << " "; 
	if (count > 60) {
		out << "min"; 
	} else {
		out << "s"; 
	}
	return out; 
}

} // end namespace trt 