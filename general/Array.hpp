#pragma once 

#include <vector> 
#include <fstream>
#include <iostream>
#include "Error.hpp"

namespace trt
{

/// Template class for wrapping std::vector. Mostly provides out of range checks 
template<class T=int> 
class Array {
public:
	/// default constructor 
	Array() { }
	/// initialize 
	/** \param N size of array 
	*/ 
	Array(int N) {_vector.resize(N); }
	/// initialize and set values 
	/** \param N size of array 
		\param val initial value 
	*/ 
	Array(int N, T val) {_vector.resize(N, val); } 
	/// construct from initializer list 
	Array(std::initializer_list<T> list) {
		for (auto i=list.begin(); i != list.end(); i++) {
			_vector.push_back(*i); 
		}
	}
	/// set from initializer list 
	void operator=(std::initializer_list<T> list) {
		Clear(); 
		for (auto i=list.begin(); i != list.end(); i++) {
			_vector.push_back(*i); 
		}
	}
	/// return the size of the array 
	int Size() const {return _vector.size(); }
	/// resize the array 
	void Resize(int N) {_vector.resize(N); }
	/// access to the array 
	T& operator[](int ind) {
		CHECK(ind < _vector.size() && ind >= 0, 
			"ind = " << ind << ", size = " << _vector.size()); 
		return _vector[ind]; 
	}
	/// const access to the array 
	const T& operator[](int ind) const {
		CHECK(ind < _vector.size() && ind >= 0, 
			"ind = " << ind << ", size = " << _vector.size()); 
		return _vector[ind]; 
	}
	/// set all elements to val 
	void operator=(T val) {
		for (int i=0; i<Size(); i++) {
			(*this)[i] = val; 
		}
	}
	/// copy assignment 
	void operator=(const Array<T>& a) {
		Resize(a.Size()); 
		for (int i=0; i<a.Size(); i++) {
			(*this)[i] = a[i]; 
		}
	}
	/// add to end of Array 
	void Append(T val) {_vector.push_back(val); }
	/// add an array to the back of this 
	void Append(const Array<T>& a) {
		int size = a.Size(); 
		for (int i=0; i<size; i++) {
			Append(a[i]); 
		}
	}
	/// clear contents of vector 
	void Clear() {_vector.clear(); }
	/// return the intersection of two arrays 
	void Intersection(const Array<T>& x, Array<T>& r) const {
		for (int i=0; i<x.Size(); i++) {
			const T& ival = x[i]; 
			for (int j=0; j<Size(); j++) {
				const T& jval = (*this)[j]; 
				if (jval == ival) {
					r.Append(ival); 
				}
			}
		}
	}
	/// test if two arrays are the same 
	bool operator==(const Array<T>& a) const {
		if (Size() != a.Size()) return false; 

		for (int i=0; i<Size(); i++) {
			if (a[i] != (*this)[i]) return false; 
		}
		return true; 
	}
	/// reverse order of array 
	void Transpose() {
		Array<T> tmp = (*this); 
		for (int i=0; i<tmp.Size(); i++) {
			(*this)[i] = tmp[tmp.Size() - 1 - i]; 
		}
	}
	/// print the Array
	void Print(std::ostream& out=std::cout) const {
		for (int i=0; i<Size(); i++) {
			out << (*this)[i] << " "; 
		}
		out << std::endl; 
	}
	/// direct access to the data 
	double* Data() {return &_vector[0]; }
	/// const direct access to the data 
	const double* Data() const {return &_vector[0]; }
	/// access to the last element 
	double& Last() {return _vector[Size()-1]; }
private:
	/// vector that stores all the data 
	std::vector<T> _vector; 
}; 

template<class T> 
std::ostream& operator<<(std::ostream& out, const Array<T>& a) {
	for (int i=0; i<a.Size(); i++) {
		out << a[i] << " "; 
	}
	return out; 
}

} // end namespace trt