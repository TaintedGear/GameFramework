#pragma once

#include "PCH.h"
#include "Texture2D.h"

class AssetFileExtensions
{
public:
	AssetFileExtensions();
	const bool ExtensionIsOfAssetType(const std::string& extension, std::type_index& type);

private:
	template <class T>
	void AddFileExtensions();
	template <>
	void AddFileExtensions<class Texture2D>();

private:
	void InsertExtension(const std::string& ext, const std::type_index& type);

	std::map<std::string, std::type_index> mAssetExtensions;
};

