#pragma once

#include "PCH.h"

class FileHelper
{
public:
	FileHelper();
	~FileHelper();

	bool CheckFileExists(const std::string& pFilename);

	//************************************
	// Method:    GetAllFilesInFolder
	// FullName:  FileManager::GetAllFilesInFolder
	// Access:    public 
	// Returns:   std::vector<std::string>
	// Qualifier:
	// Parameter: const std::string & pFolderName
	// Parameter: bool bPropergate - Allows to go through sub folders and return those file names
	// Parameter: bool & bResult
	//************************************
	std::vector<std::string> GetAllFilesInFolder(
		const std::string& pFolderName,
		bool bIncludeFolderpath,
		bool& bResult, 
		bool bPropergate = false );

	// Will return all files in the given folder with an ending substring
	std::vector<std::string> GetAllFilesInFolderWithEndingSubstring(
		const std::string& folderName,
		const std::string& endingSubstring,
		bool bIncludeFolderpath,
		bool& bResult,
		bool bPropergate = false );

	// Will return all files in the given folder that dont have an ending substring
	std::vector<std::string> GetAllFilesInFolderWithoutEndingSubstring(
		const std::string& folderName,
		const std::string& endingSubstring,
		bool bIncludeFolderpath,
		bool& bResult,
		bool bPropergate = false);

	bool CheckFolderExists(const std::string& pDirectory);
	bool CreateFolder(const std::string& pDirectory);

	bool FindFilenameFilepathInFolder(
		const std::string& pFolderDir,
		const std::string& pFilename,
		std::vector<std::string>& pMatchingFilepaths);

	// Grab the filepath from a filepath string
	bool SeperateFilePathFromFileName(const std::string& pFullPath, std::string& pFilePath);
	// Grab the filename from the filepath string
	bool SeperateFileNameFromFilePath(const std::string& pFullPath, std::string& pFileName);

private:

};

