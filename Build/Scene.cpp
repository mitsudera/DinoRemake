#include "Scene.h"
#include "GameEngine.h"
#include "gameobject.h"
#include "CameraComponent.h"
#include "component.h"
#include "transformcomponent.h"

Scene::Scene()
{
}

Scene::Scene(GameEngine* pGameEngine)
{
	this->pGameEngine = pGameEngine;

}

Scene::~Scene()
{

}

void Scene::Init()
{
	sceneTime = 0.0f;


}

void Scene::Update()
{

	for (GameObject* gameObject : GetGameObject())
	{
		if (!gameObject->GetActive())
			continue;
		gameObject->Update();

	}


	for (GameObject* gameObject : GetGameObject())
	{
		if (!gameObject->GetActive())
			continue;

		gameObject->UpdateMatrix();

	}


	sceneTime += pGameEngine->GetDeltaTime();
}

void Scene::Draw()
{

	for (CameraComponent* camera:cameraArray)
	{
		if (!camera->GetActive())
			continue;

		camera->Render();
	}
}

void Scene::Uninit()
{
	for (GameObject* gameObject : GetGameObject())
	{
		gameObject->Uninit();
		delete gameObject;
	}
	gameObjectArray.clear();
	

}

void Scene::InitAllObject(void)
{

	for (GameObject* gameObject : GetGameObject())
	{
		gameObject->Init();

	}

}

GameEngine* Scene::GetGameEngine(void)
{
	return this->pGameEngine;
}

vector<GameObject*>& Scene::GetGameObject(void)
{
	return this->gameObjectArray;
}

GameObject* Scene::GetGameObjectName(string name)
{
	for (GameObject* object:gameObjectArray)
	{
		if (object->GetName() == name)
		{
			return object;

		}

	}
	return nullptr;
}

void Scene::AddCamera(CameraComponent* camera)
{

	this->cameraArray.push_back(camera);
}

float Scene::GetSceneTime(void)
{
	return sceneTime;
}
