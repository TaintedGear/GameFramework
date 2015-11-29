#include "BasicApp.h"
#include "Log.h"

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

	if (!mWindow->CreateWindow(windowInfo))
	{
		Log::GetLog().LogCriticalMsg("Failed to create window");
		return false;
	}

	RenderingSystem::RendererInfo renderingInfo;
	renderingInfo.RenderFlags = RenderingSystem::RendererFlags::HARDWARE_RENDERED;
	for (int i = 0; i < 4; ++i)
	{
		renderingInfo.RenderDrawColour[i] = 0xFF;
	}

	if (!mRenderingSystem->CreateSystem(mWindow, renderingInfo))
	{
		Log::GetLog().LogCriticalMsg("Failed to create rendering system");
		return false;
	}

	if (!mAssetManager->InitializeAssetCache(mRenderingSystem))
	{
		Log::GetLog().LogCriticalMsg("Failed to initialize asset manager");
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

	bool test = false;
	mAssetManager->GetAsset<Texture>("Helmet.png", test);
	mAssetManager->GetAsset<Texture>("Sheild.png", test);
	mAssetManager->GetAsset<Texture>("sword.png", test);

	mAssetManager->GetAsset<Asset>("TEST", test);

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