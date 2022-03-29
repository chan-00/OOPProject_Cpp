#ifndef __AccountArr__
#define __AccountArr__

#include<iostream>
#include<cstring>
using namespace std;

template <typename T>
class AccArray {
private:
	T* arr;
	int arrlen;

	AccArray(const T& arr);
	AccArray& operator=(const T& arr);
public:
	AccArray(int len = 50) : arrlen(len) {
		arr = new T[len];
	}
	T& operator[](int i) {
		if (i < 0 && i >= arrlen) {
			cout << "배열의 범위를 벗어납니다." << endl;
			exit(1);
		}
		return arr[i];
	}
	T& operator[](int i) const {
		if (i < 0 && i >= arrlen) {
			cout << "배열의 범위를 벗어납니다." << endl;
			exit(1);
		}
		return arr[i];
	}
	int GetArrLen() const {
		return arrlen;
	}
	~AccArray() {
		delete[]arr;
	}
};

#endif