#pragma once

#include "PCH.h"
#include "Asset.h"

// Will create the asset of type T and setup the load and unload functions
template <class T> class AssetLoader
{
public:
	//Static assert if this is not of type Asset
	static_assert(std::is_base_of< class Asset, T>::value, "AssetLoader<T> is not of base Asset.");

	AssetLoader() {};
	virtual ~AssetLoader() {};

	virtual bool StartupLoader();

	virtual bool LoadAsset( std::shared_ptr<T> unloadedAsset ) = 0;
	virtual void UnloadAsset(T* asset) = 0;

protected:
};

//------------------------------------------//
// AssetLoader<T>::StartupLoader				
//------------------------------------------//
template <class T>
bool AssetLoader<T>::StartupLoader()
{
	return true;
}




