#pragma once
#include "component.h"
#include "PlayerComponent.h"

class AnimationControlerComponent;
class RigidBodyComponent;

class PlayerAnimationControlComponent :public Component
{
public:
	PlayerAnimationControlComponent(GameObject* gameObject);
	~PlayerAnimationControlComponent();

	virtual void Init(void)override;
	virtual void Update(void) override;

	void SetWalkForward(BOOL b);
	void SetWalkBack(BOOL b);
	void SetWalkRight(BOOL b);
	void SetWalkLeft(BOOL b);
	void SetRun(BOOL b);
	void AttackTrigger(void);
	void JumpTrigger(void);
	void SetAngle(float f);
	BOOL GetIsTransition(void);
private:
	PlayerComponent* playerCom;
	AnimationControlerComponent* animControler;
	RigidBodyComponent* rb;

	PlayerComponent::PlayerState lastState;
};

