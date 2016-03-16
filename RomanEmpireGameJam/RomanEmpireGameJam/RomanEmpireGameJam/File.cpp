#include "File.h"

#include "Intrinsics.h"
#include "Log.h"

// For File::ReadFileContents
#include <streambuf>

File::File() :
mFilepath("")
,mFileExtension("")
,mFileMode(FileMode::READ)
{
}

File::~File()
{
}

// Will open an existing file, however if the file does not exist it will create it
//  (Maybe make a separate func to create file)?
bool File::Open(const std::string& pFilepath, File::FileMode pFilemode)
{
	char openMode = (char)pFilemode;
	
	mFilepath = pFilepath;
	mFileMode = pFilemode;
	if (!FindFilepathExtension(pFilepath, mFileExtension))
	{
		//Couldn't ascertain file ext
		return false;
	}

	mFile.open(pFilepath, pFilemode);
	if (!mFile.is_open())
	{
		//OutputError
		return false;
	}

	return true;
}

void File::Close()
{
	if (mFile.is_open())
	{
		mFile.close();
		mFilepath = "";
		mFileMode = FileMode::READ;
	}
}

bool File::Write(const char* pWriteData)
{
	bool retVal = true;

	if (!mFile.is_open())
	{
		retVal = false;
	}
	else
	{
		std::streamsize writeWidth = 0;
		writeWidth = std::strlen(pWriteData);

		mFile.write(pWriteData, writeWidth);
		if (mFile.bad() || mFile.fail() || mFile.eof())
		{
			retVal = false;
		}
	}

	mFile.flush();

	return retVal;
}

//------------------------------------------//
// File::Write				
//------------------------------------------//
bool File::Write(const std::string& pWriteData)
{
	return Write(pWriteData.c_str());
}

bool File::Read(char* pReadData, const int& pStartPos, const int& pEndPos)
{
	bool retVal = true;

	if (mFile)
	{
		//Get to the correct position in the file
		mFile.seekg(0, pStartPos);
		if (!mFile.bad() || !mFile.fail() || !mFile.eof())
		{
			std::size_t byteSize = 0;
			byteSize = sizeof(char);

			//Read the data
			mFile.read(pReadData, std::strlen(pReadData));
			if (mFile.bad() || mFile.fail() || mFile.eof())
			{
				retVal = false;
			}
		}
		else
		{
			retVal = false;
		}
	}

	return retVal;
}

//------------------------------------------//
// File::GetLine				
//------------------------------------------//
bool File::GetLine(std::string& lineData)
{
	if (mFile)
	{
		if (!mFile.eof())
		{
			std::getline(mFile, lineData);
		}

		return true;
	}

	return false;
}


//------------------------------------------//
// File::GetFilepath				
//------------------------------------------//
const std::string File::GetFilepath() const 
{
	return mFilepath;
}

//------------------------------------------//
// File::GetFileExtension				
//------------------------------------------//
const std::string File::GetFileExtension() const
{
	return mFileExtension;
}

//------------------------------------------//
// File::GetFilemode				
//------------------------------------------//
const File::FileMode File::GetFilemode() const
{
	return mFileMode;
}

//------------------------------------------//
// File::IsOpen				
//------------------------------------------//
const bool File::IsOpen() const
{
	return mFile.is_open();
}

//------------------------------------------//
// File::ReadFileContents				
//------------------------------------------//
bool File::ReadFileContents(std::string& contents)
{
	// THIS IS UNSAFE 
	if (mFile)
	{
		if (File::IsOpen())
		{
			//Bit flag this
			if (mFileMode == 
				READ_WRITE || READ || READ_WRITE_APPEND || READ_WRITE_NEW)
			{
				//Allocate the space for the string
				contents.clear();
				//Go to EOF
				mFile.seekg(0, std::ios::end);
				contents.reserve((std::size_t)mFile.tellg());
				mFile.seekg(0, std::ios::beg);

				//Copy contents over to the string
				contents.assign((std::istreambuf_iterator<char>(mFile)),
					std::istreambuf_iterator<char>());
			}
		}
	}

	return false;
}

//------------------------------------------//
// File::FindFilepathExtension				
//------------------------------------------//
bool File::FindFilepathExtension(const std::string& filepath, std::string& fileExt)
{
	if (filepath.size() <= 0)
	{
		//String is empty
		return false;
	}

	//Find the last '.'
	std::size_t endPos = filepath.find_last_of('.');

	if (endPos == std::string::npos)
	{
		//Failed to find the last '.'
		return false;
	}

	int extLen = (int)filepath.size() - (int)endPos;
	if (extLen <= 0)
	{
		//Ext length was too small
		return false;
	}

	fileExt = filepath.substr(endPos, extLen);

	return true;
}
