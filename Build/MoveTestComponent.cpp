#include "MoveTestComponent.h"
#include "transformcomponent.h"
#include "input.h"
#include "gameobject.h"
#include "RigidBodyComponent.h"
#include "AnimationControlerComponent.h"
MoveTestComponent::MoveTestComponent(GameObject* gameObject)
{
	pGameObject = gameObject;
}

MoveTestComponent::~MoveTestComponent()
{
}

void MoveTestComponent::Awake(void)
{
	Component::Awake();

}

void MoveTestComponent::Init(void)
{
	Component::Init();
	this->rb = GetComponent<RigidBodyComponent>();
	transform = GetTransFormComponent();
	animControl = GetComponent<AnimationControlerComponent>();
	
}

void MoveTestComponent::Uninit(void)
{
	Component::Uninit();
}

void MoveTestComponent::Update(void)
{
	Component::Update();
	if (input->GetKeyboardPress(DIK_UP))
	{
		transform->MoveZ(1.0f);
		//rb->AddForce(transform->GetAxisZ() * 1.0f);
	}
	if (input->GetKeyboardPress(DIK_DOWN))
	{
		transform->MoveZ(-1.0f);

		rb->AddForce(transform->GetAxisZ() * -1.0f);

	}
	if (input->GetKeyboardPress(DIK_LEFT))
	{
		rb->AddForce(transform->GetAxisX() * -1.0f);
	}
	if (input->GetKeyboardPress(DIK_RIGHT))
	{
		rb->AddForce(transform->GetAxisX() * 1.0f);
	}

	if (input->GetKeyboardPress(DIK_Z))
	{
		GetTransFormComponent()->RotYaw(-(XM_PI / 180));

	}
	if (input->GetKeyboardPress(DIK_C))
	{
		GetTransFormComponent()->RotYaw((XM_PI / 180));

	}
	if (input->GetKeyboardTrigger(DIK_SPACE))
	{
		rb->AddForce(transform->GetAxisY() * 30.0f);
		animControl->SetCondition("JumpTrigger", TRUE);

	}

	if (rb->GetOnGround() == TRUE)
	{
		animControl->SetCondition("OnGround", TRUE);

	}
	else
	{
		animControl->SetCondition("OnGround", FALSE);

	}
}
