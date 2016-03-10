#pragma once

#include "PCH.h"
#include "Window.h"

class Renderer
{
public:
	Renderer();
	~Renderer();

	bool CreateRenderer(SDL_Renderer* renderer);

	SDL_Renderer* GetRenderer() const { return mRenderer; }

private:
	SDL_Renderer* mRenderer;

};

