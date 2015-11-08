#include <iostream>
#include "PCH.h"

#include "Application.h"
#include "Log.h"

#include "Actor.h"


int main(int argc, char* args[])
{
	//Create the only instance of the App
	Application* mainApp = Application::GetApp();

	if (mainApp == nullptr)
	{
		//Print to output
		Log::GetLog().LogCriticalMsg("Failed to create mainApp");
	}

	if (!mainApp->Initialize())
	{
		Log::GetLog().LogCriticalMsg("Failed to Init mainApp");
	}

	mainApp->Run();

	return 0;
}