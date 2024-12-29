#pragma once
#include "Coreminimal.h"
class GameEngine;
class TransformComponent;
class Input;
class GameObject;

class Component
{
public:

	enum class Attribute
	{
		Component,
		Transform,
		Collider,
		Primitive,
		Light,
		Manager,
		Camera,
	};

	Component();
	Component(GameObject* gameObject);
	~Component();

	virtual void Awake(void);//オブジェクトの生成時
	virtual void Init(void);//シーンが始まった時と動的に生成された時他オブジェクトやコンポーネント等を参照する場合はここで入れる
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void LateUpdate(void);
	virtual void Draw(void);
	virtual void DebugDraw(void);

	GameObject* GetGameObject(void);

	Component::Attribute GetAttribute(void);

	void SetActive(BOOL b);
	BOOL GetActive(void);

	template<class T>
	T* GetComponent(void);

	XMMATRIX GetWorldMtx(XMMATRIX world);
	XMMATRIX GetWorldMtx(void);
	XMFLOAT3 GetWorldPos(void);

	TransformComponent* GetTransFormComponent(void);


protected:
	GameObject* pGameObject;
	Attribute attribute;
	BOOL	isActive;
	GameEngine* pGameEngine;
	Input* input;

};

template<class T>
T* Component::GetComponent(void)
{
	return pGameObject->GetComponent<T>();
}
