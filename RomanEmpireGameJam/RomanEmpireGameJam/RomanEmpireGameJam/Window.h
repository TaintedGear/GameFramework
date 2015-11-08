#pragma once

#include "PCH.h"
#include "Math.h"

class Window
{
public:
	enum WindowFlags{FULLSCREEN = SDL_WINDOW_FULLSCREEN, 
		FULLSCREEN_DESKTOP = SDL_WINDOW_FULLSCREEN_DESKTOP, 
		BORDERLESS_WINDOW = SDL_WINDOW_BORDERLESS, 
		RESIZABLE_WINDOW = SDL_WINDOW_RESIZABLE};

	struct WindowInfo
	{
		std::string windowTitle = "Default";
		int WindowXPos = 0,
			WindowYPos = 0,
			WindowHeight = 0,
			WindowWidth = 0;
		int windowFlags = SDL_WINDOW_FULLSCREEN_DESKTOP;
	};

	Window();
	virtual ~Window();

	bool CreateWindow(const WindowInfo& pWindowInfo);
	void DestroyWindow();

	WindowInfo GetWindowInfo();

	SDL_Window* GetSDLWindow();

private:
	WindowInfo mWindowInfo;
	SDL_Window* mWindow;
};

