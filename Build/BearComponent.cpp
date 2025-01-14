#include "BearComponent.h"
#include "AnimationControlerComponent.h"
#include "Scene.h"
#include "Player.h"
#include "GameEngine.h"
#include "transformcomponent.h"
#include "RigidBodyComponent.h"
#include "AttackComponent.h"
BearComponent::BearComponent(GameObject* gameObject)
{
	pGameObject = gameObject;
}

BearComponent::~BearComponent()
{
}

void BearComponent::Init(void)
{
	EnemyComponent::Init();
	hpMax = 10;
	hp = 10;
	speed = 50.0f;
	rotValue = 1.0f;
	atkAngle = XM_PIDIV4 * 0.1;
	
	
}

void BearComponent::Update(void)
{
	EnemyComponent::Update();

	if (die)
	{
		return;
	}


	float dt = pGameEngine->GetDeltaTime();
	XMVECTOR pv = XMLoadFloat3(&playerTransform->GetWorldPos());
	XMVECTOR ev = XMLoadFloat3(&GetWorldPos());
	XMVECTOR playerVec = pv - ev;
	XMVECTOR eVec = transform->GetAxisZ();
	eVec.m128_f32[1] = 0.0f;
	eVec = XMVector3Normalize(eVec);
	float len;
	XMStoreFloat(&len,XMVector3Length(playerVec));
	playerVec.m128_f32[1] = 0.0f;
	playerVec = XMVector3Normalize(playerVec);


	float angle = XMVectorGetX(XMVector3AngleBetweenNormals(eVec, playerVec));
	XMVECTOR axis = XMVector3Cross(eVec, playerVec);

	if (!GetOnAttack())
	{
		if (len < 280.0f)
		{


			if (angle < atkAngle || angle > XM_2PI-atkAngle)
			{
				if (!animControler->GetIsTransition())
				{
					this->animControler->SetCondition("Attack", TRUE);
					fung->SetAttackDelay(20, 0.5f, 0.3f);
					StartAtk(1.2f);
				}

			}
			else
			{
				if (angle > rotValue * dt)
				{
					if (XMVectorGetY(axis) >= 0)
					{

						transform->RotYaw(rotValue * dt);

					}
					else if (XMVectorGetY(axis) < 0)
					{
						transform->RotYaw(-rotValue * dt);

					}

				}
				else
				{
					if (XMVectorGetY(axis) > 0)
					{

						transform->RotYaw(angle);

					}
					else if (XMVectorGetY(axis) < 0)
					{
						transform->RotYaw(-angle);

					}

				}

			}

		}
		else if (len < 1500.0f)
		{
			state = EnemyState::Walk;
			rb->MovePosition(playerVec, speed * dt);

			if (angle > rotValue * dt)
			{
				if (XMVectorGetY(axis) > 0)
				{

					transform->RotYaw(rotValue * dt);

				}
				else if (XMVectorGetY(axis) < 0)
				{
					transform->RotYaw(-rotValue * dt);

				}

			}
			else
			{
				if (XMVectorGetY(axis) > 0)
				{

					transform->RotYaw(angle);

				}
				else if (XMVectorGetY(axis) < 0)
				{
					transform->RotYaw(-angle);

				}

			}


		}
		else
		{
			state = EnemyState::Idle;

		}

	}


	
}

void BearComponent::SetAttack(AttackComponent* fung)
{
	this->fung = fung;
}



