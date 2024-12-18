#include "TitleManagerComponent.h"
#include "GameEngine.h"
#include "Scene.h"
#include "input.h"
#include "SceneManager.h"
#include "transformcomponent.h"
#include "gameobject.h"
#include "Scene.h"
#include "GameEngine.h"
#include "SpriteComponent.h"
#include "PostEffectShader.h"
#include "AssetsManager.h"
#include "FadeShader.h"
#include "CameraComponent.h"
#include "SoundSpeakerComponent.h"

// カーソル
#define CUR_WIDTH						(100)					//	カーソルサイズ
#define CUR_HEIGHT						(100)



#define TITLE_CUR1_X					(740.0f)				//	カーソルの位置
#define TITLE_CUR1_Y					(450.0f)

#define TITLE_CUR2_X					(1096.0f)
#define TITLE_CUR2_Y					(354.0f)

#define TITLE_CUR3_X					(740.0f)
#define TITLE_CUR3_Y					(258.0f)

#define TITLE_CUR4_X					(1096.0f)
#define TITLE_CUR4_Y					(162.0f)



TitleManagerComponent::TitleManagerComponent(GameObject* gameObject)
{
	this->pGameObject = gameObject;
}

TitleManagerComponent::~TitleManagerComponent()
{
}

void TitleManagerComponent::Init(void)
{

	Component::Init();
	attribute = Attribute::Manager;

	titleLogo = pGameObject->GetScene()->GetGameObjectName("TitleLogo");
	titleBG = pGameObject->GetScene()->GetGameObjectName("TitleBG");
	mikanLogo= pGameObject->GetScene()->GetGameObjectName("MikanLogo");
	bgmPlayer = pGameObject->GetScene()->GetGameObjectName("BGMPlayer");
	bgmPlayer->GetComponent<SoundSpeakerComponent>()->LoadSound("title.wav", "titleBGM", SoundType::BGM);
	bgmPlayer->GetComponent<SoundSpeakerComponent>()->LoadSound("crick.wav", "crick", SoundType::SE);
	bgmPlayer->GetComponent<SoundSpeakerComponent>()->LoadSound("kettei.wav", "kettei", SoundType::SE);

	cursor = pGameObject->GetScene()->GetGameObjectName("cursor");
	//一度セットすればアセットマネージャーに読み込まれる
	cursor->GetComponent<SpriteComponent>()->SetTexture("data/texture/cursor/Eyellow.png");
	cursor->GetComponent<SpriteComponent>()->SetTexture("data/texture/cursor/Egreen.png");
	cursor->GetComponent<SpriteComponent>()->SetTexture("data/texture/cursor/Eblue.png");
	cursor->GetComponent<SpriteComponent>()->SetTexture("data/texture/cursor/Ered.png");


	titleCamera = GetGameObject()->GetScene()->GetGameObjectName("Camera");
	CameraComponent* camcom = titleCamera->GetComponent<CameraComponent>();
	fadeShader = pGameEngine->GetAssetsManager()->GetFadeShader();
	fadeShader->SetFade(1.0f);
	camcom->SetPostEffect(static_cast<PostEffectShader*>(fadeShader));
	camcom->SetPostEffectEnable(FALSE);

	animCnt = 0.0f;

	animLogoWaitTime = 90;
	animLogoFadeTime = 90;
	animLogoTotalTime = animLogoWaitTime + animLogoFadeTime;
	animTitleWaitTime = 0;
	animTitleFadeTime = 45;
	animTitleTotalTime = animTitleWaitTime + animTitleFadeTime;
	animWait = 4.0f;
	cursorIndex = 0;
	select = TitleMenu::TUTORIAL;
	flag_alpha = TRUE;
	alpha = 1.0f;
	wipe = FALSE;
	wipeSize = 0.0f;
	titleState = TitleState::ANIM_LOGO;
}

void TitleManagerComponent::Uninit(void)
{
	Component::Uninit();
}

void TitleManagerComponent::Update(void)
{
	Component::Update();

	SceneManager* sceneManager= pGameObject->GetScene()->GetGameEngine()->GetSceneManager();
	

	SpriteComponent* mikanSprite = mikanLogo->GetComponent<SpriteComponent>();
	float fade = 0.0f;

	switch (titleState)
	{
	case TitleManagerComponent::TitleState::ANIM_LOGO:
		if (input->GetKeyboardTrigger(DIK_RETURN) || input->IsButtonTriggered(0, BUTTON_START) || input->IsButtonTriggered(0, BUTTON_B))
		{
			titleState = TitleState::ANIM_TITLE;
			animCnt = 0.0f;
			CameraComponent* camcom = titleCamera->GetComponent<CameraComponent>();
			camcom->SetPostEffectEnable(TRUE);
			fade = 1.0f;
			fadeShader->SetFade(fade);

			mikanLogo->SetActive(FALSE);

		}

		if (animCnt >= animLogoTotalTime)
		{
			titleState = TitleState::ANIM_TITLE;
			mikanLogo->SetActive(FALSE);
			animCnt = 0.0f;
			CameraComponent* camcom = titleCamera->GetComponent<CameraComponent>();
			camcom->SetPostEffectEnable(TRUE);

		}


		break;
	case TitleManagerComponent::TitleState::ANIM_TITLE:

		fade = animCnt / (float)animTitleFadeTime;
		fade = fade;

		fadeShader->SetFade(fade);


		if (animCnt >= animTitleTotalTime)
		{
			titleState = TitleState::TITLE_MENU;
			bgmPlayer->GetComponent<SoundSpeakerComponent>()->StartSound("titleBGM");
		}

		break;
	case TitleManagerComponent::TitleState::TITLE_MENU:




		// カーソルの切り替え
		if (input->GetKeyboardTrigger(DIK_DOWN) || input->GetKeyboardTrigger(DIK_S) || input->GetLeftStickY(0)<0 || input->IsButtonTriggered(0, BUTTON_DOWN))
		{
			bgmPlayer->GetComponent<SoundSpeakerComponent>()->StartSound("crick");
			select = (TitleMenu)((((int)select + 1 + (int)TitleMenu::TITLE_MAX) % (int)TitleMenu::TITLE_MAX));

		}
		if (input->GetKeyboardTrigger(DIK_UP) || input->GetKeyboardTrigger(DIK_W) || input->GetLeftStickY(0) > 0 || input->IsButtonTriggered(0, BUTTON_UP))
		{
			bgmPlayer->GetComponent<SoundSpeakerComponent>()->StartSound("crick");
			select = (TitleMenu)((((int)select - 1 + (int)TitleMenu::TITLE_MAX) % (int)TitleMenu::TITLE_MAX));
		}

		if (flag_alpha == TRUE)
		{
			alpha -= 0.02f;
			if (alpha <= 0.0f)
			{
				alpha = 0.0f;
				flag_alpha = FALSE;
			}
		}
		else
		{
			alpha += 0.02f;
			if (alpha >= 1.0f)
			{
				alpha = 1.0f;
				flag_alpha = TRUE;
			}
		}
		
		titleLogo->GetComponent<SpriteComponent>()->SetColor(XMFLOAT4(1.0f, 1.0f, 1.0f, alpha));

		XMFLOAT2 screenHW = pGameEngine->GetWindowSize();
		XMFLOAT3 pos;
		switch (select)		//カーソルの表記
		{
		case TitleMenu::TUTORIAL:
			pos.x = TITLE_CUR1_X ;
			pos.y = TITLE_CUR1_Y ;
			pos.z = 0.0f;
			cursor->GetComponent<SpriteComponent>()->SetSpriteLeftDown("data/texture/cursor/Ered.png", pos, CUR_WIDTH, CUR_HEIGHT);
			cursor->GetComponent<SpriteComponent>()->SetLRRev(FALSE);
			pos = XMFLOAT3(TITLE_CUR1_X, TITLE_CUR1_Y, 0.0f);

			if (input->GetKeyboardTrigger(DIK_RETURN) || input->IsButtonTriggered(0, BUTTON_START) || input->IsButtonTriggered(0, BUTTON_B))
			{// ステージ切り替え
				bgmPlayer->GetComponent<SoundSpeakerComponent>()->StartSound("kettei");

				pGameEngine->GetSceneManager()->SetScene(SceneManager::SCENE::TUORIAL);

				wipe = TRUE;
			}
			break;

		case TitleMenu::GAMESTART:
			pos.x = TITLE_CUR2_X ;
			pos.y = TITLE_CUR2_Y ;
			pos.z = 0.0f;
			cursor->GetComponent<SpriteComponent>()->SetSpriteLeftDown("data/texture/cursor/Eblue.png", pos, CUR_WIDTH, CUR_HEIGHT);
			cursor->GetComponent<SpriteComponent>()->SetLRRev(TRUE);


			if (input->GetKeyboardTrigger(DIK_RETURN) || input->IsButtonTriggered(0, BUTTON_START) || input->IsButtonTriggered(0, BUTTON_B))
			{
				// ステージ切り替え
				bgmPlayer->GetComponent<SoundSpeakerComponent>()->StartSound("kettei");

				pGameEngine->GetSceneManager()->SetScene(SceneManager::SCENE::STAGE_SELECT);

				wipe = TRUE;
			}
			break;

		case TitleMenu::CREDIT:
			pos.x = TITLE_CUR3_X ;
			pos.y = TITLE_CUR3_Y ;
			pos.z = 0.0f;
			cursor->GetComponent<SpriteComponent>()->SetSpriteLeftDown("data/texture/cursor/Egreen.png", pos, CUR_WIDTH, CUR_HEIGHT);
			cursor->GetComponent<SpriteComponent>()->SetLRRev(FALSE);



			if (input->GetKeyboardTrigger(DIK_RETURN) || input->IsButtonTriggered(0, BUTTON_START) || input->IsButtonTriggered(0, BUTTON_B))
			{// ステージ切り替え
				bgmPlayer->GetComponent<SoundSpeakerComponent>()->StartSound("kettei");
				wipe = TRUE;
			}
			break;

		case TitleMenu::EXIT:
			pos.x = TITLE_CUR4_X;
			pos.y = TITLE_CUR4_Y;
			pos.z = 0.0f;
			cursor->GetComponent<SpriteComponent>()->SetSpriteLeftDown("data/texture/cursor/Eyellow.png", pos, CUR_WIDTH, CUR_HEIGHT);
			cursor->GetComponent<SpriteComponent>()->SetLRRev(TRUE);


			pos = XMFLOAT3(TITLE_CUR4_X, TITLE_CUR4_Y, 0.0f);

			if (input->GetKeyboardTrigger(DIK_RETURN) || input->IsButtonTriggered(0, BUTTON_START) || input->IsButtonTriggered(0, BUTTON_B))
			{
				pGameEngine->Exit();
			}
			break;
		}
		cursor->GetComponent<SpriteComponent>()->SetSliceTexIndex(cursorIndex);

		if (animCnt > animWait)
		{
			animCnt = 0.0f;
			cursorIndex++;
		}


		break;
	default:
		break;
	}
	animCnt += pGameEngine->GetDeltaTime() * 60.0f;



}
