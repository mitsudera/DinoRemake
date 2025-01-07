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
		case PlayerComponent::PlayerState::ForwardWalk:
		{
			this->animControler->SetCondition("Walk", FALSE);
			break;
		}
		case PlayerComponent::PlayerState::BackWalk:
		{
			this->animControler->SetCondition("BackWalk", FALSE);

			break;
		}
		case PlayerComponent::PlayerState::RightWalk:
		{
			this->animControler->SetCondition("RightWalk", FALSE);

			break;
		}
		case PlayerComponent::PlayerState::LeftWalk:
		{
			this->animControler->SetCondition("LeftWalk", FALSE);

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
		case PlayerComponent::PlayerState::ForwardWalk:
		{
			this->animControler->SetCondition("Walk", TRUE);
			break;
		}
		case PlayerComponent::PlayerState::BackWalk:
		{
			this->animControler->SetCondition("BackWalk", TRUE);

			break;
		}
		case PlayerComponent::PlayerState::RightWalk:
		{
			this->animControler->SetCondition("RightWalk", TRUE);

			break;
		}
		case PlayerComponent::PlayerState::LeftWalk:
		{
			this->animControler->SetCondition("LeftWalk", TRUE);

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



	if (rb->GetOnGround() == TRUE)
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

void PlayerAnimationControlComponent::SetWalkBack(BOOL b)
{
	this->animControler->SetCondition("BackWalk", b);

}

void PlayerAnimationControlComponent::SetWalkRight(BOOL b)
{
	this->animControler->SetCondition("RightWalk", b);

}

void PlayerAnimationControlComponent::SetWalkLeft(BOOL b)
{
	this->animControler->SetCondition("LeftWalk", b);

}

void PlayerAnimationControlComponent::SetRun(BOOL b)
{
	this->animControler->SetCondition("Run", b);

}

void PlayerAnimationControlComponent::JumpTrigger(void)
{
	this->animControler->SetCondition("JumpTrigger",TRUE);
}
