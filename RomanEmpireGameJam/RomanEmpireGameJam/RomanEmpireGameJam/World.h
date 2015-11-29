#pragma once

#include "PCH.h"
#include "Scene.h"

class THWorld
{
public:
	THWorld();
	~THWorld();

	bool CreateWorld();

public:
	//------------------------------------------//
	// Create Scene <T>				
	//------------------------------------------//
	template< class T >
	std::shared_ptr<T> CreateScene()
	{
		// Fill out with the constructor list when we defined one
		std::shared_ptr<Scene> newScene(nullptr);
		newScene = std::make_shared<T>();

		if (newScene != nullptr)
		{
			//Store the new scene in the array
			mScenes.push_back(newScene);

			//Return the shared ptr and increase the ref count
			return newScene;
		}

		//Return a null ptr to show that we could not create a new scene
		Log::GetLog().LogMediumMsg("Failed to create a new scene");

		return nullptr;
	}

protected:
	//Stores the scenes that this world has
	std::vector<std::shared_ptr<Scene>> mScenes;
};

