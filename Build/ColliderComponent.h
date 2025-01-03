#pragma once
#include "transformcomponent.h"
#include "Coreminimal.h"
#include "gameobject.h"



struct HitResult
{
	BOOL isHit[(int)GameObject::ObjectTag::ObjectTagMax];
	vector<GameObject*> hitObject;

};


class RigidBodyComponent;
class PhysxEngine;

class ColliderComponent :public Component
{
public:

	enum class Shape: int
	{

		Point,
		Line,
		Sphere,
		Capsule,
		Box,
		Terrain,


	};



	ColliderComponent();
	ColliderComponent(GameObject* gameObject);
	~ColliderComponent();


	virtual void Awake(void) override;
	virtual void Init(void)override;
	virtual void Uninit(void) override;

	virtual void Update(void) override;

	virtual void OnEnable(void)override;
	virtual void OnDisable(void)override;

	BOOL GetHitTag(GameObject::ObjectTag tag);

	void SetHitTag(GameObject::ObjectTag tag, BOOL isHit);

	Shape GetShape(void);
	void SetShape(Shape shape);

	GameObject::ObjectTag GetTag(void);


	void SetHitObject(GameObject* gameObject);
	BOOL GetHitObject(GameObject* gameObject);

	GameObject* GetHitTagObject(GameObject::ObjectTag tag);

	void OnCollider(void);
	void OffCollider(void);
	void Clear(void);

	XMFLOAT3 GetCenter(void);
	float GetCheckRadius(void);
	void SetCheckRadius(float r);
	BOOL GetIsStatic(void);

	//void SetRigidBody(RigidBodyComponent* rb);


	void UpdateCenter(void);

protected:
	PhysxEngine* pPhysxEngine;
	HitResult result;
	Shape shape;
	BOOL enable;
	BOOL isStatic;
	XMFLOAT3 center;//íÜêS
	float checkRadius;//ëÂÇ‹Ç©Ç»ìñÇΩÇËîªíËÇçsÇ§ÇΩÇﬂÇÃîºåa


};

