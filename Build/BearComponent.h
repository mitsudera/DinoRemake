#pragma once
#include "EnemyComponent.h"

class AttackComponent;

class BearComponent : public EnemyComponent
{
public:
	

	
	BearComponent(GameObject* gameObject);
	~BearComponent();

	virtual void Init(void)override;
	virtual void Update(void)override;

	void SetAttack(AttackComponent* fung);

private:
	AttackComponent* fung;
};
