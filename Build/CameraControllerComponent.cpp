#include "CameraControllerComponent.h"
#include "gameobject.h"
#include "CameraComponent.h"
#include "GameEngine.h"
#include "Scene.h"
#include "input.h"
#include "transformcomponent.h"
CameraControllerComponent::CameraControllerComponent(GameObject* gameObject)
{
	this->pGameObject = gameObject;
}

CameraControllerComponent::~CameraControllerComponent()
{
}

void CameraControllerComponent::Awake(void)
{
	Component::Awake();
}

void CameraControllerComponent::Init(void)
{
	Component::Init();

}

void CameraControllerComponent::Uninit(void)
{
	Component::Uninit();
}

void CameraControllerComponent::Update(void)
{
	Component::Update();
	if (input->GetKeyboardPress(DIK_W))
	{
		GetTransFormComponent()->MoveZAxis(1.0f);

	}
	if (input->GetKeyboardPress(DIK_S))
	{
		GetTransFormComponent()->MoveZAxis(-1.0f);

	}
	if (input->GetKeyboardPress(DIK_D))
	{
		GetTransFormComponent()->MoveXAxis(1.0f);

	}
	if (input->GetKeyboardPress(DIK_A))
	{
		GetTransFormComponent()->MoveXAxis(-1.0f);

	}
	if (input->GetKeyboardPress(DIK_E))
	{
		GetTransFormComponent()->MoveYAxis(1.0f);

	}
	if (input->GetKeyboardPress(DIK_Q))
	{
		GetTransFormComponent()->MoveYAxis(-1.0f);

	}
	if (input->IsMouseRightPressed())
	{
		float x, y;

		x = (float)input->GetMouseX();
		y = (float)input->GetMouseY();


		x *= 0.001f;
		y *= 0.001f;

		GetTransFormComponent()->RotWorldYaw(x);
		GetTransFormComponent()->RotPitch(y);

	}

}
