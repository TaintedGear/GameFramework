#pragma once

#include "Timer.h"
class FrameRateTimer :
	public Timer
{
public:
	FrameRateTimer();
	~FrameRateTimer();

	void RegulateFPS(int fps);
};

