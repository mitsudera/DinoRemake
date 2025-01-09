#pragma once
#include "component.h"
class AttackComponent :public Component
{
public:
	AttackComponent(GameObject* gameObject);
	~AttackComponent();

	virtual void Update(void)override;

	void SetAttack(int damage, float endTime);
	void SetEnable(BOOL enable);
	void SetDamage(int damage);

	int GetDamage(void);
	BOOL GetEnable(void);
private:
	int damage;
	BOOL enable;
	float timeCnt;
	float endTime;
};

