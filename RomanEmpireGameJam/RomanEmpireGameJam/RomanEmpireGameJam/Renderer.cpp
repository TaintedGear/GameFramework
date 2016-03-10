#include "Renderer.h"

Renderer::Renderer() :
mRenderer(nullptr)
{
}

Renderer::~Renderer()
{
	if (mRenderer)
	{
		SDL_DestroyRenderer(mRenderer);
	}
}

//------------------------------------------//
// Renderer::CreateRenderer				
//------------------------------------------//
bool Renderer::CreateRenderer(SDL_Renderer* renderer)
{
	if (renderer == nullptr)
	{
		//Renderer is empty
		return false;
	}

	if (mRenderer != nullptr)
	{
		//We already have one
		return false;
	}

	mRenderer = renderer;
	
	return true;
}
