#pragma once
#include "EnemyComponent.h"

class AttackComponent;

class GolemComponent : public EnemyComponent
{
public:
	


	GolemComponent(GameObject* gameObject);
	~GolemComponent();

	virtual void Init(void)override;
	virtual void Update(void)override;

	void SetAttack(AttackComponent* rHand, AttackComponent* lHand);

private:
	AttackComponent* rHand;
	AttackComponent* lHand;
};
