#pragma once

#include "PCH.h"
#include "Window.h"
#include "Math.h"

class RenderingSystem
{
public:
	enum RendererFlags { SOFTWARE_RENDERED = SDL_RENDERER_SOFTWARE,
						 HARDWARE_RENDERED = SDL_RENDERER_ACCELERATED,
						 PRESENT_VSYNC = SDL_RENDERER_PRESENTVSYNC,
						 TARGET_TEXTURE = SDL_RENDERER_TARGETTEXTURE };

	enum ImageCompatability {
		IMG_JPG = IMG_INIT_JPG,
		IMG_PNG = IMG_INIT_PNG,
		IMG_TIF = IMG_INIT_TIF,
		IMG_WEBP = IMG_INIT_WEBP,
		IMG_ALL = IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF | IMG_INIT_TIF | IMG_INIT_WEBP
	};

	struct RendererInfo
	{
		int RenderFlags = SOFTWARE_RENDERED;
		int ImageFlags = IMG_ALL;
		// This could be a Uint32 and we just bit shift but for simplicity sake
		Uint8 RenderDrawColour[4];
	};

	RenderingSystem();
	~RenderingSystem();

	bool CreateSystem(std::shared_ptr<Window> pRenderWindow, const RendererInfo& pRenderInfo);
	void DestroySystem();

	//bool LoadTexture(std::shared_ptr<Texture> pTexture);

	RendererInfo GetRenderInfo();

private:
	RendererInfo mRenderOptions;
	SDL_Renderer* mRenderer;
};

