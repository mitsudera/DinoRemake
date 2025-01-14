#include "PlayerComponent.h"
#include "input.h"
#include "transformcomponent.h"
#include "AnimationControlerComponent.h"
#include "gameobject.h"
#include "Scene.h"
#include "TerrainComponent.h"
#include "ColliderComponent.h"
#include "PlayerAnimationControlComponent.h"
#include "RigidBodyComponent.h"
#include "GameEngine.h"
#include "SkinMeshLinkerComponent.h"
#include "ColliderComponent.h"
#include "AttackComponent.h"
#include "SpriteComponent.h"
#include "SoundSpeakerComponent.h"
#include "SceneManager.h"

PlayerComponent::PlayerComponent(GameObject* gameObject)
{
	pGameObject = gameObject;
}

PlayerComponent::~PlayerComponent()
{
}

void PlayerComponent::Awake(void)
{
	Component::Awake();
	speed = 150.0f;
	jumpForce = 600.0f;
	hpMax = 200;
	dodgeForce = 600.0f;
}

void PlayerComponent::Init(void)
{
	Component::Init();
	control = TRUE;
	animControl = GetComponent<PlayerAnimationControlComponent>();
	transform = GetTransFormComponent();
	rb = GetComponent<RigidBodyComponent>();
	linker = GetComponent<SkinMeshLinkerComponent>();
	collider = GetComponent<ColliderComponent>();
	camAt = pGameObject->SerchAllChild("CameraAt")->GetTransFormComponent();
	hpFrame= pGameObject->SerchAllChild("HPFrame")->GetComponent<SpriteComponent>();
	hpLine = pGameObject->SerchAllChild("HPLine")->GetComponent<SpriteComponent>();

	hpLineWidth = pGameEngine->GetWindowSize().x * 0.32f;
	hpLineHeight = pGameEngine->GetWindowSize().y * 0.02f;
	hpLinePos = XMFLOAT3(pGameEngine->GetWindowSize().x * 0.026f,pGameEngine->GetWindowSize().y * 0.05f,0.0f);

	hpFrame->SetSpriteLeftDown("data/texture/Hp_frame.png", hpLinePos, hpLineWidth, hpLineHeight);
	hpLine->SetSpriteLeftDown("data/texture/Hp_line.png", hpLinePos, hpLineWidth, hpLineHeight);



	camInvMode = FALSE;

	//linker->SetSpring("J_Sec_L_Bust1", 20.0f, 12000.0f, 280.0f);
	//linker->SetSpring("J_Sec_R_Bust1", 20.0f, 12000.0f, 280.0f);
	linker->SetSpring("J_Sec_L_Bust1", 20.0f, 12000.0f, 200.0f);
	linker->SetSpring("J_Sec_R_Bust1", 20.0f, 12000.0f, 200.0f);
	//linker->SetSpring("J_Sec_L_Bust2", 10.0f, 20000.0f, 400.0f);
	//linker->SetSpring("J_Sec_R_Bust2", 10.0f, 20000.0f, 400.0f);

	atkCom = pGameObject->SerchAllChild("weapon")->GetComponent<AttackComponent>();
	combo = Combo::Zero;
	attackCnt = 0.0f;
	onAttack = FALSE;

	sound = GetComponent<SoundSpeakerComponent>();
	sound->LoadSound("slash.wav", "slash", SoundType::SE);
	sound->LoadSound("playerAtkVoice.wav", "Attack", SoundType::VOICE);

	atkCom->SetHitSound(sound, "slash");
	dieCnt = 0.0f;
	hp = hpMax;
}

void PlayerComponent::Uninit(void)
{
	Component::Uninit();
}

void PlayerComponent::Update(void)
{
	Component::Update();

	float dt = pGameEngine->GetDeltaTime();

	if (state == PlayerState::Die)
	{
		dieCnt += dt;
		if (dieCnt > 2.5f)
		{
			pGameEngine->GetSceneManager()->SetScene(SceneManager::SCENE::TITLE);
			pScene->GetGameObjectName("Loading")->SetActive(TRUE);
		}
		return;
	}

	state = PlayerState::Idle;
	XMVECTOR playerFront = transform->GetAxisZ();


	if (control)
	{
		camAt->RotPitch((float)input->GetRightStickY(0) * 0.001f * XM_PI * dt);

		if (input->IsButtonTriggered(0, BUTTON_R3))
		{
			if (camInvMode)
			{
				camInvMode = FALSE;
				camAt->RotWorldYaw(XM_PI);

			}
			else
			{
				camInvMode = TRUE;

				camAt->RotWorldYaw(-XM_PI);

			}
		}

		if (!onAttack&&!onDodge)
		{

			if (camInvMode)
			{

			}
			else
			{

			}
			if (input->GetLeftStickY(0) < -950)
			{

				state = PlayerState::Run;


				velocity = speed * pGameEngine->GetDeltaTime() * 4.0f;

				rb->MovePosition(playerFront, velocity);



			}
			else if (input->GetLeftStickY(0) != 0 || input->GetLeftStickX(0) != 0)
			{

				state = PlayerState::Walk;
				velocity = speed * pGameEngine->GetDeltaTime();

				int x = input->GetLeftStickX(0);
				int y = input->GetLeftStickY(0);
				float angle = GetAngleInRadiansFromVector(XMFLOAT2(-y, x));

				XMVECTOR vec = XMVector3Rotate(playerFront, XMQuaternionRotationAxis(yonevec(), angle));
				rb->MovePosition(vec, velocity);
				animControl->SetAngle(angle);




			}
			else if (input->GetKeyboardPress(DIK_LSHIFT) && input->GetKeyboardPress(DIK_W))
			{

				state = PlayerState::Run;


				velocity = speed * pGameEngine->GetDeltaTime() * 4.0f;

				rb->MovePosition(playerFront, velocity);



			}
			else
			{

				if (input->GetKeyboardPress(DIK_W) || input->GetKeyboardPress(DIK_D) || input->GetKeyboardPress(DIK_S) || input->GetKeyboardPress(DIK_A))
				{
					state = PlayerState::Walk;

				}

				velocity = speed * pGameEngine->GetDeltaTime();

				if (input->GetKeyboardPress(DIK_W) && input->GetKeyboardPress(DIK_D))
				{
					float angle = XM_PIDIV4 * 1.0f;

					XMVECTOR vec = XMVector3Rotate(playerFront, XMQuaternionRotationAxis(yonevec(), angle));
					rb->MovePosition(vec, velocity);
					animControl->SetAngle(angle);

				}
				else if (input->GetKeyboardPress(DIK_D) && input->GetKeyboardPress(DIK_S))
				{
					float angle = XM_PIDIV4 * 3.0f;
					XMVECTOR vec = XMVector3Rotate(playerFront, XMQuaternionRotationAxis(yonevec(), angle));
					rb->MovePosition(vec, velocity);
					animControl->SetAngle(angle);


				}
				else if (input->GetKeyboardPress(DIK_S) && input->GetKeyboardPress(DIK_A))
				{
					float angle = XM_PIDIV4 * 5.0f;
					XMVECTOR vec = XMVector3Rotate(playerFront, XMQuaternionRotationAxis(yonevec(), angle));
					rb->MovePosition(vec, velocity);
					animControl->SetAngle(angle);




				}
				else if (input->GetKeyboardPress(DIK_A) && input->GetKeyboardPress(DIK_W))
				{
					float angle = XM_PIDIV4 * 7.0f;
					XMVECTOR vec = XMVector3Rotate(playerFront, XMQuaternionRotationAxis(yonevec(), angle));
					rb->MovePosition(vec, velocity);
					animControl->SetAngle(angle);




				}
				else if (input->GetKeyboardPress(DIK_W))
				{
					float angle = 0.0f;
					XMVECTOR vec = XMVector3Rotate(playerFront, XMQuaternionRotationAxis(yonevec(), angle));
					rb->MovePosition(vec, velocity);
					animControl->SetAngle(angle);



				}
				else if (input->GetKeyboardPress(DIK_D))
				{
					float angle = XM_PIDIV2 * 1.0f;
					XMVECTOR vec = XMVector3Rotate(playerFront, XMQuaternionRotationAxis(yonevec(), angle));
					rb->MovePosition(vec, velocity);
					animControl->SetAngle(angle);



				}
				else if (input->GetKeyboardPress(DIK_S))
				{
					float angle = XM_PIDIV2 * 2.0f;
					XMVECTOR vec = XMVector3Rotate(playerFront, XMQuaternionRotationAxis(yonevec(), angle));
					rb->MovePosition(vec, velocity);
					animControl->SetAngle(angle);



				}
				else if (input->GetKeyboardPress(DIK_A))
				{
					float angle = XM_PIDIV2 * 3.0f;
					XMVECTOR vec = XMVector3Rotate(playerFront, XMQuaternionRotationAxis(yonevec(), angle));
					rb->MovePosition(vec, velocity);
					animControl->SetAngle(angle);




				}

			}

			if (rb->GetOnGround())
			{
				if (input->GetKeyboardTrigger(DIK_SPACE) || input->IsButtonTriggered(0, BUTTON_X))
				{
					rb->AddForce(transform->GetAxisY() * jumpForce);

				}


			}

		}



		if (input->GetKeyboardPress(DIK_Z))
		{
			GetTransFormComponent()->RotYaw(-(XM_PI / 180));

		}
		else if (input->GetKeyboardPress(DIK_C))
		{
			GetTransFormComponent()->RotYaw((XM_PI / 180));

		}

		transform->RotWorldYaw((float)input->GetRightStickX(0) * 0.001f * XM_PI * dt);



	}
	if (onAttack)
	{
		attackCnt += pGameEngine->GetDeltaTime();
	}
	else if (onDodge)
	{
		dodgeCnt += pGameEngine->GetDeltaTime();
		rb->MovePosition(dodgeVec, dodgeForce * dt);

	}
	else
	{
		attackCnt = 0.0f;
		dodgeCnt = 0.0f;
	}


	if (rb->GetOnGround())
	{

		switch (combo)
		{
		case Combo::Zero:
		{
			if (!animControl->GetIsTransition())
			{
				if (input->GetKeyboardTrigger(DIK_RETURN) || input->IsButtonTriggered(0, BUTTON_B))
				{
					animControl->AttackTrigger();
					onAttack = TRUE;
					atkCom->SetAttack(5, 0.8f);
					combo = Combo::Attack1;
					sound->StartSound("Attack");
				}
				else if (input->GetKeyboardTrigger(DIK_R) || input->IsButtonTriggered(0, BUTTON_C))
				{

					Dodge();
					onDodge = TRUE;
					combo = Combo::Dodge;



				}


			}



			break;
		}
		case Combo::Attack1:
		{
			if (attackCnt > 0.8f && attackCnt <= 1.0f)
			{
				if (input->GetKeyboardTrigger(DIK_RETURN) || input->IsButtonTriggered(0, BUTTON_B))
				{
					animControl->AttackTrigger();
					onAttack = TRUE;

					atkCom->SetAttack(5, 0.8f);

					combo = Combo::Attack2;
					sound->StartSound("Attack");

				}
				else if (input->GetKeyboardTrigger(DIK_R) || input->IsButtonTriggered(0, BUTTON_C))
				{

					Dodge();
					onDodge = TRUE;
					onAttack = FALSE;

					combo = Combo::Dodge;
				}


			}
			else if (attackCnt > 1.0f)
			{
				onAttack = FALSE;

				combo = Combo::Zero;
			}

			break;
		}

		case Combo::Attack2:
		{
			if (attackCnt > 0.8f && attackCnt <= 1.0f)
			{
				if (input->GetKeyboardTrigger(DIK_RETURN) || input->IsButtonTriggered(0, BUTTON_B))
				{
					animControl->AttackTrigger();
					onAttack = TRUE;
					atkCom->SetAttack(5, 0.8f);

					combo = Combo::Attack1;
					sound->StartSound("Attack");

				}
				else if (input->GetKeyboardTrigger(DIK_R) || input->IsButtonTriggered(0, BUTTON_C))
				{

					Dodge();
					onDodge = TRUE;
					onAttack = FALSE;

					combo = Combo::Dodge;
				}

			}
			else if (attackCnt > 1.0f)
			{
				onAttack = FALSE;
				combo = Combo::Zero;
			}

			break;
		}
		case Combo::Dodge:
		{//回避
			if (dodgeCnt > 0.5f && dodgeCnt <= 0.666f)
			{
				if (input->GetKeyboardTrigger(DIK_RETURN) || input->IsButtonTriggered(0, BUTTON_B))
				{
					animControl->AttackTrigger();
					onAttack = TRUE;
					onDodge = FALSE;

					atkCom->SetAttack(5, 0.8f);

					combo = Combo::Attack1;
					sound->StartSound("Attack");

				}
				else if (input->GetKeyboardTrigger(DIK_R) || input->IsButtonTriggered(0, BUTTON_C))
				{

					Dodge();
					dodgeCnt = 0.0f;
					onDodge = TRUE;
					combo = Combo::Dodge;
				}

			}
			else if (dodgeCnt > 0.666f)
			{
				onDodge = FALSE;
				combo = Combo::Zero;
			}

			break;
		}

		default:
			break;
		}





	}

	if (collider->GetHitTag(GameObject::ObjectTag::EnemyAttack))
	{
		for (GameObject* hitObj : collider->GetHitTagObjectAll(GameObject::ObjectTag::EnemyAttack))
		{
			AttackComponent* atack = hitObj->GetComponent<AttackComponent>();
			if (atack->GetEnable())
			{
				//既に当たっているか？
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

	UIUpdate();

	if (hp <= 0.0f)
	{
		state = PlayerState::Die;
	}

	//if (collider->GetHitTag(GameObject::ObjectTag::Enemy))
	//{
	//	GameObject* enemy = collider->GetHitTagObject(GameObject::ObjectTag::Enemy);
	//}
}

void PlayerComponent::SetContorol(BOOL enable)
{
	control = enable;
}

PlayerComponent::PlayerState PlayerComponent::GetState(void)
{
	return this->state;
}

BOOL PlayerComponent::FindHitObject(GameObject* obj)
{

	for (GameObject* hitobj : hitList)
	{
		if (hitobj == obj)
		{
			return TRUE;

		}

	}

	return FALSE;
}

void PlayerComponent::PlayHitSoound(void)
{
	sound->StartSound("slash");
}

void PlayerComponent::Dodge(void)
{
	XMVECTOR playerFront = transform->GetAxisZ();
	XMVECTOR vec;
	float angle = 0.0f;
	animControl->DodgeTrigger();

	if (input->GetKeyboardPress(DIK_W) || input->GetKeyboardPress(DIK_D) || input->GetKeyboardPress(DIK_S) || input->GetKeyboardPress(DIK_A))
	{
		if (input->GetKeyboardPress(DIK_W) && input->GetKeyboardPress(DIK_D))
		{
			angle = XM_PIDIV4 * 1.0f;


		}
		else if (input->GetKeyboardPress(DIK_D) && input->GetKeyboardPress(DIK_S))
		{
			angle = XM_PIDIV4 * 3.0f;

		}
		else if (input->GetKeyboardPress(DIK_S) && input->GetKeyboardPress(DIK_A))
		{
			angle = XM_PIDIV4 * 5.0f;




		}
		else if (input->GetKeyboardPress(DIK_A) && input->GetKeyboardPress(DIK_W))
		{
			angle = XM_PIDIV4 * 7.0f;




		}
		else if (input->GetKeyboardPress(DIK_W))
		{
			angle = 0.0f;



		}
		else if (input->GetKeyboardPress(DIK_D))
		{
			angle = XM_PIDIV2 * 1.0f;



		}
		else if (input->GetKeyboardPress(DIK_S))
		{
			angle = XM_PIDIV2 * 2.0f;



		}
		else if (input->GetKeyboardPress(DIK_A))
		{
			angle = XM_PIDIV2 * 3.0f;

		}

	}
	else if (input->GetLeftStickX(0) || input->GetLeftStickY(0))
	{
		int x = input->GetLeftStickX(0);
		int y = input->GetLeftStickY(0);


		angle = GetAngleInRadiansFromVector(XMFLOAT2(-y, x));

	}
	else
	{
		angle = XM_PIDIV2 * 2.0f;
	}
	vec = XMVector3Rotate(playerFront, XMQuaternionRotationAxis(yonevec(), angle));
	animControl->SetAngle(angle);


	dodgeVec = vec;


}

void PlayerComponent::UIUpdate(void)
{
	float hpLen = ((float)hp / (float)hpMax) * hpLineWidth;

	hpLine->SetSpriteLeftDown(hpLinePos, hpLen, hpLineHeight);

}
