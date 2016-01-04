#pragma once

#include "Asset.h"
#include "AssetLoader.h"
#include "Log.h"

template <class T> class AssetPool
{
public:
	//Static assert if this is not of type Asset
	static_assert(std::is_base_of< class Asset, T>::value, "AssetPool<T> is not of base Asset.");

	AssetPool( const int& preallocateAmount = 0);
	~AssetPool();

	// Will allocate an unloaded asset with a bound UnloadAsset function from the asset loader on destruction
	// Or will reuse an unloaded asset
	std::shared_ptr<T> RequestAssetObject(
		class AssetLoader<T>* assetLoader);

private:
	void AllocatePool(const int& allocationAmount);
	void DeallocatePool();

	//Quick wrapper to store both T* and weakptr to that objects shared ptr
	struct AssetPoolWrapper
	{
		T* AssetObject;
		std::weak_ptr<T> AssetWeakPtr;
	};

	std::vector<AssetPoolWrapper> mAssetPool;
};

//------------------------------------------//
// AssetPool<T>::AssetPool				
//------------------------------------------//
template <class T>
AssetPool<T>::AssetPool( const int& preallocateCount )
{
	AllocatePool(preallocateCount);
}

//------------------------------------------//
// AssetPool<T>::~AssetPool				
//------------------------------------------//
template <class T>
AssetPool<T>::~AssetPool()
{
	DeallocatePool();
}

//------------------------------------------//
// AssetPool<T>::RequestAssetObject				
//------------------------------------------//
template <class T>
std::shared_ptr<T> AssetPool<T>::RequestAssetObject(
	class AssetLoader<T>* assetLoader)
{
	if (assetLoader == nullptr)
	{
		//Log warning
		Log::GetLog().LogCriticalMsg("Failed to return requested asset object as asset loader is null!");
		return nullptr;
	}

	// Currently O(n)
	const size_t assetPoolSize = mAssetPool.size();
	for (unsigned int i = 0; i < assetPoolSize; i++)
	{
		if (mAssetPool[i].AssetWeakPtr.lock() == nullptr)
		{
			// Create the shared ptr to wrap around this new asset with the addition
			// of the unload func as the destructor
			std::shared_ptr<T> assetSharedPtr(
				mAssetPool[i].AssetObject,
				std::bind(&AssetLoader<T>::UnloadAsset, assetLoader, mAssetPool[i].AssetObject));

			//Assign the weak ptr to this shared ptr
			mAssetPool[i].AssetWeakPtr = assetSharedPtr;

			return assetSharedPtr;
		}
	}

	// If we are here then we did not find a free asset object - Create a new one
	AssetPoolWrapper newAssetPoolWraper;
	newAssetPoolWraper.AssetObject = new T();

	// Store in the pool
	mAssetPool.push_back(newAssetPoolWraper);

	// Create the shared ptr with the unload function of the loader
	std::shared_ptr<T> assetSharedPtr(
		newAssetPoolWraper.AssetObject,
		std::bind(&AssetLoader<T>::UnloadAsset, assetLoader, newAssetPoolWraper.AssetObject));

	// Assign the weak ptr
	newAssetPoolWraper.AssetWeakPtr = assetSharedPtr;

	// Log that we are overflowing the pool - option to turn this off?
	Log::GetLog().LogLowMsg("Asset Pool is going into an overflow when creating this asset object");

	return assetSharedPtr;
}

//------------------------------------------//
// AssetPool<T>::AllocatePool				
//------------------------------------------//
template <class T>
void AssetPool<T>::AllocatePool(const int& allocationAmount)
{
	//Preallocate any memory upfront
	if (allocationAmount > 0)
	{
		for (int i = 0; i < allocationAmount; i++)
		{
			AssetPoolWrapper newAssetPoolWraper;
			newAssetPoolWraper.AssetObject = new T();

			mAssetPool.push_back(newAssetPoolWraper);
		}
	}
}

//------------------------------------------//
// AssetPool<T>::DeallocatePool				
//------------------------------------------//
template <class T>
void AssetPool<T>::DeallocatePool()
{
	const size_t assetPoolSize = mAssetPool.size();
	for (unsigned int i = 0; i < assetPoolSize; i++)
	{
		SAFE_DELETE(mAssetPool[i].AssetObject);
	}
}