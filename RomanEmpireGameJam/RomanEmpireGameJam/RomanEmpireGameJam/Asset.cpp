#include "Asset.h"

Asset::Asset(const std::string& pAssetFilepath, const std::string& pAssetFilename)
	:
	mAssetFilePath(pAssetFilepath)
	, mAssetFileName(pAssetFilename)
{
}

Asset::~Asset()
{
	Release();
}

//------------------------------------------//
// Asset::Create				
//------------------------------------------//
bool Asset::Create()
{
	return false;
}

//------------------------------------------//
// Asset::Release				
//------------------------------------------//
void Asset::Release()
{

}
