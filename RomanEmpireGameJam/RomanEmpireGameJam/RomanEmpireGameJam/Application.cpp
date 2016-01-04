#include "Application.h"

#include "PCH.h"
#include "Log.h"

Application* Application::mApplication = nullptr;

//(MOVE THIS TO INIT when doing window + render + asset)
Application::Application() :
mFrameTimer(nullptr),
mWindow(nullptr)
{
	//Get this application as the singleton
	mApplication = this;

	//Create the frame timer to regulate fps for the child class
	mFrameTimer = std::make_shared<FrameRateTimer>();
	if (mFrameTimer == nullptr)
	{
		//log the error
		Log::GetLog().LogCriticalMsg("Failed to allocate the frame rate timer");
	}

	//Create the window instance
	mWindow = std::make_shared<Window>();
	if (mWindow == nullptr)
	{
		Log::GetLog().LogCriticalMsg("Failed to allocate the window");
	}

	//Create the rendering system instance
	mRenderingSystem = std::make_shared<RenderingSystem>();
	if (mRenderingSystem == nullptr)
	{
		Log::GetLog().LogCriticalMsg("Failed to allocate the rendering system");
	}

	mAssetCacheCollection = std::make_shared<AssetCacheCollection>();
	if (mAssetCacheCollection == nullptr)
	{
		Log::GetLog().LogCriticalMsg("Failed to allocate the AssetCacheCollection");
	}

	mAssetDatabase = std::make_shared<AssetDatabase>();
	if (mAssetDatabase == nullptr)
	{
		Log::GetLog().LogCriticalMsg("Failed to allocate the AssetDatabase");
	}

	//Write verbosity setting
	Log::GetLog().WriteSeperator();

	Log::GetLog().PrintVerbositySetting();

	//Write time + date: etc

	Log::GetLog().WriteSeperator();



}

Application::~Application()
{
	//Maybe log how many references 
}

Application* Application::GetApp()
{
	return(mApplication);
}

void Application::Run()
{
	mFrameTimer->Start();

	//Do game loop
	while (!IsQuitting())
	{
		//Go through the SDL events
		MessagingLoop();

		//Update the elements
		Update();
		Draw();

		mFrameTimer->RegulateFPS(60);
	}
}

void Application::PollQuit()
{
	//Set all the other things that may need to know that we are about to quit the app
	mQuit = true;
}

bool Application::IsQuitting()
{
	bool retVal = false;

	retVal = mQuit;

	return retVal;
}
