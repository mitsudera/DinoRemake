#pragma once
#include "gameobject.h"

class SceneManager;
class GameEngine;
class CollisionManager;
class CameraComponent;
class PrimitiveComponent;

class Scene
{
public:
	Scene();
	Scene(GameEngine* pGameEngine);
	~Scene();


	virtual void Awake();

	void Init(void);

	void Update();
	void LateUpdate();
	void Draw();
	void Uninit();





	GameEngine* GetGameEngine(void);

	vector <GameObject*>& GetGameObject(void);

	GameObject* GetGameObjectName(string name);

	void AddCamera(CameraComponent* camera);

	float GetSceneTime(void);

	template<class T>
	T* CreateGameObject(void);

	template<class T>
	T* DynamicCreateGameObject(void);

	template<class T>
	T* CreateGameObject(string name);

	template<class T>
	T* DynamicCreateGameObject(string name);

	template<class T>
	T* GetGameObject(void);

	list<Component*>& GetAllComponent(void);
	list<TransformComponent*>& GetAllTransformComponent(void);
	list<PrimitiveComponent*>& GetAllPrimitiveComponent(void);

	void AddSceneComponent(Component* com);
	void AddSceneTransformComponent(TransformComponent* com);
	void AddScenePrimitiveComponent(PrimitiveComponent* com);

	void RemoveSceneComponent(Component* com);
	void RemoveSceneTransformComponent(TransformComponent* com);
	void RemoveScenePrimitiveComponent(PrimitiveComponent* com);

protected:
	GameEngine* pGameEngine;
	vector <GameObject*> gameObjectArray;
	vector<CameraComponent*> cameraArray;
	float sceneTime;
	list<Component*> allComponent;
	list<TransformComponent*> allTransformComponent;
	list<PrimitiveComponent*> allPrimitiveComponent;

};


template<class T>
T* Scene::CreateGameObject(void)
{
	T* obj = new T(this);

	this->gameObjectArray.push_back(obj);

	GameObject* o = dynamic_cast<GameObject*>(obj);
	o->Awake();
	return obj;
}

template<class T>
T* Scene::DynamicCreateGameObject(void)
{
	T* obj = new T(this);

	this->gameObjectArray.push_back(obj);

	GameObject* o = dynamic_cast<GameObject*>(obj);
	o->Awake();
	o->Init();

	return obj;
}
template<class T>
T* Scene::CreateGameObject(string name)
{
	T* obj = new T(this);

	this->gameObjectArray.push_back(obj);

	GameObject* o = dynamic_cast<GameObject*>(obj);
	o->Awake();
	o->SetName(name);
	return obj;
}

template<class T>
T* Scene::DynamicCreateGameObject(string name)
{
	T* obj = new T(this);

	this->gameObjectArray.push_back(obj);

	GameObject* o = dynamic_cast<GameObject*>(obj);
	o->Awake();

	o->Init();

	o->SetName(name);

	return obj;
}

template<class T>
T* Scene::GetGameObject(void)
{
	for (GameObject* obj : gameObjectArray) 
	{
		T* buff = dynamic_cast<T*>(obj);
		if (buff != nullptr)
			return buff;
	}
	return nullptr;

}

