#pragma once
#include "component.h"

class RigidBodyComponent;

class MoveTestComponent : public Component
{
public:
	MoveTestComponent(GameObject* gameObject);
	~MoveTestComponent();

	virtual void Awake(void) override;
	virtual void Init(void)override;
	virtual void Uninit(void) override;
	virtual void Update(void) override;


private:

	RigidBodyComponent* rb;
	TransformComponent* transform;
};

