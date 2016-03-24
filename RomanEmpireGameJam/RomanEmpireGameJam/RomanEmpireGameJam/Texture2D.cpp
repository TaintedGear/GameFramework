#include "Texture2D.h"
#include "AssetDefaultAttributes.h"

AssetScalarAttributeContainer AssetDefaultAttributes<Texture2D>::DefaultScalarAttributes
{
	AssetScalarAttribute("Come", 1.0f),
	AssetScalarAttribute("At", 5.0f),
	AssetScalarAttribute("Me", 10.0f),
	AssetScalarAttribute("Bro", 0.f)
};

Texture2D::Texture2D()
{
}

Texture2D::~Texture2D()
{
	if (SDLTexture)
	{
		SDL_DestroyTexture(SDLTexture);
	}
}
