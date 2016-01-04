#include "AssetFileExtensions.h"
#include "Texture2D.h"

//------------------------------------------//
// AssetFileExtensions::AssetFileExtensions				
//------------------------------------------//
AssetFileExtensions::AssetFileExtensions()
{
	AddFileExtensions<Texture2D>();
}

//------------------------------------------//
// AssetFileExtensions::ExtensionIsOfAssetType				
//------------------------------------------//
const bool AssetFileExtensions::ExtensionIsOfAssetType(const std::string& extension, std::type_index& type)
{
	if (mAssetExtensions.count(extension) <= 0)
	{
		return false;
	}

	type = mAssetExtensions.find(extension)->second;

	return true;
}

//------------------------------------------//
// AssetFileExtensions::InsertExtension				
//------------------------------------------//
void AssetFileExtensions::InsertExtension(const std::string& ext, const std::type_index& type)
{
	mAssetExtensions.insert(std::pair<std::string, std::type_index>(ext, type));
}

template<>
void AssetFileExtensions::AddFileExtensions<class Texture2D>()
{
	const std::type_index typeIndex(typeid(Texture2D));
	InsertExtension("png", typeIndex);
	InsertExtension("bmp", typeIndex);
	InsertExtension("jpg", typeIndex);
	InsertExtension("jpeg", typeIndex);
}