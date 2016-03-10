#include "Texture2D.h"

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
