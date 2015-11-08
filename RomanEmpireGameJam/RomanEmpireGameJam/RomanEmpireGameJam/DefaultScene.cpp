#include "DefaultScene.h"

DefaultScene::DefaultScene()
{
}

DefaultScene::~DefaultScene()
{
}

bool DefaultScene::InitializeScene()
{
	Scene::AddCamera();

	return true;
}