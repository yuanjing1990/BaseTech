#ifndef BASEUTIL_H_
#define BASEUTIL_H_

//For delete Object in vector
struct DeleteObj {
	template<class T>
	void operator()(const T* ptr) const {
		delete ptr;
	}
	template<class T>
	void operator()(T*& ptr) const {
		delete ptr;ptr = NULL;
		cout << "set NULL" << endl;
	}
};

#endif
