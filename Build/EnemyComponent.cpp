#include "EnemyComponent.h"
#include "ColliderComponent.h"
#include "AttackComponent.h"
#include "AnimationControlerComponent.h"
#include "Scene.h"
#include "Player.h"
#include "RigidBodyComponent.h"
#include "GameEngine.h"
#include "QuadComponent.h"


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

void EnemyComponent::Awake(void)
{
	Component::Awake();
	hpFrame= pGameObject->AddChild("hpFrame");
	hpLine= pGameObject->AddChild("hpLine");

}

void EnemyComponent::Init(void)
{
	Component::Init();
	collider = GetComponent<ColliderComponent>();
	animControler = GetComponent<AnimationControlerComponent>();
	rb = GetComponent<RigidBodyComponent>();
	rb->SetIsStatic(FALSE);
	transform = GetTransFormComponent();
	player = pGameObject->GetScene()->GetGameObject<Player>();
	playerTransform = player->GetComponent<TransformComponent>();
	onAttack = FALSE;
	atkCnt = 0.0f;
	atkTime = 0.0f;

	QuadComponent* quad = hpFrame->AddComponent<QuadComponent>();
	quad->Init();
	quad->LoadTexture("data/texture/Hp_frame.png");
	quad->SetBillBorad(TRUE);
	hpFrameTrans = hpFrame->GetTransFormComponent();

	quad = hpLine->AddComponent<QuadComponent>();
	quad->Init();
	quad->LoadTexture("data/texture/Hp_line.png");
	quad->SetBillBorad(TRUE);
	hpLineTrans = hpLine->GetTransFormComponent();
	hpWidth = 300.0f;
	hpHeght = 10.0f;

	hpFrameTrans->SetScale(XMFLOAT3(hpWidth, hpHeght, 1.0f));
	hpLineTrans->SetScale(XMFLOAT3(hpWidth, hpHeght, 0.5f));
	hpFrameTrans->SetPosition(XMFLOAT3(0.0f, 310.0f, 0.0f));
	hpLineTrans->SetPosition(XMFLOAT3(0.0f, 310.0f, 0.0f));
	die = FALSE;
}

void EnemyComponent::Update(void)
{
	Component::Update();

	if (!die)
	{
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
						atack->PlayHitSound();

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

		if (onAttack)
		{
			atkCnt += pGameEngine->GetDeltaTime();
			if (atkCnt > atkTime)
			{
				onAttack = FALSE;
			}
		}
		if (hp <= 0.0f)
		{
			die = TRUE;
			this->animControler->SetCondition("Die", TRUE);

		}

	}



}

void EnemyComponent::LateUpdate(void)
{
	Component::LateUpdate();
	//アニメーション制御
	if (lastState != state)
	{


		switch (lastState)
		{
		case EnemyComponent::EnemyState::Idle:
		{
			break;
		}
		case EnemyComponent::EnemyState::Walk:
		{
			this->animControler->SetCondition("Walk", FALSE);
			break;
		}
		case EnemyComponent::EnemyState::Run:
		{
			this->animControler->SetCondition("Run", FALSE);

			break;
		}
		case EnemyComponent::EnemyState::Fall:
		{

			break;
		}

		default:
			break;
		}

		switch (state)
		{
		case EnemyComponent::EnemyState::Idle:
		{
			break;
		}
		case EnemyComponent::EnemyState::Walk:
		{
			this->animControler->SetCondition("Walk", TRUE);
			break;
		}
		case EnemyComponent::EnemyState::Run:
		{
			this->animControler->SetCondition("Run", TRUE);

			break;
		}
		case EnemyComponent::EnemyState::Fall:
		{

			break;
		}

		default:
			break;
		}




		lastState = state;

	}


	float hpLen = ((float)hp / (float)hpMax) * hpWidth;
	hpLineTrans->SetScale(XMFLOAT3(hpLen, hpHeght, 0.5f));

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

void EnemyComponent::StartAtk(float atkTime)
{
	this->atkTime = atkTime;
	atkCnt = 0.0f;
	onAttack = TRUE;
	state = EnemyState::Attack;
}

BOOL EnemyComponent::GetOnAttack(void)
{
	return onAttack;
}

