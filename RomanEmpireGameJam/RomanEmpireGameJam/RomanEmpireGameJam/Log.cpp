#include "Log.h"
#include "FileHelper.h"
#include "FilePaths.h"

//------------------------------------------//
//				 Log::Log				
//------------------------------------------//
Log::Log()
{

	FileHelper fileManager;

	//Create log folder and file if it doest already exist
	if (!fileManager.CheckFolderExists( FilePaths::FILE_PATH_LOG() ))
	{
		fileManager.CreateFolder( FilePaths::FILE_PATH_LOG() );
	}

	// Will create the log file if it doesnt exist
	std::string logFilePath = FilePaths::FILE_PATH_LOG() + "Log.txt";
	mLogFile.Open(logFilePath, File::FileMode::READ_WRITE_NEW);
}

//------------------------------------------//
//				 Log::~Log				
//------------------------------------------//
Log::~Log()
{
	mLogFile.Close();
}

//------------------------------------------//
//				 Log::GetLog				
//------------------------------------------//
Log& Log::GetLog()
{
	static Log log;
	return(log);
}

//------------------------------------------//
//				 Log::Write				
//------------------------------------------//
void Log::Write(const std::string& pWriteData)
{
	const std::string writeDataNewLine = pWriteData + "\n";
	mLogFile.Write(writeDataNewLine.c_str());
}

//------------------------------------------//
//				Log::WriteSeperator				
//------------------------------------------//
void Log::WriteSeperator()
{
	mLogFile.Write("<---------------------------------------------------->\n");
}

//------------------------------------------//
//				Log::LogLowMsg				
//------------------------------------------//
#ifdef _DEBUG
void Log::LogLowMsg(const std::string& pMsg)
{
	if (CheckVerbosity(VerbositySettings::Low))
	{
		Write("Low: " + pMsg);
	}
}
#endif // _DEBUG

//------------------------------------------//
//				Log::LogMediumMsg				
//------------------------------------------//
#ifdef _DEBUG
void Log::LogMediumMsg(const std::string& pMsg)
{
	if (CheckVerbosity(VerbositySettings::Medium))
	{
		Write("Medium: " + pMsg);
	}
}
#endif // _DEBUG

//------------------------------------------//
//				Log::LogHighMsg				
//------------------------------------------//
#ifdef _DEBUG
void Log::LogHighMsg(const std::string& pMsg)
{
	if (CheckVerbosity(VerbositySettings::High))
	{
		Write("High: " + pMsg);
	}
}
#endif // _DEBUG

//------------------------------------------//
//				Log::LogCriticalMsg				
//------------------------------------------//
#ifdef _DEBUG
void Log::LogCriticalMsg(const std::string& pMsg)
{
	if (CheckVerbosity(VerbositySettings::Critical))
	{
		Write("Critical: " + pMsg);
	}
}
#endif // _DEBUG

//------------------------------------------//
//				Log::CheckVerbosity				
//------------------------------------------//
#ifdef _DEBUG
bool Log::CheckVerbosity(const VerbositySettings pVerbosePriority)
{
	if (pVerbosePriority >= C_VERBOSITY)
	{
		return true;
	}
	
	return false;
}
#endif // _DEBUG

//------------------------------------------//
// Log::PrintVerbositySetting				
//------------------------------------------//
void Log::PrintVerbositySetting()
{
	std::string printVerbosity = "Verbosity is set to ";

	switch (C_VERBOSITY)
	{
	case Low:
		printVerbosity += "Low";
		break;
	case Medium:
		printVerbosity += "Medium";
		break;
	case High:
		printVerbosity += "High";
		break;
	case Critical:
		printVerbosity += "Critical";
		break;
	default:
		printVerbosity += "INVALID";
		break;
	}

	Log::Write(printVerbosity);
}
