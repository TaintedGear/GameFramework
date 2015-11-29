#pragma once

#include "PCH.h"

// DO NOT USE THIS, i dont think i will need this as of yet as its not a problem
// (When a new shared ptr is created bind a custom delete function to return it to this pool)
// Requires use of raw pointers and delete on the object pool destructor.
// http://stackoverflow.com/questions/12340810/using-custom-deleter-with-stdshared-ptr

//Object pool class which allows the creation of objects to be pooled 
// REQUIRES A DELETER SO IF AN OBJECT IS DESTROYED IT CAN BE PASSED BACK TO THIS POOL
// OR IF THE POOL IS DESTROYED BEFORE THE OBJECT HAS BEEN DEALLOCATED THEN THE PTR DEALLOCATES ITSELF
// currently just a chunk allocator not a pool
template<class T>
class ObjectPool
{
public:
	ObjectPool();
	~ObjectPool();

	//Will setup the pool to start to allocate all the memory needed depending on the object count
	bool AllocatePool(const int& pObjectCount);

	//Returns an empty object from the pool
	std::shared_ptr<T> Create();

	int ObjectCount() const { return mObjectCount; }

private:
	void Recycle(T* ptr);

	int mObjectCount;

	std::vector< bool > mInUseFlags;
	std::vector< std::shared_ptr<T> > mPool;
};

//------------------------------------------//
// ObjectPool<T>::ObjectPool				
//------------------------------------------//
template<class T>
ObjectPool<T>::ObjectPool() :
mObjectCount(0)
{

}

//------------------------------------------//
// ObjectPool<T>::~ObjectPool				
//------------------------------------------//
template<class T>
ObjectPool<T>::~ObjectPool()
{
	//Dont need to iterate through and destroy as they are smart pointer and will internally destroy
}

//------------------------------------------//
// ObjectPool<T>::AllocatePool				
//------------------------------------------//
template<class T>
bool ObjectPool<T>::AllocatePool(const int& pObjectCount)
{
	{
		if (pObjectCount <= 0)
		{
			//Log
			return false;
		}

		for (const int& i = 0; i <= pObjectCount; ++i)
		{
			mPool.push_back(make_shared<T>());
			mInUseFlags.push_back(false);
		}

		//Sanity check the length of the two vectors (Should be fine but as a fallback)
		if (mPool.size() != mInUseFlags.size())
		{
			return false;
		}
	}
}

//------------------------------------------//
// ObjectPool<T>::Create				
//------------------------------------------//
template<class T>
std::shared_ptr<T> ObjectPool<T>::Create()
{
	//Quickly sanity check the two vectors are of the same length
	if (mPool.size() != mInUseFlags.size())
	{
		return nullptr;
	}

	//Find a free index
	int freeIndex = -1;
	for (const int& i = 0; i <= mObjectCount; ++i)
	{
		if (!mInUseFlags[i])
		{
			freeIndex = i;
			break;
		}
	}

	//Pool is in full use
	if (freeIndex <= -1)
	{
		return nullptr;
	}
	else
	{
		mInUseFlags[freeIndex] = true;
		return mPool[freeIndex];
	}
}

//------------------------------------------//
// ObjectPool<T>::Recycle				
//------------------------------------------//
template<class T>
void ObjectPool<T>::Recycle(T* ptr)
{

}
