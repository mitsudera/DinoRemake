#pragma once
#include "component.h"

class ColliderComponent;
class RigidBodyComponent;
class AnimationControlerComponent;
class EnemyComponent : public Component
{
public:
	enum class EnemyState :int
	{
		Idle,
		Walk,
		Run,
		Fall,
		Attack,

	};



	EnemyComponent();
	EnemyComponent(GameObject* gameObject);
	~EnemyComponent();
	virtual void Awake(void)override;
	virtual void Init(void)override;
	virtual void Update(void) override;
	virtual void LateUpdate(void)override;

	BOOL FindHitObject(GameObject* obj);

	void StartAtk(float atkTime);

	BOOL GetOnAttack(void);
protected:
	int hpMax;
	int hp;
	float speed;
	float rotValue;
	float atkAngle;
	ColliderComponent* collider;

	list<GameObject*> hitList;
	
	EnemyState state;
	EnemyState lastState;
	AnimationControlerComponent* animControler;
	RigidBodyComponent* rb;
	TransformComponent* transform;

	GameObject* player;
	TransformComponent* playerTransform;
	GameObject* hpFrame;
	GameObject* hpLine;

	TransformComponent* hpFrameTrans;
	TransformComponent* hpLineTrans;

private:
	BOOL onAttack;
	float atkCnt;
	float atkTime;
	float height;
	float hpHeght;
	float hpWidth;
};

