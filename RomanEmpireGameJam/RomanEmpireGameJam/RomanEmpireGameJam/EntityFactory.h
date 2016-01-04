#pragma once

#include "PCH.h"

//Creates the entitys

class EntityFactory
{
public:
	EntityFactory();
	~EntityFactory();

	template<typename T>
	std::shared_ptr<EntityFactory> CreateEntity()
	{
		// Create the entity

	}

private:
	// To be passed down to all the entitys that are created
	
};

