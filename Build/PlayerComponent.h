#pragma once
#include "component.h"

class RigidBodyComponent;
class PlayerAnimationControlComponent;
class SkinMeshLinkerComponent;
class ColliderComponent;
class AttackComponent;
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

	PlayerComponent(GameObject* gameObject);
	~PlayerComponent();

	virtual void Awake(void) override;
	virtual void Init(void)override;
	virtual void Uninit(void) override;
	virtual void Update(void) override;

	void SetContorol(BOOL enable);

	PlayerState GetState(void);


private:
	BOOL control;

	PlayerState state;
	RigidBodyComponent* rb;
	PlayerAnimationControlComponent* animControl;
	SkinMeshLinkerComponent* linker;
	TransformComponent* transform;
	ColliderComponent* collider;
	AttackComponent* atkCom;
	float velocity;
	float speed;
	float jumpForce;
	float attackCnt;
	BOOL onAttack;

	BOOL devicePad;

	int combo;
};

