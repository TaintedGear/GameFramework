#include "Actor.h"

Actor::Actor()
{
	// Add component - keep reference to it for easy use
	Actor::AddComponent<TransformComponent>("Transform");
	TransformComp = Actor::GetComponent<TransformComponent>("Transform");
}

Actor::~Actor()
{
}

