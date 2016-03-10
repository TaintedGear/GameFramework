#include "Texture2DAssetLoader.h"
#include "PCH.h"
#include "FilePaths.h"
#include "Log.h"
#include "Renderer.h"

Texture2DAssetLoader::Texture2DAssetLoader() : AssetLoader<Texture2D>()
{

}

Texture2DAssetLoader::~Texture2DAssetLoader()
{
}

//------------------------------------------//
// Texture2DAssetLoader::StartupLoader				
//------------------------------------------//
bool Texture2DAssetLoader::StartupLoader(std::weak_ptr<class Renderer> renderer)
{
	if (renderer.lock() == nullptr)
	{
		//Fail something
		return false;
	}

	mWeakRenderer = renderer;
	return true;
}


//------------------------------------------//
// Texture2DAssetLoader::LoadAsset				
//------------------------------------------//
bool Texture2DAssetLoader::LoadAsset(std::shared_ptr<Texture2D> unloadedAsset)
{
	//Check if the the renderer we have is still valid
	if (mWeakRenderer.expired())
	{
		// Renderer expired
		return false;
	}

	//Grab the metadata from the asset
	//Sanity check the metadata

	if (unloadedAsset->MetaData.AssetFilePath.length() <= 0)
	{
		Log::GetLog().LogHighMsg("Failed to load texture asset due to invalid path");
		return false;
	}

	//Load the texture from asset path - EXPAND THIS TO INCLUDE BMP's (Unless IMG does it)
	SDL_Surface* loadedSurface = nullptr;
	std::string fullAssetPath = FilePaths::FILE_PATH_ASSETS() + unloadedAsset->MetaData.AssetFilePath;
	
	loadedSurface = IMG_Load(fullAssetPath.c_str());
	if (loadedSurface == nullptr)
	{
		Log::GetLog().LogHighMsg("Failed to load texture asset due to: "
			+ std::string(SDL_GetError())
			+ " " + std::string(IMG_GetError())
			+ " at: "
			+ unloadedAsset->MetaData.AssetFilePath);
		return false;
	}

	// Create the new texture
	SDL_Texture* newTexture = nullptr;
	newTexture = SDL_CreateTextureFromSurface(mWeakRenderer.lock()->GetRenderer(), loadedSurface);
	if (newTexture == nullptr)
	{
		Log::GetLog().LogHighMsg("Failed to create new texture asset due to :"
			+ std::string(SDL_GetError())
			+ " at: "
			+ unloadedAsset->MetaData.AssetFilePath);

		//Free surface
		SDL_FreeSurface(loadedSurface);

		return false;
	}

	// Free the old surface
	SDL_FreeSurface(loadedSurface);

	// Assign the texture to the asset
	unloadedAsset->SDLTexture = newTexture;

	// Check if the texture is still null
	if (unloadedAsset->SDLTexture == nullptr)
	{
		Log::GetLog().LogHighMsg("Texture failed to create internally at: "
			+ unloadedAsset->MetaData.AssetFilePath);
		return false;
	}

	return true;
}

//------------------------------------------//
// Texture2DAssetLoader::UnloadAsset				
//------------------------------------------//
void Texture2DAssetLoader::UnloadAsset(Texture2D* asset)
{
	Log::GetLog().LogCriticalMsg("WE are in the texture2D asset Loader unload function");

	if (asset->SDLTexture)
	{
		SDL_DestroyTexture(asset->SDLTexture);
	}
}

