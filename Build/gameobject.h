#pragma once
#include "Coreminimal.h"
#include "component.h"
#include "ShaderSet.h"




class ColliderComponent;
class Scene;
class TransformComponent;
class Component;
class MeshData;
class GameEngine;
class ColliderComponent;


class GameObject
{
public:

	enum class ObjectTag:int
	{
		Default,
		Player,
		Enemy,
		Field,

		ObjectTagMax,
	};


	enum class Layer:int
	{
		Default,
		Sky,
		Field,
		Water,
		UI,
		Text,

		LayerMax,
	};

	GameObject();
	GameObject(Scene* scene);
	GameObject(GameObject* parent);
	~GameObject();

	virtual void Awake(void);
	void Init(void);
	void Uninit(void);
	void Update(void);
	void UpdateMatrix(void);
	void Draw(ShaderSet::ShaderIndex index);
	void ShadowMapping(void);
	

	Scene* GetScene(void);
	TransformComponent* GetTransFormComponent(void);

	ObjectTag GetTag(void);
	Layer GetLayer(void);

	BOOL GetActive(void);
	void SetActive(BOOL isActive);

	GameObject* GetParent(void);
	GameObject* GetRootObject(void);

	GameObject* GetChild(int index);
	GameObject* GetChild(string name);
	vector<GameObject*>& GetChild();

	vector<Component*>& GetComponentList(void);

	//指定したアトリビュートを持つコンポーネントの中でn番目のコンポーネントのポインタを取得
	Component* GetComponentAttrbute(Component::Attribute attr, int n);

	template<class T>
	T* GetComponent(void);

	template<class T>
	T* AddComponent(void);



	void SetHasShadowAll(BOOL b);

	GameObject* AddChild(string name);


	string GetName(void);
	void SetName(string name);

	void LoadFbxFileMesh(string fName);

	void LoadMeshNode(MeshData* node);

protected:
	Scene* pScene;
	GameEngine* pGameEngine;
	TransformComponent* transformComponent;

	vector<Component*> componentList;

	string name;
	ObjectTag tag;
	Layer layer;

	

	BOOL isActive;

	GameObject* parent;
	vector <GameObject*> childList;

};



template<class T>
T* GameObject::GetComponent(void)
{
	for (Component* com : componentList) {
		T* buff = dynamic_cast<T*>(com);
		if (buff != nullptr)
			return buff;
	}
	return nullptr;

}

template<class T>
T* GameObject::AddComponent(void)
{
	T* com = new T(this);

	this->componentList.push_back(com);

	Component* c = dynamic_cast<Component*>(com);
	c->Awake();
	return com;
}
