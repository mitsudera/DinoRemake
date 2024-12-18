#pragma once
#include "Scene.h"
class TutorialScene :public Scene
{
public:
	
	TutorialScene(GameEngine* pGameEngine);
	~TutorialScene();

	virtual void Init() override;


};

