#include "RenderingSystem.h"
#include "Log.h"

RenderingSystem::RenderingSystem() :
mRenderer(nullptr),
mRenderOptions(RendererInfo())
{
}

RenderingSystem::~RenderingSystem()
{
	if (mRenderer)
	{
		DestroySystem();
	}
}

bool RenderingSystem::CreateSystem(std::shared_ptr<Window> pRenderWindow, const RendererInfo& pRenderInfo)
{
	// Sanity checks
	// We cant stamp over an existing system
	if (mRenderer)
	{
		Log::GetLog().LogHighMsg("Renderer already exist when trying to create a new render");
		return false;
	}

	if (pRenderWindow == nullptr)
	{
		Log::GetLog().LogHighMsg("Render Window is null when creating Rendering system");
		return false;
	}

	SDL_Window* sdlWindow = pRenderWindow->GetSDLWindow();
	if (sdlWindow == nullptr)
	{
		Log::GetLog().LogHighMsg("SDL Window is null when creating Rendering system");
		return false;
	}

	mRenderer = SDL_CreateRenderer(sdlWindow, -1, pRenderInfo.RenderFlags);
	if (mRenderer == nullptr)
	{
		Log::GetLog().LogHighMsg("Failed to create renderer due to: " + std::string(SDL_GetError()));
		return false;
	}

	mRenderOptions = pRenderInfo;
	SDL_SetRenderDrawColor(
		mRenderer,
		mRenderOptions.RenderDrawColour[0],
		mRenderOptions.RenderDrawColour[1],
		mRenderOptions.RenderDrawColour[2],
		mRenderOptions.RenderDrawColour[3]);

	if (!(IMG_Init(mRenderOptions.ImageFlags) & mRenderOptions.ImageFlags))
	{
		Log::GetLog().LogHighMsg("Failed to initialize SDL_IMAGE Error: " + std::string(IMG_GetError()));
		return false;
	}

	Log::GetLog().LogHighMsg("Created Renderer Successfully");

	return true;
}

void RenderingSystem::DestroySystem()
{
	if (mRenderer)
	{
		SDL_DestroyRenderer(mRenderer);
		mRenderer = nullptr;
	}
}

//------------------------------------------//
// RenderingSystem::LoadTexture				
//------------------------------------------//
bool RenderingSystem::LoadTexture(std::shared_ptr<Texture> pTexture)
{
	//Sanity check
	if (pTexture->AssetFilePath().length() <= 0) //Check if the asset path is valid
	{
		Log::GetLog().LogHighMsg("Failed to load texture asset due to invalid path");
		return false;
	}

	//Load the texture from asset path - EXPAND THIS TO INCLUDE BMP's (Unless IMG does it)
	SDL_Surface* loadedSurface = nullptr;
	loadedSurface = IMG_Load(pTexture->AssetFilePath().c_str());
	if (loadedSurface == nullptr)
	{
		Log::GetLog().LogHighMsg("Failed to load texture asset due to: "
			+ std::string(SDL_GetError()) 
			+ " " + std::string(IMG_GetError()) 
			+ " at: "
			+ pTexture->AssetFilePath());
		return false;
	}

	// Create the new texture
	SDL_Texture* newTexture = nullptr;
	newTexture = SDL_CreateTextureFromSurface(mRenderer, loadedSurface);
	if (newTexture == nullptr)
	{
		Log::GetLog().LogHighMsg("Failed to create new texture asset due to :"
			+ std::string(SDL_GetError())
			+ " at: " 
			+ pTexture->AssetFilePath());

		//Free surface
		SDL_FreeSurface(loadedSurface);

		return false;
	}

	SDL_FreeSurface(loadedSurface);

	if (!pTexture->Create(newTexture))
	{
		Log::GetLog().LogHighMsg("Texture failed to create internally at: "
			+ pTexture->AssetFilePath());
		return false;
	}

	return true;
}
