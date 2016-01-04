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

	//@Param: pReadData[out] = The read data retreived from file
	bool Read(char* pReadData, int pStartPos, int pEndPos);

	const std::string GetFilepath() const;
	const FileMode GetFilemode() const;
	const bool IsOpen() const;



private:
	std::fstream mFile;
	std::string mFilepath;
	FileMode mFileMode;
};

