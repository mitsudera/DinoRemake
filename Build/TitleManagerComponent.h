#pragma once
#include "component.h"

class FadeShader;

class TitleManagerComponent :public Component
{
public:
	TitleManagerComponent(GameObject* gameObject);
	~TitleManagerComponent();

	// Component ÇâÓÇµÇƒåpè≥Ç≥ÇÍÇ‹ÇµÇΩ
	virtual void Init(void) override;
	virtual void Uninit(void) override;
	virtual void Update(void) override;

private:
	GameObject* mikanLogo;
	GameObject* titleBG;
	GameObject* titleLogo;
	GameObject* bgmPlayer;
	GameObject* cursor;
	FadeShader* fadeShader;
	GameObject* titleCamera;
	enum class TitleState:int
	{
		ANIM_LOGO,	//= 0
		ANIM_TITLE,
		TITLE_MENU,

	};

	enum class TitleMenu:int
	{
		TUTORIAL,
		GAMESTART,
		CREDIT,
		EXIT,

		TITLE_MAX,
	};



	TitleState titleState;

	float animCnt;


	int animLogoWaitTime;
	int animLogoFadeTime;
	int animLogoTotalTime;
	int animTitleWaitTime;
	int animTitleFadeTime;
	int animTitleTotalTime;
	float animWait;
	int cursorIndex;
	BOOL flag_alpha;
	float alpha;

	TitleMenu select;

	int yellowIndex;
	int greenIndex;
	int blueIndex;
	int redIndex;
	BOOL wipe;
	float wipeSize;
};

