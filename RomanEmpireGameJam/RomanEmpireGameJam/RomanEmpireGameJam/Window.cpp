#include "Window.h"

Window::Window() :
mWindow(nullptr),
mWindowInfo(WindowInfo())
{
}

Window::~Window()
{
	if (mWindow)
	{
		DestroyWindow();
	}
}

bool Window::CreateNewWindow(const WindowInfo& pWindowInfo)
{
	bool retVal = false;

	mWindow = SDL_CreateWindow(pWindowInfo.windowTitle.c_str(),
		pWindowInfo.WindowXPos,
		pWindowInfo.WindowYPos,
		pWindowInfo.WindowHeight,
		pWindowInfo.WindowWidth,
		pWindowInfo.windowFlags);

	if (mWindow)
	{
		retVal = true;
	}

	return retVal;
}

void Window::DestroyWindow()
{
	if (mWindow)
	{
		SDL_DestroyWindow(mWindow);
		mWindow = nullptr;
	}
}
//------------------------------------------//
//				Window::GetSDLWindow				
//------------------------------------------//
SDL_Window* Window::GetSDLWindow()
{
	return mWindow;
}
