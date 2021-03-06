#include "AssetMetaDataParser.h"
#include "FileHelper.h"
#include "FilePaths.h"
#include "Intrinsics.h"
#include "Log.h"
#include "XMLParser.h"
#include "AssetDefaultAttributes.h"

// <%s> Tag names
const std::string AssetMetaDataParser::ASSET_TAG = "Asset";
const std::string AssetMetaDataParser::ASSET_NAME_TAG = "Name";
const std::string AssetMetaDataParser::ASSET_TYPE_TAG = "Type";
const std::string AssetMetaDataParser::ASSET_PATH_TAG = "Path";
const std::string AssetMetaDataParser::ASSET_ATTRIBUTE_TAG = "Attributes";
const std::string AssetMetaDataParser::ASSET_SCALAR_ATTRIBUTE_TAG = "Scalar";
const std::string AssetMetaDataParser::ASSET_VECTOR_ATTRIBUTE_TAG = "Vector";

//------------------------------------------//
// AssetMetaDataParser::AssetMetaDataParser				
//------------------------------------------//
AssetMetaDataParser::AssetMetaDataParser() :
mTabLevel(0),
mAssetFileTypeExtensions(nullptr)
{
	mAssetFileTypeExtensions = std::make_unique<AssetFileTypeExtensions>();
}

//------------------------------------------//
// AssetMetaDataParser::~AssetMetaDataParser				
//------------------------------------------//
AssetMetaDataParser::~AssetMetaDataParser()
{

}

//------------------------------------------//
// AssetMetaDataParser::CreateMetaData				
//------------------------------------------//
bool AssetMetaDataParser::CreateMetaData(const std::string& assetFilePath, struct AssetMetaData& metaData)
{
	//Log::GetLog().LogCriticalMsg(assetFilePath);

	// Sanity check string
	if (assetFilePath.length() <= 0)
	{
		//Invalid file path
		// Failed to create meta data for this file path
		Log::GetLog().LogCriticalMsg("AssetFilePath is invalid");
		return false;
	}

	//Grab extension
	// substring the last .*
	const std::string::size_type extDotPos = (assetFilePath.find_last_of('.') + 1); // stop the dot
	if (extDotPos == std::string::npos)
	{
		// Couldnt find the last '.' for the file ext
		Log::GetLog().LogCriticalMsg("Failed to find file ext");
		return false;
	}

	//Run that through the assetFileExt class - if not valid return log
	const std::string ext = assetFilePath.substr(extDotPos);
	if (mAssetFileTypeExtensions == nullptr)
	{
		return false;
	}

	std::size_t typeHash = 0;
	if (!mAssetFileTypeExtensions->ExtensionIsOfAssetType(ext, typeHash))
	{
		// Log invalid asset type
		Log::GetLog().LogCriticalMsg("Asset type is invalid");
		return false;
	}
	if (typeHash == 0)
	{
		Log::GetLog().LogCriticalMsg("Asset type is invalid");
		return false;
	}

	//Grab filename
	const std::string::size_type pathLength = FilePaths::FILE_PATH_ASSETS().length();
	const std::string filename = assetFilePath.substr(
		pathLength,
		//Find string length remaining from filepath then take away the number of chars in the 'ext'
		(assetFilePath.length() - pathLength) - (assetFilePath.length() - (extDotPos - 1)));

	//Grab filepath
	const std::string filepath = assetFilePath.substr(pathLength);

	//From extension create default attributes - TODO
	AssetMetaData newMetaData;
	newMetaData.AssetTypeHash = typeHash;
	newMetaData.AssetName = filename;
	newMetaData.AssetFilePath = filepath;

	metaData = newMetaData;

	return true;
}

//------------------------------------------//
// AssetMetaDataParser::WriteMetaData				
//------------------------------------------//
bool AssetMetaDataParser::WriteMetaDataToFile(
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
		Log::GetLog().LogHighMsg("MetaDataFile is not empty.");
		return false;
	}

	//Begin the XML parsing
	XMLParser parser;
	if (!parser.Parse(metaDataFile))
	{
		return false;
	}

	XMLElement baseElement = parser.CreateNewElement(ASSET_TAG);
	baseElement.CreateChildElement(ASSET_NAME_TAG, metaData.AssetName);
	
	//Determine readable name from TypeHash
	std::string assetType = "Invalid";
	if (!mAssetFileTypeExtensions->HashIsOfAssetTypeName(metaData.AssetTypeHash, assetType))
	{
		//Log that we cant determine type
	}

	baseElement.CreateChildElement(ASSET_TYPE_TAG, assetType);
	baseElement.CreateChildElement(ASSET_PATH_TAG, metaData.AssetFilePath);

	XMLElement attrElement = baseElement.CreateChildElement(ASSET_ATTRIBUTE_TAG);
	XMLElement scalarAttrElement = attrElement.CreateChildElement(ASSET_SCALAR_ATTRIBUTE_TAG);
	XMLElement vectorAttrElement = attrElement.CreateChildElement(ASSET_VECTOR_ATTRIBUTE_TAG);

	AssetScalarAttributeContainer& container = AssetDefaultAttributes<Texture2D>::DefaultScalarAttributes;
	for each (AssetScalarAttribute scalarAttr in container)
	{
		scalarAttrElement.CreateChildElement(scalarAttr.AttributeName, ToString(scalarAttr.AttributeValue));
	}

	//Write the contents of the XML Tree to file
	metaDataFile.Write(parser.GetContents());

	// I WANT TO MEASURE TIME FRAME - THATS WHY COMMENTED CODE IS STAYing
	////Write <Asset>
	//metaDataFile.Write(Tab() + "<" + ASSET_TAG + ">\n");
	//AddTabLevel();

	////Write common data
	//if (!WriteCommonMetaData(metaDataFile, metaData))
	//{
	//	//Log
	//	return false;
	//}

	////Determine Attributes on T or type_index?


	////Write </Asset>
	//RemoveTabLevel();
	//metaDataFile.Write(Tab() + "</" + ASSET_TAG + ">\n");

	return true;
}

//------------------------------------------//
// AssetMetaDataParser::ReadMetaData				
//------------------------------------------//
bool AssetMetaDataParser::ReadMetaDataFromFile(
	class File& metaDataFile,
	struct AssetMetaData& metaData)
{
	//Check file is valid
	if (!CheckMetaDataFileIsValid(metaDataFile))
	{
		return false;
	}

	XMLParser xmlParser;

	if (!xmlParser.Parse(metaDataFile))
	{
		return false;
	}

	XMLElement baseElement = xmlParser.GetFirstElement();
	if (!baseElement.IsValid())
	{
		return false;
	}
	// Check if the base is of <Asset>
	if (baseElement.GetName() != ASSET_TAG)
	{
		return false;
	}
	//Get all the child elements
	std::vector<XMLElement> childElements;
	if (!baseElement.GetAllChildElements(childElements))
	{
		return false;
	}

	for each (XMLElement ele in childElements)
	{
		//Get the Asset Name
		if (ele.GetName() == ASSET_NAME_TAG)
		{
			metaData.AssetName = ele.GetValue();
		} 
		//Get the Asset Filepath
		if (ele.GetName() == ASSET_PATH_TAG)
		{
			metaData.AssetFilePath = ele.GetValue();
		}

		//Get the Asset Type
		if (ele.GetName() == ASSET_TYPE_TAG)
		{
			// Determine type hash
			std::size_t typeHash = 0;
			if (!mAssetFileTypeExtensions->AssetTypeNameIsOfHash(
				ele.GetValue(),
				typeHash))
			{
				return false;
			}

			metaData.AssetTypeHash = typeHash;
		}
	}


	////Read everything between <Asset> and </Asset>
	//// AssetTypeName
	//// AssetName
	//// AssetPath
	//// Attributes
	//// Read <%s>%s</%s>
	//// (Read everything) get the key value <%k> %v </%k> - store into map - then process

	////HARD CODED FOR NWO UNTIL I CAN THINK OF AN ELEGANT SOLOUTION - Just wanna start building a game
	//std::string fileContents;
	//if (!metaDataFile.ReadFileContents(fileContents))
	//{
	//	return false;
	//}

	//if (fileContents.length() <= 0)
	//{
	//	return false;
	//}

	//std::size_t keyStartPos = 0;
	//std::size_t keyEndPos = 0;

	//std::string type = "";
	//std::string name = "";
	//std::string path = "";

	//keyStartPos = fileContents.find("<Type>") + 6;
	//keyEndPos = fileContents.find("</Type>");

	//if (keyStartPos != std::string::npos && keyEndPos != std::string::npos)
	//{
	//	type = fileContents.substr(keyStartPos, (keyEndPos - keyStartPos));
	//}
	//
	//keyStartPos = fileContents.find("<Name>") + 6;
	//keyEndPos = fileContents.find("</Name>");

	//if (keyStartPos != std::string::npos && keyEndPos != std::string::npos)
	//{
	//	name = fileContents.substr(keyStartPos, (keyEndPos - keyStartPos));
	//}

	//keyStartPos = fileContents.find("<Path>") + 6;
	//keyEndPos = fileContents.find("</Path>");

	//if (keyStartPos != std::string::npos && keyEndPos != std::string::npos)
	//{
	//	path = fileContents.substr(keyStartPos, (keyEndPos - keyStartPos));
	//}

	//// Determine type hash
	//std::size_t typeHash = 0;
	//if (!mAssetFileTypeExtensions->AssetTypeNameIsOfHash(type, typeHash))
	//{
	//	return false;
	//}

	//if (typeHash == 0)
	//{
	//	return false;
	//}

	////Fill out info
	//metaData.AssetTypeHash = typeHash;
	//metaData.AssetName = name;
	//metaData.AssetFilePath = path;

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
	metaDataFile.Write(Tab() + "<" + ASSET_TYPE_TAG + ">");

	// Will write out invalid if type hash cant be matched with assettype
	std::string assetName = "Invalid";
	if (!mAssetFileTypeExtensions->HashIsOfAssetTypeName(metaData.AssetTypeHash, assetName))
	{
		//Log that we cant determine type
	}

	metaDataFile.Write(assetName);

	metaDataFile.Write("</" + ASSET_TYPE_TAG + ">\n");

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
	metaDataFile.Write(Tab() + "<" + ASSET_NAME_TAG + ">");

	//Write the filename
	metaDataFile.Write(metaData.AssetName);

	//End name
	metaDataFile.Write("</" + ASSET_NAME_TAG + ">\n");

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
	metaDataFile.Write(Tab() + "<" + ASSET_PATH_TAG + ">");

	metaDataFile.Write(metaData.AssetFilePath);

	//End Path
	metaDataFile.Write("</" + ASSET_PATH_TAG + ">\n");

	return true;
}

//------------------------------------------//
// AssetMetaDataParser::WriteAssetAttributes				
//------------------------------------------//
bool AssetMetaDataParser::WriteAssetAttributes(class File& metaDataFile, const struct AssetMetaData& metaData)
{
	metaDataFile.Write(Tab() + "<" + ASSET_ATTRIBUTE_TAG + ">\n");
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
	metaDataFile.Write(Tab() + "</" + ASSET_ATTRIBUTE_TAG + ">\n");

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






