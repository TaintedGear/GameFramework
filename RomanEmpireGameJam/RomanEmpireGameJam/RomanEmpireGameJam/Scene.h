#pragma once

class Scene
{
public:
	Scene();
	virtual ~Scene();

	virtual bool InitializeScene();

	void AddCamera();
	void AddActor();
	void AddPawn();

	bool RemoveCamera();
	bool RemoveActor();


protected:
	//vectors for camera + actor + pawn

private:
};

