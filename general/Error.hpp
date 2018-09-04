#pragma once 
#include "config.hpp"
#include <iostream> 
#include <cmath> 

namespace trt
{

/// traverse the call stack to find where an error call originated 
void backtrace(int mode=0, int depth=-1); 

#define EXIT {\
	backtrace(1); \
	std::cout << "encountered FATAL ERROR... aborting" << std::endl; \
	exit(1); \
}

#define EXIT_NOBACKTRACE {\
	std::cout << "encountered FATAL ERROR... aborting" << std::endl; \
	exit(1); \
}

#define SRCMSG " ... in " << __PRETTY_FUNCTION__ << "\n ... from " \
	<< __FILE__ << " " << __LINE__

#define PRINTMSG(msg) "\n --> " << msg << std::endl 

#define ERROR(msg) {\
	std::cout << "FATAL ERROR:" << PRINTMSG(msg) << SRCMSG << std::endl; \
	EXIT; \
}

#define WARNING(msg) {\
	std::cout << "*** WARNING: " << msg << std::endl; \
}

#ifndef NDEBUG 
#define CHECK(chk, msg) {\
	if (!(bool)(chk)) {\
		std::cout << "CHECK FAILED: " << #chk << " is false" << \
		PRINTMSG(msg) << SRCMSG << std::endl; \
		EXIT; \
	}\
}
#else 
#define CHECK(chk, msg) 
#endif

#define TEST(chk, msg) {\
	std::cout << msg << ": "; \
	if ((bool)(chk)) {\
		std::cout << "pass" << std::endl; \
	} else {\
		std::cout << "fail" << std::endl; \
		EXIT_NOBACKTRACE; \
	}\
}

#define EQUAL(a, b) (fabs(a-b) < 1e-7) 

} // end namespace trt 
