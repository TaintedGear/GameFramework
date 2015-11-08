#pragma once

#include "Component.h"
#include "Math.h"

class TransformComponent :
	public Component
{
public:
	TransformComponent();
	virtual ~TransformComponent();

	//Accessors
	Math::Transform Transform() const { return mTransform; }
	void Transform(Math::Transform val) { mTransform = val; }

	void SetLocation(Math::FVector3 val) { mTransform.Location = val; }
	void SetRotation(Math::FVector3 val) { mTransform.Rotation = val; }
	void SetScale(Math::FVector3 val) { mTransform.Scale = val; }

	Math::FVector3 GetLocation()  { return mTransform.Location; }
	Math::FVector3 GetRotation()  { return mTransform.Rotation; }
	Math::FVector3 GetScale()  { return mTransform.Scale; }

protected:
	Math::Transform mTransform;

};

