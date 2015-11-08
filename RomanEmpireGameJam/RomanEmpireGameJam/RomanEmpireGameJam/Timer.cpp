#include "Timer.h"

#include "PCH.h"

Timer::Timer() : 
mStartTicks(0),
mPausedTicks(0),
mStarted(false),
mPaused(false)
{
	mCurrentTicks = SDL_GetTicks();
}

Timer::~Timer()
{
}

void Timer::Start()
{
	mStarted = true;
	mPaused = false;

	mStartTicks = SDL_GetTicks();
}

void Timer::Stop()
{
	mStarted = false;
	mPaused = false;
}

void Timer::Pause()
{
	if ((mStarted) && (!mPaused))
	{
		mPaused = true;
		mPausedTicks = SDL_GetTicks() - mStartTicks;
	}
}

void Timer::UnPause()
{
	if (mPaused)
	{
		mPaused = false;
		mStartTicks = SDL_GetTicks() - mPausedTicks;
		mPausedTicks = 0;
	}
}

float Timer::GetTicks()
{
	if (mStarted)
	{
		if (mPaused)
		{
			return (float)mPausedTicks;
		}
		else
		{
			return(float) SDL_GetTicks() - mStartTicks;
		}
	}

	return -1.0f;
}

bool Timer::GetStarted()
{
	return mStarted;
}

bool Timer::GetPaused()
{
	return mPaused;
}