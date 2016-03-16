#pragma once

#include "PCH.h"

//File class

class File
{
public:
	enum FileMode{
		READ = std::ios::in,					
		WRITE = std::ios::out,				
		APPEND = std::ios::app,				
		READ_WRITE = std::ios::in | std::ios::out,
		READ_WRITE_APPEND = std::ios::in | std::ios::out | std::ios::app,
		READ_WRITE_NEW = std::ios::in | std::ios::out | std::ios::trunc
	};
	
	File();
	~File();

	bool Open(const std::string& pFilepath, FileMode pFilemode);
	void Close();

	bool Write(const char* pWriteData);
	bool Write(const std::string& pWriteData);

	//@Param: pReadData[out] = The read data retrieved from file
	bool Read(char* pReadData, const int& pStartPos, const int& pEndPos);
	bool ReadFileContents(std::string& contents);

	bool GetLine(std::string& lineData);

	const std::string GetFilepath() const;
	const std::string GetFileExtension() const;
	const FileMode GetFilemode() const;

	const bool IsOpen() const;

private:
	bool FindFilepathExtension(const std::string& filepath, std::string& fileExt);

	std::fstream	mFile;
	std::string		mFilepath,
					mFileExtension;
	FileMode		mFileMode;
};

