#pragma once
#include "component.h"

class ColliderComponent;
class EnemyComponent : public Component
{
public:
	EnemyComponent();
	EnemyComponent(GameObject* gameObject);
	~EnemyComponent();
	virtual void Init(void)override;
	virtual void Update(void) override;

	BOOL FindHitObject(GameObject* obj);

protected:
	int hpMax;
	int hp;
	ColliderComponent* collider;

	list<GameObject*> hitList;
	
};

