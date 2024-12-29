#include "MoveTestComponent.h"
#include "transformcomponent.h"
#include "input.h"
#include "gameobject.h"
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
		GetTransFormComponent()->MoveZAxis(1.0f);
	}
	if (input->GetKeyboardPress(DIK_DOWN))
	{
		GetTransFormComponent()->MoveZAxis(-1.0f);

	}
	if (input->GetKeyboardPress(DIK_LEFT))
	{
		GetTransFormComponent()->MoveXAxis(-1.0f);
	}
	if (input->GetKeyboardPress(DIK_RIGHT))
	{
		GetTransFormComponent()->MoveXAxis(1.0f);
	}

	if (input->GetKeyboardPress(DIK_Z))
	{
		GetTransFormComponent()->RotYaw(-(XM_PI / 180));

	}
	if (input->GetKeyboardPress(DIK_C))
	{
		GetTransFormComponent()->RotYaw((XM_PI / 180));

	}

	GameObject* bone= pGameObject->SerchAllChild("C_Hip");

	//bone->GetTransFormComponent()->RotPitch(0.1f);

	//bone= pGameObject->SerchAllChild("C_Spine5");

	//bone->GetTransFormComponent()->RotPitch(-0.1f);
	//bone= pGameObject->SerchAllChild("C_Tail2");

	//bone->GetTransFormComponent()->RotYaw(0.1f);

}
