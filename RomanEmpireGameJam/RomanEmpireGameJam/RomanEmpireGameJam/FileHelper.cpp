#include "FileHelper.h"
#include "Intrinsics.h" //To use FindAndReplace

#include "Log.h"

// Create this to be cross platform in the future - potential to break atm (Maybe expand this so that 
// the file operations are wrapped around platform specific classes )
#if __WINDOWS__
#include <Windows.h>
#endif

FileHelper::FileHelper()
{
}

FileHelper::~FileHelper()
{
}

bool FileHelper::CheckFileExists(const std::string& pFilename)
{
	std::ifstream file(pFilename);
	return file.good();
}

//------------------------------------------//
// FileHelper::GetAllFilesInFolder				
//------------------------------------------//
std::vector<std::string> FileHelper::GetAllFilesInFolder(const std::string& pFolderName, bool& bResult, bool bPropergate /*= false*/)
{
	std::vector<std::string> fileStrings;
	bResult = true;

	//Get all files from folder - windows - code from: http://stackoverflow.com/questions/20860822/finding-the-file-path-of-all-files-in-a-folder
#if __WINDOWS__

	char searchPath[MAX_PATH];

	// Get the search path
	sprintf_s(searchPath, "%s*.*", pFolderName.c_str());

	WIN32_FIND_DATA fileData;
	HANDLE hFind = ::FindFirstFile(searchPath, &fileData);

	if (hFind != INVALID_HANDLE_VALUE)
	{
		do
		{
			if (!(fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
			{
				fileStrings.push_back(pFolderName + fileData.cFileName);
			}
		} while (::FindNextFile(hFind, &fileData));
		::FindClose(hFind);
	}

#endif

	if (fileStrings.size() <= 0)
	{
		bResult = false;
	}

	return fileStrings;
}

//------------------------------------------//
// FileHelper::CheckFolderExists				
//------------------------------------------//
bool FileHelper::CheckFolderExists(const std::string& pDirectory)
{
	//http://stackoverflow.com/questions/8233842/how-to-check-if-directory-exist-using-c-and-winapi
#if __WINDOWS__

	DWORD ftyp = GetFileAttributesA(pDirectory.c_str());
	if (ftyp == INVALID_FILE_ATTRIBUTES)
	{
		return false;  //something is wrong with your path!
	}
	
	if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
	{
		return true;   // this is a directory!
	}
	
#endif

	return false; 
}

//------------------------------------------//
// FileHelper::CreateFolder				
//------------------------------------------//
bool FileHelper::CreateFolder(const std::string& pDirectory)
{
#if __WINDOWS__
	if (CreateDirectory(pDirectory.c_str(), NULL))
	{
		return true;
	}
#endif
	return false;
}

//------------------------------------------//
// FileHelper::FindFilePathInFolder(NOT AS DESCRIBED) -- Can be exspensive if the directory includes alot of children (Also generally expensive with string matching)			
//------------------------------------------//
bool FileHelper::FindFilenameFilepathInFolder(const std::string& pFolderDir, const std::string& pFilename, std::vector<std::string>& pMatchingFilepaths)
{
	bool bResult = true;

	//Get all files from folder - windows - code from: http://stackoverflow.com/questions/20860822/finding-the-file-path-of-all-files-in-a-folder
#if __WINDOWS__

	char searchPath[MAX_PATH];

	// Get the search path
	sprintf_s(searchPath, "%s*.*", pFolderDir.c_str());

	WIN32_FIND_DATA fileData;
	HANDLE hFind = ::FindFirstFile(searchPath, &fileData);

	if (hFind != INVALID_HANDLE_VALUE)
	{
		do
		{
			if (!(fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
			{
				//fileData.pFilename gives the filename not the whole path :( (Need to find a way to recursively check all child folders)
				//std::string fileName = "";
				//if (SeperateFileNameFromFilePath(pFolderDir + pFilename, fileName))
				{
					if (fileData.cFileName == pFilename)
					{
						pMatchingFilepaths.push_back(pFolderDir + fileData.cFileName);
					}
				}
			}

		} while (::FindNextFile(hFind, &fileData));
		::FindClose(hFind);
	}

#endif

	if (pMatchingFilepaths.size() <= 0)
	{
		bResult = false;
	}

	return bResult;
}

//------------------------------------------//
// FileHelper::SeperateFilePathFromFileName				
//------------------------------------------//
bool FileHelper::SeperateFilePathFromFileName(const std::string& pFullPath, std::string& pFilePath)
{
	// Invalid path length
	if (pFullPath.length() <= 0)
	{
		return false;
	}

	//Grab the last '/' or '\' //
	std::string::size_type lastSlash = pFullPath.find_last_of("\\");
	if (lastSlash == std::string::npos)
	{
		//Couldnt find  a \ now try a /
		lastSlash = pFullPath.find_last_of("//");
		if (lastSlash == std::string::npos)
		{
			// couldnt find either / or \ in the string return false
			return false;
		}
	}

	pFilePath = pFullPath.substr(0, lastSlash - 1);
	return true;
}

//------------------------------------------//
// FileHelper::SeperateFileNameFromFilePath				
//------------------------------------------//
bool FileHelper::SeperateFileNameFromFilePath(const std::string& pFullPath, std::string& pFileName)
{
	// Invalid path length
	if (pFullPath.length() <= 0)
	{
		return false;
	}

	//Grab the last '/' or '\' //
	std::string::size_type lastSlash = pFullPath.find_last_of("\\");
	if (lastSlash == std::string::npos)
	{
		//Couldnt find  a \ now try a /
		lastSlash = pFullPath.find_last_of("//");
		if (lastSlash == std::string::npos)
		{
			// couldnt find either / or \ in the string return false
			return false;
		}
	}

	if (lastSlash + 1 >= pFullPath.length())
	{
		//Slash was found at the end of the string
		return false;
	}

	pFileName = pFullPath.substr(lastSlash + 1);

	return true;
}
