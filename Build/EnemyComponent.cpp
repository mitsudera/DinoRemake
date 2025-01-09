#include "EnemyComponent.h"
#include "ColliderComponent.h"
#include "AttackComponent.h"
EnemyComponent::EnemyComponent()
{
}
EnemyComponent::EnemyComponent(GameObject* gameObject)
{
	pGameObject = gameObject;
}

EnemyComponent::~EnemyComponent()
{
}

void EnemyComponent::Init(void)
{
	Component::Init();
	collider = GetComponent<ColliderComponent>();
	
}

void EnemyComponent::Update(void)
{
	Component::Update();

	if (collider->GetHitTag(GameObject::ObjectTag::PlayerAttack))
	{
		for (GameObject* hitObj : collider->GetHitTagObjectAll(GameObject::ObjectTag::PlayerAttack))
		{
			AttackComponent* atack = hitObj->GetComponent<AttackComponent>();
			if (atack->GetEnable())
			{
				if (FindHitObject(hitObj))
				{

				}
				else
				{
					hitList.push_back(hitObj);
					hp -= atack->GetDamage();


				}
			}
			else
			{

				hitList.remove(hitObj);

			}

		}

	}


	


	for (auto it = hitList.begin(); it != hitList.end(); ) 
	{
		GameObject* obj = *it;
		if (!collider->GetHitObject(obj)) {
			it = hitList.erase(it); // eraseは次の要素のイテレータを返す
		}
		else 
		{
			++it;
		}
	}

}

BOOL EnemyComponent::FindHitObject(GameObject* obj)
{

	for (GameObject* hitobj : hitList)
	{
		if (hitobj==obj)
		{
			return TRUE;

		}

	}

	return FALSE;
}

