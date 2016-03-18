#include "BasicApp.h"
#include "Log.h"

////Testing
//#include "File.h"
//#include "FilePaths.h"
//#include "XMLParser.h"

//Create an instance for the application
BasicApp appInstance;

BasicApp::BasicApp() :
mWorld(nullptr)
{
}

BasicApp::~BasicApp()
{
}

bool BasicApp::Initialize()
{
	//Setup the window
	if (mWindow == nullptr)
	{
		return false;
	}

	Window::WindowInfo windowInfo;
	windowInfo.WindowXPos = 50;
	windowInfo.WindowYPos = 50;
	windowInfo.WindowHeight = 800;
	windowInfo.WindowWidth = 600;

	windowInfo.windowTitle = "The Legion";
	windowInfo.windowFlags = Window::WindowFlags::RESIZABLE_WINDOW;

	if (!mWindow->CreateNewWindow(windowInfo))
	{
		Log::GetLog().LogCriticalMsg("Failed to create window");
		return false;
	}

	RenderingSystem::RendererInfo renderingInfo;
	renderingInfo.RenderFlags = RenderingSystem::RendererFlags::HARDWARE_RENDERED;
	
	//Change this to use just base colour
	for (int i = 0; i < 4; ++i)
	{
		renderingInfo.RenderDrawColour[i] = 0xFF;
	}

	if (!mRenderingSystem->StartupSystem(mWindow, renderingInfo))
	{
		Log::GetLog().LogCriticalMsg("Failed to create rendering system");
		return false;
	}

	mAssetDatabase->DiscoverAssets();

	if (!mAssetCacheCollection->InitilizeAssetCollection(mRenderingSystem->GetRendererWeak(),
		mAssetDatabase))
	{
		Log::GetLog().LogCriticalMsg("Failed to initialize the asset cache collection");
		return false;
	}

	//Create the first world object
	mWorld = std::make_shared<THWorld>();
	if (mWorld == nullptr)
	{
		Log::GetLog().LogCriticalMsg("Failed to allocate the world");
		return false;
	}

	// Create the world
	if (!mWorld->CreateWorld() )
	{
		Log::GetLog().LogCriticalMsg("Failed to create world");
		return false;
	}

	//File testFile;
	//testFile.Open(FilePaths::FILE_PATH_ASSETS() + "Testing.xml", File::READ_WRITE_NEW);
	////testFile.Open(FilePaths::FILE_PATH_ASSETS() + "Test.xml");

	//XMLParser parser;
	//parser.Parse(testFile);

	//XMLElement firstEle = parser.GetFirstElement();

	//XMLElement newEle = parser.CreateNewElement("Asset");
	//newEle.CreateChildElement("Type", "Texture2D");
	//newEle.CreateChildElement("Name", "Shield");
	//newEle.CreateChildElement("Path", "Shield.png");

	//testFile.Write(parser.GetContents());

	return true;
}

void BasicApp::Shutdown()
{

}

void BasicApp::MessagingLoop()
{
	SDL_Event sdlEvent;

	while (SDL_PollEvent(&sdlEvent))
	{
		if (sdlEvent.type == SDL_QUIT)
		{
			Application::PollQuit();
		}
	}
}

void BasicApp::Update()
{
	
}

void BasicApp::Draw()
{
}