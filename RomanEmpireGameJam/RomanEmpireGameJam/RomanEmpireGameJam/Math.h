#pragma once

#include <glm\glm.hpp>

//Typedef alot of the GLM data types for easy use
namespace Math
{
	// Vectors
	typedef glm::fvec2 FVector2;
	typedef glm::fvec3 FVector3;
	typedef glm::fvec4 FVector4;

	typedef glm::u32vec2 IVector2;
	typedef glm::u32vec3 IVector3;
	typedef glm::u32vec4 IVector4;

	struct Transform
	{
		Transform()
		{
			Location = FVector3(0.f, 0.f, 0.f);
			Rotation = FVector3(0.f, 0.f, 0.f);
			Scale = FVector3(0.f, 0.f, 0.f);
		}
		Transform(FVector3 pLocation, FVector3 pRotation, FVector3 pScale)
		{
			Location = pLocation;
			Rotation = pRotation;
			Scale = pScale;
		}

		FVector3 Location;
		FVector3 Rotation;
		FVector3 Scale;
	};
}