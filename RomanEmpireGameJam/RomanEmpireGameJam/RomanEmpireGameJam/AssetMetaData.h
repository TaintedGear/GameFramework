#pragma once

#include "PCH.h"
#include "Math.h"

// @Future create a 'Dirty' method if any of this changes so we can serialize back to the metadata file

template< class T >
struct AssetMetaDataAttribute
{
	AssetMetaDataAttribute(const std::string name, const T& value) :
		AttributeName(name),
		AttributeValue(value)
	{

	};

	std::string AttributeName;
	T AttributeValue;
};

struct AssetMetaData
{
	AssetMetaData() :
		AssetTypeHash(-1),
		AssetName(""),
		AssetFilePath("")
	{

	}

	//AssetType - Hash
	size_t AssetTypeHash;
	//AssetName
	std::string AssetName;
	//AssetFilePath
	std::string AssetFilePath;

	//Hold all the scalar attributes
	std::vector<AssetMetaDataAttribute<float>> ScalarAttributes;
	//Holds all the vector attributes
	std::vector<AssetMetaDataAttribute<Math::FVector4>> VectorAttributes;

	//Possibility for adding user defined attributes
};

