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
std::shared_ptr<Asset> TextureAssetLoader::CreateAsset(const std::string& pFilepath, const std::string& pFilename)
{
	//Check if the weak reference to the rendering system is all good
	if (mInjector.RenderingSystemRef().lock() == nullptr)
	{
		return nullptr;
	}
	
	std::shared_ptr<Texture> newTexture;
	newTexture = std::make_shared<Texture>(pFilepath, pFilename);

	if (!mInjector.RenderingSystemRef().lock()->LoadTexture(newTexture))
	{
		Log::GetLog().LogCriticalMsg("Failed to create texture asset!");
		return nullptr;
	}

	return newTexture;
}

//------------------------------------------//
// TextureAssetFactory::InitializeFactory				
//------------------------------------------//
bool TextureAssetLoader::InitializeLoader(AssetLoaderInjector& pAssetLoaderInjector)
{
	//(CHANGE THIS SO THAT WE JUST TAKE A SYSTEM THAT HAS A VIRTUAL LOAD FUNC (REMOVES THE NEEDS TO DOWNCAST)
	mInjector = static_cast<TextureAssetLoaderInjector&>(pAssetLoaderInjector);
	
	if (mInjector.RenderingSystemRef().lock() == nullptr)
	{
		//LOG
		return false;
	}

	return true;
}
