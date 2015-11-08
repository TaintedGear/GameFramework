#pragma once

#include "PCH.h"
#include "Intrinsics.h"

#if __WINDOWS__
#include <Windows.h>
#endif

namespace FilePaths
{
	static const std::string FILE_PATH_CONTENT()
	{
		return "/Asset/";
	}
	static const std::string FILE_PATH_LOG()
	{
		return "/Log/";
	}

	// Allows me to call this once and never need to do it again
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
}