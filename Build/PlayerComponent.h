#pragma once
#include "component.h"

class RigidBodyComponent;
class PlayerAnimationControlComponent;


class PlayerComponent :public Component
{
public:

	enum class PlayerState :int
	{
		Idle,
		ForwardWalk,
		BackWalk,
		RightWalk,
		LeftWalk,
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

	TransformComponent* transform;

	float velocity;

};

