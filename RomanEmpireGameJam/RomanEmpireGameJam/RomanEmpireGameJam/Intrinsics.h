#pragma once

#include "PCH.h"

//-------------------------------------------------------------------------
//	ToStringFuncs
//-------------------------------------------------------------------------

// Allows a value to convert to string
inline std::string ToString(const int& pInt)
{
	return std::to_string((float)pInt);
}
// Allows a value to convert to string
inline std::string ToString(const float& pfloat)
{
	return std::to_string(pfloat);
}
// Allows a value to convert to string: Warning this rounds down to float (May incur inaccuracy when logging)
inline std::string ToString(const double& pDouble)
{
	return std::to_string((float)pDouble);
}
// Allows a bool to convert to string
inline std::string ToString(const bool& pBool)
{
	return pBool ? "True" : "False";
}


//-------------------------------------------------------------------------
//	BuildStringFuncs
//-------------------------------------------------------------------------

// Wrap a class name around a string for ease of logging
inline std::string BuildStringClass(
	const std::type_index& pTypeIndex,
	const std::string& pPrefix = "",
	const std::string& pSuffix = "")
{
	std::string newString = (pPrefix + pTypeIndex.name() + pSuffix);
	return newString;
}

// Wrap a in value around a string for ease of logging
inline std::string BuildStringInt(
	const int& pInt,
	const std::string& pPrefix = "",
	const std::string& pSuffix = "")
{
	std::string newString = (pPrefix + ToString(pInt) + pSuffix);
	return newString;
}

// Wrap a in value around a string for ease of logging
inline std::string BuildStringFloat(
	const float& pFloat,
	const std::string& pPrefix = "",
	const std::string& pSuffix = "")
{
	std::string newString = (pPrefix + ToString(pFloat) + pSuffix);
	return newString;
}

// Wrap a in value around a string for ease of logging
inline std::string BuildStringBool(
	const bool& pBool,
	const std::string& pPrefix = "",
	const std::string& pSuffix = "")
{
	std::string newString = (pPrefix + ToString(pBool) + pSuffix);
	return newString;
}

//-------------------------------------------------------------------------
//	GetLineAndFileInfo
//-------------------------------------------------------------------------

inline std::string GetLineAndFileInfo()
{
	std::string FileInfo(__FILE__);
	std::string LineInfo(ToString(__LINE__));

	return std::string(" File: " + FileInfo + " Line: " + LineInfo);
}

//-------------------------------------------------------------------------
//	FindAndReplace
//-------------------------------------------------------------------------

inline bool FindAndReplace(std::string& pSourceString,
	const std::string pFindString,
	const std::string pReplaceString,
	const std::string::size_type pStart,
	const std::string::size_type pEnd)
{
	//Sanity Check
	if (pStart < 0 || pStart > pEnd || pStart > (pSourceString.length() - 1) ||
		pEnd < 0 || pEnd < pStart || pEnd >(pSourceString.length() - 1))
	{
		return false;
	}

	std::string::size_type pos = pStart;
	while (true)
	{
		pos = pSourceString.find(pFindString, pos);

		if (pos == std::string::npos || pos >= pEnd)
		{
			break;
		}

		pSourceString.replace(pos, pReplaceString.length(), pReplaceString);
	};

	return true;
}
