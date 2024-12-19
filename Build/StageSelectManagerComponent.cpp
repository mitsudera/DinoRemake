#include "StageSelectManagerComponent.h"
#include "GameEngine.h"
#include "SpriteComponent.h"
#include "gameobject.h"
#include "Scene.h"
#include "input.h"
#include "SoundSpeakerComponent.h"
#include "SceneManager.h"

#define SELECT_CUR1_X				(964.0f)		//	カーソルの位置
#define SELECT_CUR1_Y				(720.0f)

#define SELECT_CUR2_X				(1400.0f)
#define SELECT_CUR2_Y				(580.0f)

#define SELECT_CUR3_X				(964.0f)
#define SELECT_CUR3_Y				(440.0f)

#define CUR_WIDTH					(100.0f)			//カーソルサイズ
#define CUR_HEIGHT					(100.0f)





StageSelectManagerComponent::StageSelectManagerComponent(GameObject* gameObject)
{
	this->pGameObject = gameObject;
}

StageSelectManagerComponent::~StageSelectManagerComponent()
{
}

void StageSelectManagerComponent::Awake(void)
{
	Component::Awake();


}

void StageSelectManagerComponent::Init(void)
{
	Component::Init();

	cursor = pGameObject->GetScene()->GetGameObjectName("cursor");
	select = Select::Stage1;
	cursorIndex = 0;
	soundPlayer = pGameObject->GetScene()->GetGameObjectName("BGMPlayer");
	soundPlayer->GetComponent<SoundSpeakerComponent>()->LoadSound("crick.wav", "crick", SoundType::SE);
	soundPlayer->GetComponent<SoundSpeakerComponent>()->LoadSound("kettei.wav", "kettei", SoundType::SE);

	animWait = 4.0f;

}

void StageSelectManagerComponent::Uninit(void)
{
	Component::Uninit();

}

void StageSelectManagerComponent::Update(void)
{
	Component::Update();
	XMFLOAT3 pos;
	switch (select)
	{
	case StageSelectManagerComponent::Select::Stage1:

		pos = XMFLOAT3(SELECT_CUR1_X, SELECT_CUR1_Y, 0.0f);
		cursor->GetComponent<SpriteComponent>()->SetSpriteLeftDown("data/TEXTURE/cursor/Ered.png", pos, CUR_WIDTH, CUR_HEIGHT);
		if (input->GetKeyboardTrigger(DIK_RETURN) || input->IsButtonTriggered(0, BUTTON_START) || input->IsButtonTriggered(0, BUTTON_B))
		{// ステージ切り替え
			soundPlayer->GetComponent<SoundSpeakerComponent>()->StartSound("kettei");
			pGameEngine->GetSceneManager()->SetScene(SceneManager::SCENE::STAGE1);
		}

		break;

	case StageSelectManagerComponent::Select::Stage2:

		pos = XMFLOAT3(SELECT_CUR2_X, SELECT_CUR2_Y, 0.0f);
		cursor->GetComponent<SpriteComponent>()->SetSpriteLeftDown("data/TEXTURE/cursor/Eblue.png", pos, CUR_WIDTH, CUR_HEIGHT);

		if (input->GetKeyboardTrigger(DIK_RETURN) || input->IsButtonTriggered(0, BUTTON_START) || input->IsButtonTriggered(0, BUTTON_B))
		{// ステージ切り替え
			soundPlayer->GetComponent<SoundSpeakerComponent>()->StartSound("kettei");
			pGameEngine->GetSceneManager()->SetScene(SceneManager::SCENE::STAGE2);
		}

		break;

	case StageSelectManagerComponent::Select::Back:

		pos = XMFLOAT3(SELECT_CUR3_X, SELECT_CUR3_Y, 0.0f);
		cursor->GetComponent<SpriteComponent>()->SetSpriteLeftDown("data/TEXTURE/cursor/Egreen.png", pos, CUR_WIDTH, CUR_HEIGHT);

		if (input->GetKeyboardTrigger(DIK_RETURN) || input->IsButtonTriggered(0, BUTTON_START) || input->IsButtonTriggered(0, BUTTON_B))
		{// ステージ切り替え
			soundPlayer->GetComponent<SoundSpeakerComponent>()->StartSound("kettei");
			pGameEngine->GetSceneManager()->SetScene(SceneManager::SCENE::TITLE);
		}


		break;

	default:
		break;
	}

	if (input->GetKeyboardTrigger(DIK_DOWN) || input->GetKeyboardTrigger(DIK_S) || input->GetLeftStickY(0)<0 || input->IsButtonTriggered(0, BUTTON_DOWN))
	{
		soundPlayer->GetComponent<SoundSpeakerComponent>()->StartSound("crick");
		select = (Select)(((int)select + 1 + (int)Select::Max) % (int)Select::Max);
	}
	if (input->GetKeyboardTrigger(DIK_UP) || input->GetKeyboardTrigger(DIK_W) || input->GetLeftStickY(0) > 0 || input->IsButtonTriggered(0, BUTTON_UP))
	{
		soundPlayer->GetComponent<SoundSpeakerComponent>()->StartSound("crick");
		select = (Select)(((int)select - 1 + (int)Select::Max) % (int)Select::Max);
	}

	if (animCnt > animWait)
	{
		animCnt = 0.0f;
		cursorIndex++;
	}

	animCnt += pGameEngine->GetDeltaTime() * 60.0f;
	cursor->GetComponent<SpriteComponent>()->SetSliceTexIndex(cursorIndex);

}
