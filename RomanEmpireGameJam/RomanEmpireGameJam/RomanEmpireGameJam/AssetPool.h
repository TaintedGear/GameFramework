#pragma once

#include "PCH.h"

template< class T >
class AssetPool
{
public:
	//The total allowed of assets of this type (Allows for budgeting memory)
	AssetPool( const int& pAssetCount);
	virtual ~AssetPool();

	//Asks for a deleter function to be passed into the request object so asset can be unloaded
	std::shared_ptr<T> RequestObject( const std::function<void()>& pUnloaderFunc, bool& pResult );

private:
	int mObjectCount;
	std::vector<T*> mAssetPool;
	std::vector< std::weak_ptr<T> > mAssetWeakRef;

	void AllocatePool();
	void DeletePool();
};

//------------------------------------------//
// AssetPool<T>::AssetPool				
//------------------------------------------//
template< class T >
AssetPool<T>::AssetPool(const int& pAssetCount)
	:
mObjectCount(pAssetCount)
{
	if (mObjectCount <= 0)
	{
		//LOG
	}

	AllocatePool();
}

//------------------------------------------//
// AssetPool<T>::~AssetPool				
//------------------------------------------//
template< class T >
AssetPool<T>::~AssetPool()
{
	DeletePool();
}

//------------------------------------------//
// AssetPool<T>::RequestObject				
//------------------------------------------//
template< class T >
std::shared_ptr<T> AssetPool<T>::RequestObject(const std::function<void()>& pUnloaderFunc, bool& pResult)
{
	// TODO: CHANGE THIS
	// Check for an un-used object
	uint foundIndex = -1;
	for (uint p = 1; p <= mObjectCount; ++p)
	{
		if (mAssetWeakRef[p].lock() == nullptr)
		{
			foundIndex = p;
			break;
		}
	}

	if (foundIndex <= -1)
	{
		//LOG - Pool is at full capacity (could possibly overflow if this is the case)
		pResult = false;
		return nullptr;
	}

	// Create the shared ptr with the custom deleter
	std::shared_ptr<T> requestObject(mAssetPool[foundIndex], pUnloaderFunc);
	mAssetWeakRef[foundIndex] = requestObject;

	return requestObject;
}

//------------------------------------------//
// AssetPool<T>::AllocatePool				
//------------------------------------------//
template< class T >
void AssetPool<T>::AllocatePool()
{
	for (uint p = 1; p <= mObjectCount; ++p)
	{
		T* newObject = new T;
		newObject = nullptr;

		mAssetPool.push_back(newObject);
		mAssetPool.push_back(std::weak_ptr<T>)
	}
}

//------------------------------------------//
// AssetPool<T>::DeletePool				
//------------------------------------------//
template< class T >
void AssetPool<T>::DeletePool()
{
	for (uint p = 1; p <= mAssetPool.size(); ++p)
	{
		delete mAssetPool[p];
	}
}


