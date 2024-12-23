#include "gameobject.h"
#include "GameEngine.h"
#include "transformcomponent.h"
#include "Scene.h"
#include "ColliderComponent.h"
#include "component.h"
#include "primitivecomponent.h"
#include "AssetsManager.h"
#include "MeshData.h"
#include "MeshComponent.h"
#include "Material.h"

GameObject::GameObject()
{
	pScene =nullptr;
	this->transformComponent = new TransformComponent(this);
	this->componentList.push_back(transformComponent);

	tag = ObjectTag::Default;

}


GameObject::GameObject(Scene* scene)
{
	this->parent = nullptr;
	this->pScene = scene;
	tag = ObjectTag::Default;

	this->layer = Layer::Default;


	this->transformComponent = new TransformComponent(this);
	this->componentList.push_back(transformComponent);

}

GameObject::GameObject(GameObject* parent)
{

	this->parent = parent;
	this->pScene = parent->GetScene();
	this->tag = parent->GetTag();

	this->layer = parent->GetLayer();

	this->transformComponent = new TransformComponent(this);
	this->componentList.push_back(transformComponent);
}

GameObject::~GameObject()
{
	Uninit();
}

void GameObject::Awake(void)
{
	this->pGameEngine = pScene->GetGameEngine();
	this->isActive = TRUE;
	this->transformComponent->Awake();

}

void GameObject::Init(void)
{
	this->transformComponent->Init();

	for (Component* com : componentList)
	{
		com->Init();
	}
	for (GameObject* obj : childList)
	{
		obj->Init();
	}

}

void GameObject::Uninit(void)
{
	for (int i = 0; i < this->componentList.size(); i++)
	{
		componentList[i]->Uninit();
		delete componentList[i];
	}
	this->componentList.clear();

	for (int i = 0; i < childList.size(); i++)
	{
		childList[i]->Uninit();
		delete childList[i];

	}
	this->childList.clear();
}

void GameObject::Update(void)
{
	if (!isActive)
		return;

	for (Component* com:componentList)
	{
		if (!com->GetActive())
			continue;

		com->Update();
	}
	for (GameObject* gameObject:childList)
	{
		if (!gameObject->GetActive())
			continue;

		gameObject->Update();
	}

}

void GameObject::UpdateMatrix(void)
{
	if (!isActive)
		return;


	this->transformComponent->UpdateMatrix();

	for (GameObject* gameObject : childList)
	{
		if (!gameObject->GetActive())
			continue;

		gameObject->UpdateMatrix();
	}

}

void GameObject::Draw(ShaderSet::ShaderIndex index)
{
	if (!isActive)
		return;

	for (Component* component : GetComponentList())
	{
		if (component->GetAttribute() != Component::Attribute::Primitive)
			continue;

		PrimitiveComponent* primitiveComponent = static_cast<PrimitiveComponent*>(component);

		//現在セットしてるシェーダーを使っている場合描画
		if (primitiveComponent->GetMaterial()->GetShaderSet()->GetShaderIndex() != index)
			continue;

		primitiveComponent->Draw();

	}
	for (GameObject* child:childList)
	{
		if (!child->GetActive())
			continue;
		child->Draw(index);
	}

}

void GameObject::ShadowMapping(void)
{
	if (!isActive)
		return;

	for (Component* component : GetComponentList())
	{
		if (component->GetAttribute() != Component::Attribute::Primitive)
			continue;

		PrimitiveComponent* primitiveComponent = static_cast<PrimitiveComponent*>(component);

		if (!primitiveComponent->GetHasShadow()||!primitiveComponent->GetActive())
			continue;

		primitiveComponent->ShadowMapping();

	}
	for (GameObject* child : childList)
	{
		if (!child->GetActive())
			continue;
		child->ShadowMapping();
	}


}

Scene* GameObject::GetScene(void)
{

	return this->pScene;
}

TransformComponent* GameObject::GetTransFormComponent(void)
{
	return this->transformComponent;
}


GameObject::ObjectTag GameObject::GetTag(void)
{
	return tag;
}

GameObject::Layer GameObject::GetLayer(void)
{
	return this->layer;
}

BOOL GameObject::GetActive(void)
{
	return isActive;
}

void GameObject::SetActive(BOOL isActive)
{
	this->isActive = isActive;

	for (Component* com : componentList)
	{
		com->SetActive(isActive);
	}
	for (GameObject* child: childList)
	{
		child->SetActive(isActive);
	}
}

GameObject* GameObject::GetParent(void)
{
	return this->parent;
}

GameObject* GameObject::GetRootObject(void)
{
	if (this->parent == nullptr)
	{
		return this;

	}
	else
	{
		return this->parent->GetRootObject();
	}

}

GameObject* GameObject::GetChild(int index)
{
	return this->childList[index];
}

GameObject* GameObject::GetChild(string name)
{
	for (GameObject* gameObj:childList)
	{
		if (gameObj->GetName()==name)
		{
			return gameObj;
		}
	}

	return nullptr;
}

vector<GameObject*>& GameObject::GetChild()
{
	return this->childList;
}

vector<Component*>& GameObject::GetComponentList(void)
{
	return this->componentList;
}

Component* GameObject::GetComponentAttrbute(Component::Attribute attr, int n)
{
	int cnt = 0;

	for (int i = 0; i < componentList.size(); i++)
	{
		if (componentList[i]->GetAttribute()==attr)
		{
			if (cnt==n)
			{
				return componentList[i];

			}
			else
			{
				cnt++;
			}
		}
	}
	return nullptr;
}

void GameObject::SetHasShadowAll(BOOL b)
{

	for (Component* component : GetComponentList())
	{
		if (component->GetAttribute() != Component::Attribute::Primitive)
			continue;

		PrimitiveComponent* primitiveComponent = static_cast<PrimitiveComponent*>(component);


		primitiveComponent->SetHasShadow(b);

	}
	for (GameObject* child : childList)
	{
		child->SetHasShadowAll(b);
	}

}

GameObject* GameObject::AddChild(string name)
{
	GameObject* newObj = new GameObject(this);
	newObj->name = name;
	newObj->Awake();
	this->childList.push_back(newObj);
	return newObj;
}

string GameObject::GetName(void)
{
	return this->name;
}

void GameObject::SetName(string name)
{
	this->name = name;
}

void GameObject::LoadFbxFileMesh(string fName)
{
	MeshData* root = pScene->GetGameEngine()->GetAssetsManager()->LoadMeshFileFbx(fName);
	LoadMeshNode(root);
}

void GameObject::LoadMeshNode(MeshData* node)
{
	if (!node->GetIsRoot())
	{
		MeshComponent* mesh = this->AddComponent<MeshComponent>();
		mesh->SetMeshData(node);

	}


	for (MeshData* childData: node->GetChild())
	{
		AddChild(childData->GetName())->LoadMeshNode(childData);
	}


}
