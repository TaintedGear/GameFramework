#include "RenderingSystem.h"
#include "Log.h"

#include "Texture2D.h"

RenderingSystem::RenderingSystem() :
mRenderer(nullptr),
mRenderOptions(RendererInfo())
{
}

RenderingSystem::~RenderingSystem()
{
	if (mRenderer)
	{
		ShutdownSystem();
	}
}

bool RenderingSystem::StartupSystem(std::shared_ptr<Window> pRenderWindow, const RendererInfo& pRenderInfo)
{
	// Sanity checks
	// We cant stamp over an existing system
	if (mRenderer)
	{
		Log::GetLog().LogCriticalMsg("Renderer already exist");
		return false;
	}

	mRenderer = std::make_shared<Renderer>();
	if (mRenderer == nullptr)
	{
		Log::GetLog().LogCriticalMsg("Renderer failed to be allocated");
		return false;
	}

	if (pRenderWindow == nullptr)
	{
		Log::GetLog().LogCriticalMsg("Render Window is null when creating Rendering system");
		return false;
	}

	SDL_Window* sdlWindow = pRenderWindow->GetSDLWindow();
	if (sdlWindow == nullptr)
	{
		Log::GetLog().LogCriticalMsg("SDL Window is null when creating Rendering system");
		return false;
	}

	if (!mRenderer->CreateRenderer(SDL_CreateRenderer(sdlWindow, -1, pRenderInfo.RenderFlags)))
	{
		Log::GetLog().LogCriticalMsg("Failed to create Renderer!");
		return false;
	}

	if (mRenderer == nullptr)
	{
		Log::GetLog().LogCriticalMsg("Failed to create renderer due to: " + std::string(SDL_GetError()));
		return false;
	}

	mRenderOptions = pRenderInfo;
	SDL_SetRenderDrawColor(
		mRenderer->GetRenderer(),
		mRenderOptions.RenderDrawColour[0],
		mRenderOptions.RenderDrawColour[1],
		mRenderOptions.RenderDrawColour[2],
		mRenderOptions.RenderDrawColour[3]);

	if (!(IMG_Init(mRenderOptions.ImageFlags) & mRenderOptions.ImageFlags))
	{
		Log::GetLog().LogCriticalMsg("Failed to initialize SDL_IMAGE Error: " + std::string(IMG_GetError()));
		return false;
	}

	Log::GetLog().LogCriticalMsg("Created Renderer Successfully");

	return true;
}

void RenderingSystem::ShutdownSystem()
{
}

//------------------------------------------//
// RenderingSystem::GetRendererWeak				
//------------------------------------------//
std::weak_ptr<Renderer> RenderingSystem::GetRendererWeak()
{
	return mRenderer;
}

////------------------------------------------//
//// RenderingSystem::RenderTextureTEST				
////------------------------------------------//
//void RenderingSystem::RenderTextureTEST(std::shared_ptr<class Texture2D> asset)
//{
//	if (asset != nullptr)
//	{
//		SDL_RenderClear(mRenderer->GetRenderer());
//
//		SDL_RenderCopy(mRenderer->GetRenderer(), asset->SDLTexture, 0, 0);
//
//		SDL_RenderPresent(mRenderer->GetRenderer());
//	}
//}
