#pragma once

#include "PCH.h"
#include "Asset.h"
#include "AssetLoader.h"

class IAssetPool
{
public:
	IAssetPool() {};
	IAssetPool(const int& pAssetCount) { mObjectCount = pAssetCount; };
	virtual ~IAssetPool() = 0;

	virtual bool RequestAssetObject(class AssetLoader* pLoader, std::shared_ptr< class Asset>& pAsset) = 0;
	virtual bool FindAssetObject(const std::string& pFilename, std::shared_ptr<Asset>& pAsset) = 0;

public:
	int mObjectCount;

	std::vector<Asset*> mAssetPool;
	std::vector< std::weak_ptr<Asset> > mAssetWeakRef;
};

inline IAssetPool::~IAssetPool() {}

template< class T >
class AssetPool : public IAssetPool
{
public:
	//The total allowed of assets of this type (Allows for budgeting memory)
	AssetPool(const int& pAssetCount);
	virtual ~AssetPool();

	//Asks for a deleter function to be passed into the request object so asset can be unloaded
	bool RequestAssetObject(class AssetLoader* pLoader, std::shared_ptr<class Asset>& pAsset) override;

	bool FindAssetObject(const std::string& pFilename, std::shared_ptr<Asset>& pAsset) override;

private:
	void AllocatePool();
	void DeletePool();
};

//------------------------------------------//
// AssetPool<T>::AssetPool				
//------------------------------------------//
template< class T >
AssetPool<T>::AssetPool(const int& pAssetCount) 
	:
	IAssetPool(pAssetCount)
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
bool AssetPool<T>::RequestAssetObject(class AssetLoader* pLoader, std::shared_ptr<class Asset>& pAsset)
{
	if (pLoader == nullptr)
	{
		return false;
	}

	//Check if the loader matches the type
	const std::type_index assetPoolType = typeid(T);
	if (assetPoolType != pLoader->GetAssetType())
	{
		return false;
	}

	// TODO: CHANGE THIS
	// Check for an un-used object
	int foundIndex = -1;
	for (int p = 0; p < mObjectCount; ++p)
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
		return false;
	}

	Asset* foundAsset = nullptr;
	foundAsset = mAssetPool[foundIndex];

	// Create the shared ptr with the custom deleter
	std::shared_ptr<Asset> requestObject(foundAsset, std::bind(&AssetLoader::UnloadAsset, pLoader, foundAsset));
	mAssetWeakRef[foundIndex] = requestObject;

	pAsset = requestObject;

	return true;
}


//------------------------------------------//
// AssetPool<T>::FindAssetObject				
//------------------------------------------//
template< class T >
bool AssetPool<T>::FindAssetObject(const std::string& pFilename, std::shared_ptr<Asset>& pAsset)
{
	// Find the asset in the pool
	std::shared_ptr<Asset> foundAsset = nullptr;
	for (int p = 0; p < mObjectCount; ++p)
	{
		foundAsset = mAssetWeakRef[p].lock();
		if (foundAsset != nullptr)
		{
			if (foundAsset->AssetFileName() == pFilename)
			{
				pAsset = foundAsset;
				return true;
			}
		}
	}

	return false;
}


//------------------------------------------//
// AssetPool<T>::AllocatePool				
//------------------------------------------//
template< class T >
void AssetPool<T>::AllocatePool()
{
	for (unsigned int p = 0; p < (unsigned)mObjectCount; ++p)
	{
		T* newObject = new T;
		newObject = nullptr;

		mAssetPool.push_back(newObject);
		std::weak_ptr<T> newWeakPtr;
		mAssetWeakRef.push_back(newWeakPtr);
	}
}

//------------------------------------------//
// AssetPool<T>::DeletePool				
//------------------------------------------//
template< class T >
void AssetPool<T>::DeletePool()
{
	for (unsigned int p = 0; p < mAssetPool.size(); ++p)
	{
		delete mAssetPool[p];
	}
}


