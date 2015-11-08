#pragma once

#include "PCH.h"
#include "Scene.h"
#include "Actor.h"

class THWorld
{
public:
	THWorld();
	~THWorld();

	bool CreateWorld();

public:
	//------------------------------------------//
	// Spawn Actor <T>				
	//------------------------------------------//
	template< class T >
	std::shared_ptr<T> SpawnActor(Math::Transform pTransform)
	{
		// Fill out with the constructor list when we defined one
		std::shared_ptr<Actor> newActor(nullptr);
		newActor = std::make_shared<T>();

		if (newActor != nullptr)
		{
			//Set starting transform
			newActor->TransformComp->Transform(pTransform);

			//Store the actor in the array
			mPersistantActors.push_back(newActor);

			//Return the ptr and increase the ref count
			return newActor;
		}

		//Return a null ptr to show that we could not spawn an actor
		Log::GetLog().LogMediumMsg("Failed to create a new actor");

		return nullptr;
	}

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

	//Stores every object in this world
	std::vector<std::shared_ptr<Actor>> mPersistantActors;
};

