#ifndef __UNIQUE_PTR_H_INCLUDED__
#define __UNIQUE_PTR_H_INCLUDED__

template <typename T>
class uniquePtr
{
public:
	explicit uniquePtr(T* ptr = nullptr);
	uniquePtr(uniquePtr&&);
	uniquePtr(const uniquePtr&) = delete;
	~uniquePtr();

	uniquePtr& operator=(uniquePtr);

	T* operator->();
	T& operator*();

	operator bool()const;
	bool operator!()const;

private:
	T* ptr;
};

#include "uniquePtrImpl.hpp"
#endif //__UNIQUE_PTR_H_INCLUDED__
