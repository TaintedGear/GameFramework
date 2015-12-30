#include "TextureAssetLoader.h"
#include "Texture.h"

//------------------------------------------//
// TextureAssetFactoryLoader::TextureAssetFactoryLoader				
//------------------------------------------//
TextureAssetLoaderInjector::TextureAssetLoaderInjector(std::weak_ptr<RenderingSystem> pRenderingSystem)
{
	RenderingSystemWeakRef = pRenderingSystem;
}


TextureAssetLoader::TextureAssetLoader() : AssetLoader(typeid(Texture))
{
	AddExceptedFileExstention("png");
	AddExceptedFileExstention("bmp");
	AddExceptedFileExstention("jpg");
	AddExceptedFileExstention("jpeg");

}

TextureAssetLoader::~TextureAssetLoader()
{

}

//------------------------------------------//
// TextureAssetFactory::CreateAsset				
//------------------------------------------//
bool TextureAssetLoader::LoadAsset(
	const std::string& pFilepath,
	const std::string& pFilename,
	std::shared_ptr<Asset>& pAsset)
{
	//Downcast the asset to make sure we can use it
	std::shared_ptr<Texture> loadAsset = std::static_pointer_cast<Texture>(pAsset);

	//Check if the weak reference to the rendering system is all good
	if (mInjector.RenderingSystemRef().lock() == nullptr)
	{
		return false;
	}

	if (!mInjector.RenderingSystemRef().lock()->LoadTexture(loadAsset))
	{
		Log::GetLog().LogCriticalMsg("Failed to create texture asset!");
		return false;
	}

	return true;
}

//------------------------------------------//
// TextureAssetFactory::InitializeFactory				
//------------------------------------------//
bool TextureAssetLoader::InitializeLoader(const AssetLoaderInjector& pAssetLoaderInjector)
{
	//(CHANGE THIS SO THAT WE JUST TAKE A SYSTEM THAT HAS A VIRTUAL LOAD FUNC (REMOVES THE NEEDS TO DOWNCAST)
	mInjector = static_cast<const TextureAssetLoaderInjector&>(pAssetLoaderInjector);
	
	if (mInjector.RenderingSystemRef().lock() == nullptr)
	{
		//LOG
		return false;
	}

	return true;
}

//------------------------------------------//
// TextureAssetLoader::UnloadAsset				
//------------------------------------------//
void TextureAssetLoader::UnloadAsset(Asset* pAsset)
{
	Log::GetLog().LogCriticalMsg("THIS WAS CALLED!");
}
