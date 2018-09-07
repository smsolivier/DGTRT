#include "TRT.hpp"

using namespace trt; 
using namespace std; 

int main() {
	int N = 10; 
	Array<int> test(N, 0); 
	for (int i=0; i<N; i++) {
		test[i] = i; 
	}
	test.Append(-1); 

	for (int i=0; i<test.Size(); i++) {
		cout << test[i] << endl; 
	}

	test.Resize(100);

	test.Print(); 

}