#pragma once

#include "PCH.h"
#include "Component.h"
#include "Log.h"
#include "Math.h"
#include "TransformComponent.h"

class Actor
{
public:
	Actor();
	virtual ~Actor();

	//Hold reference for easy use
	TransformComponent* TransformComp;
public:
	template <class T>
	bool AddComponent(const std::string pName) //same names may fuck this up
	{
		std::shared_ptr<Component> newComponent(nullptr);
		newComponent = std::make_shared<T>();
	
		if (newComponent)
		{
			newComponent->Name(pName);
			mComponents.push_back(newComponent);
			return true;
		}

		Log::GetLog().LogMediumMsg("Failed to create component: " + pName);
		return false;
	}

	template <class T>
	T* GetComponent(const std::string pTag)
	{
		for each (std::shared_ptr<Component> comp in mComponents)
		{
			if (comp->Tag() == pTag)
			{
				return static_cast<T*>(comp.get());
			}
		}

		return nullptr;
	}

protected:
	std::vector<std::shared_ptr<Component>> mComponents;
};

