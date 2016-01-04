#pragma once

#include "PCH.h"
#include "Intrinsics.h"

#if __WINDOWS__
#include <Windows.h>
#endif

namespace FilePaths
{
	// Allows me to call this once and never need to do it again - confirm this
	static const std::string PROJECT_PATH()
	{
		static std::string projectPath("");

		if (projectPath == "")
		{
			//http://stackoverflow.com/questions/875249/how-to-get-current-directory
#if __WINDOWS__

			char currentDir[MAX_PATH];
			GetCurrentDirectory(MAX_PATH, currentDir);
			projectPath = currentDir;

			//Replace \\ with /
			FindAndReplace(projectPath, "\\", "/", 0, (projectPath.length() - 1));
#endif
		}

		return projectPath;
	}

	static const std::string FILE_PATH_ASSETS()
	{
		return PROJECT_PATH() + "/Asset/";
	}
	static const std::string FILE_PATH_LOG()
	{
		return PROJECT_PATH() + "/Log/";
	}

	static const std::string META_DATA_FILE_EXT()
	{
		return "meta.xml";
	}
}