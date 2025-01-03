#pragma once
#include "component.h"

class ColliderComponent;

class RigidBodyComponent :public Component
{
public:
	RigidBodyComponent(GameObject* gameObject);
	~RigidBodyComponent();

	virtual void Awake(void) override;
	virtual void Init(void) override;
	virtual void Update(void) override;
	virtual void LateUpdate(void) override;
	virtual void Uninit(void) override;
	virtual void OnEnable(void)override;
	virtual void OnDisable(void)override;


	void SetMass(float f);
	void SetDrag(float f);
	void SetAngularDrag(float f);
	void SetUseGarvity(BOOL b);
	void SetIsKinematic(BOOL b);
	void AddForce(XMVECTOR force);

	BOOL GetOnGround(void);

private:
	ColliderComponent* collider;
	TransformComponent* transform;
	XMVECTOR velocity;
	float mass;
	float drag;
	float angularDrag;
	BOOL useGravity;
	BOOL isKinematic;
	BOOL onGround;
};

