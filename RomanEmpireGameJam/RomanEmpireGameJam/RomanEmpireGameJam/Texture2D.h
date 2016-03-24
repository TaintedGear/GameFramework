#pragma once

#include "Asset.h"
#include "PCH.h"

//Fillout the default attributes

class Texture2D : public Asset
{
public:
	Texture2D();
	virtual ~Texture2D();

	SDL_Texture* SDLTexture;
};

