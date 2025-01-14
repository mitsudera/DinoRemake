#include "Scene.h"
#include "GameEngine.h"
#include "gameobject.h"
#include "CameraComponent.h"
#include "component.h"
#include "transformcomponent.h"
#include "SoundEngine.h"
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

void Scene::Awake()
{
	sceneTime = 0.0f;


}

void Scene::Init(void)
{
	for (Component* com : allComponent)
	{

		com->Init();

	}

}

void Scene::FixedUpdate()
{
	for (Component* com : allComponent)
	{
		if (!com->GetActive())
			continue;

		com->FixedUpdate();

	}

	for (TransformComponent* com : allTransformComponent)
	{
		if (!com->GetActive())
			continue;

		com->UpdateMatrix();

	}



}

void Scene::FixedLateUpdate()
{
	for (Component* com : allComponent)
	{
		if (!com->GetActive())
			continue;

		com->FixedLateUpdate();

	}

	for (TransformComponent* com : allTransformComponent)
	{
		if (!com->GetActive())
			continue;

		com->UpdateMatrix();

	}

}

void Scene::Update()
{


	for (Component* com :allComponent)
	{
		if (!com->GetActive())
			continue;

		com->Update();

	}

	for (TransformComponent* com :allTransformComponent)
	{
		if (!com->GetActive())
			continue;

		com->UpdateMatrix();

	}


	sceneTime += pGameEngine->GetDeltaTime();
}

void Scene::LateUpdate()
{
	for (Component* com : allComponent)
	{
		if (!com->GetActive())
			continue;

		com->LateUpdate();

	}

	for (TransformComponent* com : allTransformComponent)
	{
		if (!com->GetActive())
			continue;

		com->UpdateMatrix();

	}

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
	this->pGameEngine->GetSoundEngine()->StopAllSound();

	for (GameObject* gameObject : GetGameObject())
	{
		gameObject->Destroy();
		delete gameObject;
	}
	gameObjectArray.clear();
	cameraArray.clear();
	allComponent.clear();
	allTransformComponent.clear();
	allPrimitiveComponent.clear();
	allRigidBodyComponent.clear();
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

list<Component*>& Scene::GetAllComponent(void)
{
	return allComponent;
}

list<TransformComponent*>& Scene::GetAllTransformComponent(void)
{
	return allTransformComponent;
}

list<PrimitiveComponent*>& Scene::GetAllPrimitiveComponent(void)
{
	return allPrimitiveComponent;
}

list<RigidBodyComponent*>& Scene::GetAllRigidBodyComponent(void)
{
	return allRigidBodyComponent;
}

void Scene::AddSceneComponent(Component* com)
{
	this->allComponent.push_back(com);
}

void Scene::AddSceneTransformComponent(TransformComponent* com)
{
	this->allTransformComponent.push_back(com);
}

void Scene::AddScenePrimitiveComponent(PrimitiveComponent* com)
{
	this->allPrimitiveComponent.push_back(com);
}

void Scene::AddSceneRigidBodyComponent(RigidBodyComponent* com)
{
	this->allRigidBodyComponent.push_back(com);
}

void Scene::RemoveSceneComponent(Component* com)
{
	allComponent.remove(com);
}

void Scene::RemoveSceneTransformComponent(TransformComponent* com)
{
	allTransformComponent.remove(com);
}

void Scene::RemoveScenePrimitiveComponent(PrimitiveComponent* com)
{
	allPrimitiveComponent.remove(com);
}

void Scene::RemoveSceneRigidBodyComponent(RigidBodyComponent* com)
{
	allRigidBodyComponent.remove(com);
}
