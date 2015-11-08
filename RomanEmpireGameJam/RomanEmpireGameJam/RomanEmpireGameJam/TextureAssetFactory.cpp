#include "TextureAssetFactory.h"
#include "Texture.h"

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
	std::shared_ptr<Texture> newTexture;
	newTexture = std::make_shared<Texture>(pFilepath, pFilename);

	if (!mRenderer->LoadTexture(newTexture))
	{
		Log::GetLog().LogCriticalMsg("Failed to create texture asset!");
		return nullptr;
	}

	return newTexture;
}

