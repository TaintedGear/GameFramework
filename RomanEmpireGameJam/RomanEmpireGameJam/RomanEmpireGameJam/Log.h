#pragma once

//Application log
#include "PCH.h"
#include "File.h"

//Types
enum VerbositySettings {
	Low = 0,
	Medium = 1,
	High = 2,
	Critical = 3
};

const VerbositySettings C_VERBOSITY = Low;

// Singleton class: Allows logging to the Log.Txt file with use of verbosity
class Log
{
public:
	Log();
	~Log();

	static Log& GetLog();

#ifdef _DEBUG
	void LogLowMsg(const std::string& pMsg);
	void LogMediumMsg(const std::string& pMsg);
	void LogHighMsg(const std::string& pMsg);
	void LogCriticalMsg(const std::string& pMsg);
#else // _DEBUG
	void LogLowMsg(const std::string& pMsg) {};
	void LogMediumMsg(const std::string& pMsg) {};
	void LogHighMsg(const std::string& pMsg) {};
	void LogCriticalMsg(const std::string& pMsg) {};
#endif // _DEBUG

	void WriteSeperator();
	void PrintVerbositySetting();
private:
	File mLogFile;
	void Write(const std::string& pWriteData);
	bool CheckVerbosity(const VerbositySettings pVerbosePriority);
};

