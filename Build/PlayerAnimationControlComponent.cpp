#include "PlayerAnimationControlComponent.h"
#include "AnimationControlerComponent.h"
#include "RigidBodyComponent.h"
#include "gameobject.h"
#include "PlayerComponent.h"

PlayerAnimationControlComponent::PlayerAnimationControlComponent(GameObject* gameObject)
{
	pGameObject = gameObject;

}

PlayerAnimationControlComponent::~PlayerAnimationControlComponent()
{
}


void PlayerAnimationControlComponent::Init(void)
{
	Component::Init();
	this->animControler = GetComponent<AnimationControlerComponent>();
	this->rb = GetComponent<RigidBodyComponent>();
	this->playerCom = GetComponent<PlayerComponent>();
	lastState = PlayerComponent::PlayerState::Idle;
}


void PlayerAnimationControlComponent::Update(void)
{
	Component::Update();

	PlayerComponent::PlayerState ps = playerCom->GetState();

	if (lastState != ps)
	{


		switch (lastState)
		{
		case PlayerComponent::PlayerState::Idle:
		{
			break;
		}
		case PlayerComponent::PlayerState::Walk:
		{
			this->animControler->SetCondition("Walk", FALSE);
			break;
		}
		case PlayerComponent::PlayerState::Run:
		{
			this->animControler->SetCondition("Run", FALSE);

			break;
		}
		case PlayerComponent::PlayerState::Fall:
		{

			break;
		}

		default:
			break;
		}

		switch (ps)
		{
		case PlayerComponent::PlayerState::Idle:
		{
			break;
		}
		case PlayerComponent::PlayerState::Walk:
		{
			this->animControler->SetCondition("Walk", TRUE);
			break;
		}
		case PlayerComponent::PlayerState::Run:
		{
			this->animControler->SetCondition("Run", TRUE);

			break;
		}
		case PlayerComponent::PlayerState::Fall:
		{

			break;
		}

		default:
			break;
		}




		lastState = ps;

	}



	if (rb->GetGroundLength() < 10.0f)
	{
		this->animControler->SetCondition("OnGround", TRUE);

	}
	else
	{
		this->animControler->SetCondition("OnGround", FALSE);

	}


}

void PlayerAnimationControlComponent::SetWalkForward(BOOL b)
{
	this->animControler->SetCondition("Walk", b);

}


void PlayerAnimationControlComponent::SetRun(BOOL b)
{
	this->animControler->SetCondition("Run", b);

}

void PlayerAnimationControlComponent::AttackTrigger(void)
{
	this->animControler->SetCondition("Attack",TRUE);
}

void PlayerAnimationControlComponent::SetAngle(float f)
{
	animControler->SetAngle(f);
}

BOOL PlayerAnimationControlComponent::GetIsTransition(void)
{
	return animControler->GetIsTransition();
}
