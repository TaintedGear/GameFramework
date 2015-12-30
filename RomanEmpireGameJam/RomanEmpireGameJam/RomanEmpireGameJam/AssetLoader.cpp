#include "AssetLoader.h"

#include "FileHelper.h"
#include "FilePaths.h"
#include "Intrinsics.h"

AssetLoader::AssetLoader(const std::type_index& pAssetType)
	:
mAssetType(pAssetType)
{
}

AssetLoader::~AssetLoader()
{
	ShutdownLoader();
}

//------------------------------------------//
// AssetFactory::AddExceptedFileExstention				
//------------------------------------------//
void AssetLoader::AddExceptedFileExstention(const std::string& pFileExtension)
{
	mAssetAcceptedFileExtension.push_back(pFileExtension);
}

//------------------------------------------//
// AssetFactory::CheckFilenameIsValidWithFileExtensions				
//------------------------------------------//
bool AssetLoader::CheckFilenameIsValidWithFileExtensions(const std::string& pFilename)
{
	//Get everything passed the .
	std::string::size_type dotPos = pFilename.find_last_of('.');
	if (dotPos == std::string::npos)
	{
		Log::GetLog().LogHighMsg(pFilename + " is an invalid filename when creating an asset");
		return false;
	}

	std::string extension = pFilename.substr(dotPos + 1);

	for each (std::string acceptedExtension in mAssetAcceptedFileExtension)
	{
		if (acceptedExtension == extension)
		{
			return true;
		}
	}

	Log::GetLog().LogHighMsg( extension + " is not in the acceptedExtension list for this asset factory!" );
	return false;
}

//------------------------------------------//
// AssetFactory::GetAssetFilepath				
//------------------------------------------//
bool AssetLoader::GetAssetFilepath(const std::string& pFilename, std::string& pFilepath)
{
	//Find the filepath to the filename - (Look at alternative for this)
	FileHelper fileHelper;

	std::string contentDir = FilePaths::PROJECT_PATH() + FilePaths::FILE_PATH_CONTENT();
	std::vector<std::string> filePathsForFilename;

	if (!fileHelper.FindFilenameFilepathInFolder(contentDir, pFilename, filePathsForFilename))
	{
		Log::GetLog().LogHighMsg(
			"Asset could not be found with filename: "
			+ pFilename +
			" it could be spelled wrong or not in the content directory: " +
			FilePaths::PROJECT_PATH() + FilePaths::FILE_PATH_CONTENT());

		return false;
	}

	//log warning if count > 1 but use one of them
	if (filePathsForFilename.size() <= 0)
	{
		Log::GetLog().LogHighMsg(
			"Asset could not be found with filename: "
			+ pFilename +
			" it could be spelled wrong or not in the content directory: " +
			FilePaths::PROJECT_PATH() + FilePaths::FILE_PATH_CONTENT());

		return false;
	}

	if (filePathsForFilename.size() > 1)
	{
		Log::GetLog().LogMediumMsg(
			"Warning: " +
			ToString((int)filePathsForFilename.size()) +
			" Was found at that location using the first found!");
	}

	pFilepath = filePathsForFilename[0];

	return true;
}

//------------------------------------------//
// AssetFactory::ShutdownFactory				
//------------------------------------------//
void AssetLoader::ShutdownLoader()
{
	//Go through each loaded asset and release them (If any still have ref count then handle differently?)
}

//------------------------------------------//
// AssetFactory::InitializeFactory				
//------------------------------------------//
bool AssetLoader::InitializeLoader(const AssetLoaderInjector& pAssetFactoryLoader)
{
	return true;
}


