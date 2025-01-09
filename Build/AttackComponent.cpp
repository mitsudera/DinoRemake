#include "AttackComponent.h"
#include "GameEngine.h"
AttackComponent::AttackComponent(GameObject* gameObject)
{
	pGameObject = gameObject;
}

AttackComponent::~AttackComponent()
{
}

void AttackComponent::Update(void)
{
	Component::Update();
	if (enable)
	{
		if (endTime < timeCnt)
		{
			enable = FALSE;
		}

		timeCnt += pGameEngine->GetDeltaTime();
	}


}

void AttackComponent::SetAttack(int damage, float endTime)
{
	enable = TRUE;
	this->damage = damage;
	this->endTime = endTime;
	timeCnt = 0.0f;
}

void AttackComponent::SetEnable(BOOL enable)
{
	this->enable = enable;
}

void AttackComponent::SetDamage(int damage)
{
	this->damage = damage;
}

int AttackComponent::GetDamage(void)
{
	return this->damage;
}

BOOL AttackComponent::GetEnable(void)
{
	return this->enable;
}
