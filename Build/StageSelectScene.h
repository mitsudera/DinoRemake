#pragma once
#include "Scene.h"
class StageSelectScene :public Scene
{
public:

	StageSelectScene(GameEngine* pGameEngine);
	~StageSelectScene();

	virtual void Awake() override;


};


