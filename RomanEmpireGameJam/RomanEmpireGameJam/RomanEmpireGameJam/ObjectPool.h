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
//template<class T>
//class ObjectPool
//{
//public:
//	ObjectPool(const uint& pObjectCount){};
//	virtual ~ObjectPool(){};
//
//	std::shared_ptr<T> Create()(return nullptr;);
//
//private:
//	// Holds the amount of objects this pool can manage
//	uint mObjectCount;
//	std::vector< std::weak_ptr<T> > mPool;
//};

////------------------------------------------//
//// ObjectPool<T>::ObjectPool				
////------------------------------------------//
//template<class T>
//ObjectPool<T>::ObjectPool(const uint& pObjectCount)
//{
//	mObjectCount = pObjectCount;
//
//	//Create shared ptrs and store as weak ptr's the 
//	for (uint p = 1; p <= mObjectCount; ++p)
//	{
//		mPool.push_back(std::make_shared<T>());
//	}
//}
//
////------------------------------------------//
//// ObjectPool<T>::~ObjectPool				
////------------------------------------------//
//template<class T>
//ObjectPool<T>::~ObjectPool()
//{
//
//}
//
////------------------------------------------//
//// ObjectPool<T>::Create				
////------------------------------------------//
//template<class T>
//std::shared_ptr<T> ObjectPool<T>::Create()
//{
//
//}
