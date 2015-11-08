#include "FrameRateTimer.h"

#include "PCH.h"

FrameRateTimer::FrameRateTimer()
{
}

FrameRateTimer::~FrameRateTimer()
{
}

void FrameRateTimer::RegulateFPS(int fps)
{
	mCurrentTicks = SDL_GetTicks();

	if (SDL_GetTicks() < 1000 / (unsigned)fps)
	{
		SDL_Delay(((1000 / fps) - SDL_GetTicks()));
	}
}
