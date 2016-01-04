#include "AssetDatabase.h"
#include "FileHelper.h"
#include "FilePaths.h"
#include "File.h"
#include "Log.h"

#include "AssetMetaDataParser.h"

//TEST
#include "Math.h"

AssetDatabase::AssetDatabase()
{
	mAssetFileExtensions = std::make_unique<AssetFileExtensions>();
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
		result);

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
			// Create meta data file
			CreateMetaDataFile(assetFiles[i]);
		}
	}
	
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
	//Check if this asset is of a valid asset type
	// Check on AssetFileExtensions

	//Create a new meta data file
	File newAssetMetaDataFile;
	newAssetMetaDataFile.Open(assetFilePath + ".meta.xml", File::READ_WRITE_NEW);

	//Create the metaDataStruct
	AssetMetaData testData;
	{
		testData.AssetType = &std::type_index(typeid(AssetMetaData));
		testData.AssetName = "Test";
		testData.AssetFilePath = "SHIT";

		testData.ScalarAttributes.push_back(AssetMetaDataAttribute<float>("Test", 5.f));
		testData.VectorAttributes.push_back(AssetMetaDataAttribute<Math::FVector4>(
			"TestV", Math::FVector4(5.f, 5.f, 0.f, 0.f)));
	}

	//Create the empty attributes depending on type

	AssetMetaDataParser assetMetaDataParser;
	assetMetaDataParser.WriteMetaData(newAssetMetaDataFile, testData);

	return true;
}

//------------------------------------------//
// AssetDatabase::ReadMetaDataFile				
//------------------------------------------//
bool AssetDatabase::ReadMetaDataFile(
	const std::string& metaDataFilePath)
{
	return true;
}
