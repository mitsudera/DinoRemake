#pragma once
#include "component.h"

class RigidBodyComponent;
class PlayerAnimationControlComponent;
class SkinMeshLinkerComponent;
class ColliderComponent;
class AttackComponent;
class SpriteComponent;
class PlayerComponent :public Component
{
public:

	enum class PlayerState :int
	{
		Idle,
		Walk,
		Run,
		Jump,
		Fall,

	};

	enum class Combo :int
	{
		Zero,
		Attack1,
		Attack2,
		Dodge,

	};

	PlayerComponent(GameObject* gameObject);
	~PlayerComponent();

	virtual void Awake(void) override;
	virtual void Init(void)override;
	virtual void Uninit(void) override;
	virtual void Update(void) override;

	void SetContorol(BOOL enable);

	PlayerState GetState(void);

	BOOL FindHitObject(GameObject* obj);



private:
	BOOL control;

	PlayerState state;
	RigidBodyComponent* rb;
	PlayerAnimationControlComponent* animControl;
	SkinMeshLinkerComponent* linker;
	TransformComponent* transform;
	ColliderComponent* collider;
	AttackComponent* atkCom;
	TransformComponent* camAt;
	SpriteComponent* hpLine;
	SpriteComponent* hpFrame;
	float hpLineWidth;
	float hpLineHeight;
	XMFLOAT3 hpLinePos;

	float velocity;
	float speed;
	float jumpForce;
	float attackCnt;
	float dodgeCnt;
	BOOL onAttack;
	BOOL onDodge;
	float dodgeForce;
	float dodgeUpForce;

	void Dodge(void);
	void UIUpdate(void);

	BOOL devicePad;

	Combo combo;

	int hpMax;
	int hp;

	list<GameObject*> hitList;

};

