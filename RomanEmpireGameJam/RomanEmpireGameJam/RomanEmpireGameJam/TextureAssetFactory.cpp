#include "TextureAssetFactory.h"
#include "Texture.h"


//------------------------------------------//
// TextureAssetFactoryLoader::TextureAssetFactoryLoader				
//------------------------------------------//
TextureAssetFactoryLoader::TextureAssetFactoryLoader(std::weak_ptr<RenderingSystem> pRenderingSystem)
{
	RenderingSystemWeakRef = pRenderingSystem;
}


TextureAssetFactory::TextureAssetFactory() : AssetFactory(typeid(Texture))
{
	AddExceptedFileExstention("png");
	AddExceptedFileExstention("bmp");
	AddExceptedFileExstention("jpg");
	AddExceptedFileExstention("jpeg");
}

TextureAssetFactory::~TextureAssetFactory()
{

}

//------------------------------------------//
// TextureAssetFactory::CreateAsset				
//------------------------------------------//
std::shared_ptr<Asset> TextureAssetFactory::CreateAsset(const std::string& pFilepath, const std::string& pFilename)
{
	//Check if the weak reference to the rendering system is all good
	if (mFactoryLoader.RenderingSystemRef().lock() == nullptr)
	{
		return nullptr;
	}
	
	std::shared_ptr<Texture> newTexture;
	newTexture = std::make_shared<Texture>(pFilepath, pFilename);

	if (!mFactoryLoader.RenderingSystemRef().lock()->LoadTexture(newTexture))
	{
		Log::GetLog().LogCriticalMsg("Failed to create texture asset!");
		return nullptr;
	}

	return newTexture;
}

//------------------------------------------//
// TextureAssetFactory::InitializeFactory				
//------------------------------------------//
bool TextureAssetFactory::InitializeFactory(AssetFactoryLoader& pAssetFactoryLoader)
{
	//(CHANGE THIS SO THAT WE JUST TAKE A SYSTEM THAT HAS A VIRTUAL LOAD FUNC (REMOVES THE NEEDS TO DOWNCAST)
	mFactoryLoader = static_cast<TextureAssetFactoryLoader&>(pAssetFactoryLoader);
	
	if (mFactoryLoader.RenderingSystemRef().lock() == nullptr)
	{
		//LOG
		return false;
	}

	return true;
}
