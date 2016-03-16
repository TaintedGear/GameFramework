#include "AssetDatabase.h"
#include "FileHelper.h"
#include "FilePaths.h"
#include "File.h"
#include "Log.h"

//TEST
#include "Math.h"

AssetDatabase::AssetDatabase()
{
}


AssetDatabase::~AssetDatabase()
{
}

//------------------------------------------//
// AssetDatabase::DiscoverAssets				
//------------------------------------------//
void AssetDatabase::DiscoverAssets()
{
	// Go through the AssetDir find all the files, determine the asset type from the extension
	// Parsers? 
	//mAssetFileExtensions->ExtensionIsOfAssetType("png", typeOfExtension);

	//Grabs all the asset files
	FileHelper fileHelper;
	bool result = false;
	std::vector<std::string> assetFiles = fileHelper.GetAllFilesInFolderWithoutEndingSubstring(
		FilePaths::FILE_PATH_ASSETS(),
		"meta.xml",
		true,
		result,
		true);

	if (!result || assetFiles.size() <= 0)
	{
		Log::GetLog().LogCriticalMsg("Failed to discover any assets");
	}

	for (unsigned int i = 0; i < assetFiles.size(); ++i)
	{
		if (fileHelper.CheckFileExists(assetFiles[i] + ".meta.xml"))
		{
			// Check information of MD and store it
			Log::GetLog().LogLowMsg(assetFiles[i] + " Meta data file exists");
			ReadMetaDataFile(assetFiles[i] + ".meta.xml");
			
		}
		else
		{
			// Create the meta data from the new asset
			if (!CreateMetaDataFile(assetFiles[i]))
			{
			//	Log::GetLog().LogCriticalMsg("Failed to create meta data file for: " + assetFiles[i]);
			}
		}
	}
	
	mAssetMetaData.size();
	
	// Simpler solution:
	// Go through the meta data files check if the path to the file exists - if not then delete the MD
	// If it does exist read the MD data in

	// Would like to do this:
	// Grab the meta data files and check if the file it points to exists - Check if it exists elsewhere
	// if it doest then delete the meta data file, if it does check if it already has a meta data file
	// if not then move that MD file to the new location and update its info

	// Now check for any files that dont have meta data files, and create for them.


	// Store that metadata into a map with a key of the filepath
}

//------------------------------------------//
// AssetDatabase::CreateMetaDataFile				
//------------------------------------------//
bool AssetDatabase::CreateMetaDataFile(
	const std::string& assetFilePath)
{
	// Create the meta data from this file path
	AssetMetaData newMetaData;
	if (!mAssetMetaDataParser.CreateMetaData(assetFilePath, newMetaData))
	{
		return false;
	}

	//Create a new meta data file
	File newAssetMetaDataFile;
	if (!newAssetMetaDataFile.Open(assetFilePath + ".meta.xml", File::READ_WRITE_NEW))
	{
		Log::GetLog().LogCriticalMsg("Failed to create meta data file for: " + assetFilePath);
		return false;
	}

	mAssetMetaDataParser.WriteMetaDataToFile(newAssetMetaDataFile, newMetaData);

	// Check if we already have this
	if (mAssetMetaData.count(newMetaData.AssetFilePath) >= 1)
	{
		return false;
	}

	//Store the metaData to the map
	mAssetMetaData[newMetaData.AssetFilePath] = newMetaData;

	return true;
}

//------------------------------------------//
// AssetDatabase::ReadMetaDataFile				
//------------------------------------------//
bool AssetDatabase::ReadMetaDataFile(
	const std::string& metaDataFilePath)
{
	AssetMetaData newMetaData;

	// Open File
	File metaDataFile;
	if (!metaDataFile.Open(metaDataFilePath, File::READ))
	{
		return false;
	}

	if (!mAssetMetaDataParser.ReadMetaDataFromFile(metaDataFile, newMetaData))
	{
		return false;
	}

	// Check if we already have this
	if (mAssetMetaData.count(newMetaData.AssetFilePath) >= 1)
	{
		return false;
	}

	mAssetMetaData[newMetaData.AssetFilePath] = newMetaData;

	return true;
}

//------------------------------------------//
// AssetDatabase::DoesAssetExist				
//------------------------------------------//
bool AssetDatabase::DoesAssetExist(const std::string& assetPath)
{
	return mAssetMetaData.count(assetPath) >= 1;
}

//------------------------------------------//
// AssetDatabase::GetAssetMetaData				
//------------------------------------------//
bool AssetDatabase::GetAssetMetaData(const std::string& assetPath, AssetMetaData& assetMetaData)
{
	if (mAssetMetaData.count(assetPath) <= 0)
	{
		return false;
	}

	assetMetaData = mAssetMetaData[assetPath];

	return true;
}

