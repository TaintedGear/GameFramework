#include "AssetMetaDataParser.h"
#include "FileHelper.h"
#include "FilePaths.h"
#include "Log.h"

AssetMetaDataParser::AssetMetaDataParser() :
mTabLevel(0)
{
}

AssetMetaDataParser::~AssetMetaDataParser()
{
}

//------------------------------------------//
// AssetMetaDataParser::WriteMetaData				
//------------------------------------------//
bool AssetMetaDataParser::WriteMetaData(
class File& metaDataFile,
	const struct AssetMetaData& metaData)
{
	if (!CheckMetaDataFileIsValid(metaDataFile))
	{
		return false;
	}

	// Check if the file is new and cleared
	if (metaDataFile.GetFilemode() != File::READ_WRITE_NEW)
	{
		Log::GetLog().LogHighMsg("MetaDataFile is not a empty.");
		return false;
	}

	//Write <Asset>
	metaDataFile.Write(Tab() + "<Asset>\n");
	AddTabLevel();

	//Write common data
	if (!WriteCommonMetaData(metaDataFile, metaData))
	{
		//Log
		return false;
	}

	//Determine Attributes on T or type_index?


	//Write </Asset>
	RemoveTabLevel();
	metaDataFile.Write(Tab() + "</Asset>\n");

	return true;
}

//------------------------------------------//
// AssetMetaDataParser::ReadMetaData				
//------------------------------------------//
bool AssetMetaDataParser::ReadMetaData(
class File& metaDataFile,
struct AssetMetaData& metaData)
{
	return true;
}

//------------------------------------------//
// AssetMetaDataParser::WriteCommonMetaData				
//------------------------------------------//
bool AssetMetaDataParser::WriteCommonMetaData(
class File& metaDataFile,
	const struct AssetMetaData& metaData)
{
	//Check file is valid
	if (!CheckMetaDataFileIsValid(metaDataFile))
	{
		return false;
	}

	// Check if the file is new and cleared
	if (metaDataFile.GetFilemode() != File::READ_WRITE_NEW)
	{
		Log::GetLog().LogHighMsg("MetaDataFile is not a empty.");
		return false;
	}

	//Write AssetType, AssetName, Asset file path>
	if (!WriteAssetType(metaDataFile, metaData))
	{
		return false;
	}
	if (!WriteAssetName(metaDataFile, metaData))
	{
		return false;
	}
	if (!WriteAssetPath(metaDataFile, metaData))
	{
		return false;
	}
	if (!WriteAssetAttributes(metaDataFile, metaData))
	{
		return false;
	}

	return true;
}

//------------------------------------------//
// AssetMetaDataParser::WriteAssetType				
//------------------------------------------//
bool AssetMetaDataParser::WriteAssetType(
class File& metaDataFile,
	const struct AssetMetaData& metaData)
{
	//Write the asset type
	metaDataFile.Write(Tab() + "<Type>");

	metaDataFile.Write(metaData.AssetType != nullptr ? metaData.AssetType->name() : "Invalid");

	metaDataFile.Write("</Type>\n");

	return true;
}

//------------------------------------------//
// AssetMetaDataParser::WriteAssetName				
//------------------------------------------//
bool AssetMetaDataParser::WriteAssetName(
class File& metaDataFile,
	const struct AssetMetaData& metaData)
{
	// Start name
	metaDataFile.Write(Tab() + "<Name>");

	//Write the filename
	metaDataFile.Write(metaData.AssetName);

	//End name
	metaDataFile.Write("</Name>\n");

	return true;
}

//------------------------------------------//
// AssetMetaDataParser::WriteAssetPath				
//------------------------------------------//
bool AssetMetaDataParser::WriteAssetPath(
class File& metaDataFile,
	const struct AssetMetaData& metaData)
{
	// Start Path
	metaDataFile.Write(Tab() + "<Path>");

	metaDataFile.Write(metaData.AssetFilePath);

	//End Path
	metaDataFile.Write("</Path>\n");

	return true;
}

//------------------------------------------//
// AssetMetaDataParser::WriteAssetAttributes				
//------------------------------------------//
bool AssetMetaDataParser::WriteAssetAttributes(class File& metaDataFile, const struct AssetMetaData& metaData)
{
	metaDataFile.Write(Tab() + "<Attributes>\n");
	AddTabLevel();

	// Write the scalar attributes
	const size_t scalarAttributeSize = metaData.ScalarAttributes.size();
	for (unsigned int i = 0; i < scalarAttributeSize; ++i)
	{
		const std::string attributeName = metaData.ScalarAttributes[i].AttributeName;
		const std::string attributeValue = ToString(metaData.ScalarAttributes[i].AttributeValue);
		
		metaDataFile.Write(Tab() + "<" + attributeName + ">\n");
		AddTabLevel();

		metaDataFile.Write(Tab() + "<V>" + attributeValue + "</V>\n");
		RemoveTabLevel();
		metaDataFile.Write(Tab() + "</" + attributeName + ">\n");

	}

	// Write the vector attributes
	const size_t vectorAttributeSize = metaData.VectorAttributes.size();
	for (unsigned int i = 0; i < vectorAttributeSize; ++i)
	{
		const std::string attributeName = metaData.VectorAttributes[i].AttributeName;
		std::string attributeValue = "";

		metaDataFile.Write(Tab() + "<" + attributeName + ">\n");
		AddTabLevel();

		// X
		attributeValue = ToString(metaData.VectorAttributes[i].AttributeValue.x);
		metaDataFile.Write(Tab() + "<X>" + attributeValue + "</X>\n");

		// Y
		attributeValue = ToString(metaData.VectorAttributes[i].AttributeValue.y);
		metaDataFile.Write(Tab() + "<Y>" + attributeValue + "</Y>\n");

		// Z
		attributeValue = ToString(metaData.VectorAttributes[i].AttributeValue.z);
		metaDataFile.Write(Tab() + "<Z>" + attributeValue + "</Z>\n");

		// W
		attributeValue = ToString(metaData.VectorAttributes[i].AttributeValue.w);
		metaDataFile.Write(Tab() + "<W>" + attributeValue + "</W>\n");

		RemoveTabLevel();
		metaDataFile.Write(Tab() + "</" + attributeName + ">\n");
	}

	RemoveTabLevel();
	metaDataFile.Write(Tab() + "</Attributes>\n");

	return true;
}


//------------------------------------------//
// AssetMetaDataParser::CheckMetaDataFileIsValid				
//------------------------------------------//
bool AssetMetaDataParser::CheckMetaDataFileIsValid(
class File& metaDataFile)
{
	//Check file is open
	if (!metaDataFile.IsOpen())
	{
		Log::GetLog().LogHighMsg("MetaDataFile is not open when trying to read or write to it.");
		return false;
	}

	//Check if the file is of type meta data
	const size_t startPos = metaDataFile.GetFilepath().length() -
		FilePaths::META_DATA_FILE_EXT().length();

	if (metaDataFile.GetFilepath().compare(
		startPos,
		metaDataFile.GetFilepath().length(),
		FilePaths::META_DATA_FILE_EXT()) != 0)
	{
		Log::GetLog().LogHighMsg("MetaDataFile is not of a valid metadata file extension.");
		return false;
	}

	return true;
}

//------------------------------------------//
// AssetMetaDataParser::AddTabLevel				
//------------------------------------------//
void AssetMetaDataParser::AddTabLevel()
{
	mTabLevel += 1;
}

//------------------------------------------//
// AssetMetaDataParser::RemoveTabLevel				
//------------------------------------------//
void AssetMetaDataParser::RemoveTabLevel()
{
	mTabLevel -= 1;
}

//------------------------------------------//
// AssetMetaDataParser::Tab				
//------------------------------------------//
const std::string AssetMetaDataParser::Tab()
{
	std::string tab = "";
	for (int i = 0; i < mTabLevel; ++i)
	{
		tab += '\t';
	}

	return tab;
}






