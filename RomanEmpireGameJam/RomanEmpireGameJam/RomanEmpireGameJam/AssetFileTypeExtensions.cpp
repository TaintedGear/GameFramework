#include "AssetFileTypeExtensions.h"
#include "Texture2D.h"

//------------------------------------------//
// AssetFileExtensions::AssetFileExtensions				
//------------------------------------------//
AssetFileTypeExtensions::AssetFileTypeExtensions()
{
	// Create asset string hashmap
	CreateAssetTypeHashMap();

	// Create the accepted extensions
	AddFileExtensions<Texture2D>();
}

//------------------------------------------//
// AssetFileTypeExtensions::CreateAssetTypeHashMap				
//------------------------------------------//
void AssetFileTypeExtensions::CreateAssetTypeHashMap()
{
	std::size_t textureHash = typeid(Texture2D).hash_code();
	mAssetTypeString[textureHash] = "Texture2D";
	mAssetTypeHash["Texture2D"] = textureHash;
}

template<>
void AssetFileTypeExtensions::AddFileExtensions<class Texture2D>()
{
	//Could remove this typeid with the use of the assetTypeHashMap
	const std::type_index typeIndex(typeid(Texture2D));
	const size_t typeHash = typeIndex.hash_code();
	InsertExtension("png", typeHash);
	InsertExtension("bmp", typeHash);
	InsertExtension("jpg", typeHash);
	InsertExtension("jpeg", typeHash);
}

//------------------------------------------//
// AssetFileExtensions::ExtensionIsOfAssetType				
//------------------------------------------//
const bool AssetFileTypeExtensions::ExtensionIsOfAssetType(const std::string& extension, size_t& typeHash)
{
	// Sanity check
	if (extension.length() <= 0)
	{
		return false;
	}

	if (mAssetExtensions.count(extension) <= 0)
	{
		return false;
	}

	typeHash = mAssetExtensions.find(extension)->second;

	return true;
}      

//------------------------------------------//
// AssetFileTypeExtensions::HashIsOfAssetName				
//------------------------------------------//
const bool AssetFileTypeExtensions::HashIsOfAssetTypeName(const size_t typeHash, std::string& assetName)
{
	if (mAssetTypeString.count(typeHash) <= 0)
	{
		return false;
	}

	assetName = mAssetTypeString.find(typeHash)->second;

	return true;
}

//------------------------------------------//
// AssetFileTypeExtensions::AssetTypeIsofHash				
//------------------------------------------//
const bool AssetFileTypeExtensions::AssetTypeNameIsOfHash(const std::string& assetType, size_t& typeHash)
{
	if (mAssetTypeHash.count(assetType) <= 0)
	{
		return false;
	}

	typeHash = mAssetTypeHash.find(assetType)->second;

	return true;
}

//------------------------------------------//
// AssetFileExtensions::InsertExtension				
//------------------------------------------//
void AssetFileTypeExtensions::InsertExtension(const std::string& ext, const  size_t& typeHash)
{
	mAssetExtensions.insert(std::pair<std::string, size_t>(ext, typeHash));
}