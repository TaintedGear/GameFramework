#pragma once

//Base Application class
#include "FrameRateTimer.h"
#include "Window.h"
#include "RenderingSystem.h"
#include "AssetCacheCollection.h"
#include "AssetDatabase.h"

class Application
{
public:
	Application();
	virtual ~Application();

	static Application* GetApp();

	//Child implementatable - Maybe have the core systems init from a func called from the constructor?
	virtual bool Initialize() = 0;
	virtual void Shutdown() = 0;

	virtual void Run();

protected:
	void PollQuit();
	bool IsQuitting();

	virtual void MessagingLoop() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	static Application* mApplication;

	std::shared_ptr<class FrameRateTimer> mFrameTimer;
	std::shared_ptr<class Window> mWindow;
	std::shared_ptr<class RenderingSystem> mRenderingSystem;
	std::shared_ptr<class AssetCacheCollection> mAssetCacheCollection;
	std::shared_ptr<class AssetDatabase> mAssetDatabase;

	bool mQuit;
};

