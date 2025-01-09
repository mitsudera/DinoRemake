#include "GolemComponent.h"

GolemComponent::GolemComponent(GameObject* gameObject)
{
	pGameObject = gameObject;
}

GolemComponent::~GolemComponent()
{
}

void GolemComponent::Init(void)
{
	EnemyComponent::Init();
	hpMax = 100;
	hp = 100;

}
