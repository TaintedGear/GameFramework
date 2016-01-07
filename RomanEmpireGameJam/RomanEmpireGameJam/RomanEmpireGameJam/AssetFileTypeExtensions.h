#pragma once

#include "PCH.h"
#include "Texture2D.h"

class AssetFileTypeExtensions
{
public:
	AssetFileTypeExtensions();
	// Checks Hash against valid extentions
	const bool ExtensionIsOfAssetType(const std::string& extension, size_t& typeHash);
	//Converts a hash back to the asset name
	const bool HashIsOfAssetName(const size_t typeHash, std::string& assetName);

private:
	template <class T>
	void AddFileExtensions();
	template <>
	void AddFileExtensions<class Texture2D>();

private:
	void InsertExtension(const std::string& ext, const size_t& typeHash);
	void CreateAssetTypeHashMap();

	// Key: Type Hash, Type String
	std::map<size_t, std::string> mAssetTypeString;

	// Key: Extension string, TypeHash
	std::map<std::string, size_t> mAssetExtensions;
};

