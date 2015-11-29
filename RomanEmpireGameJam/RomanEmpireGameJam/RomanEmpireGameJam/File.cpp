#include "File.h"

File::File() :
mFilepath(""),
mFileMode(FileMode::READ)
{
}

File::~File()
{
}

// Will open an existing file, however if the file does not exist it will create it
//  (Maybe make a separate func to create file)?
bool File::Open(const std::string& pFilepath, File::FileMode pFilemode)
{
	bool retVal = true;

	char openMode = (char)pFilemode;
	
	mFilepath = pFilepath;
	mFileMode = pFilemode;
	mFile.open(pFilepath, pFilemode);
	if (!mFile.is_open())
	{
		//OutputError
		retVal = false;
	}

	return retVal;
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

bool File::Read(char* pReadData, int pStartPos, int pEndPos)
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

std::string File::GetFilepath() const 
{
	return mFilepath;
}

File::FileMode File::GetFilemode() const
{
	return mFileMode;
}