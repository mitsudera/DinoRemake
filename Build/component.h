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

	virtual void Awake(void);//�I�u�W�F�N�g�̐�����
	virtual void Init(void);//�V�[�����n�܂������Ɠ��I�ɐ������ꂽ�����I�u�W�F�N�g��R���|�[�l���g�����Q�Ƃ���ꍇ�͂����œ����
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void LateUpdate(void);
	virtual void Draw(void);
	virtual void DebugDraw(void);
	virtual void OnEnable(void);
	virtual void OnDisable(void);


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
	GameEngine* pGameEngine;
	Input* input;

private:
	BOOL	isActive;

};

template<class T>
T* Component::GetComponent(void)
{
	return pGameObject->GetComponent<T>();
}
