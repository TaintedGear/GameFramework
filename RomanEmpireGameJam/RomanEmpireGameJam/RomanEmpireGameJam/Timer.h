#pragma once

//Timer.h

class Timer
{
public:
	Timer();
	virtual ~Timer();

	void Start();
	void Pause();
	void Stop();
	void UnPause();
	float GetTicks();

	bool GetStarted();
	bool GetPaused();

protected:
	int mCurrentTicks;
	int mStartTicks;
	int mPausedTicks;

	bool mStarted;
	bool mPaused;
};