#pragma once
#include "Scene.h"

class TestScene : public Scene
{
public:
	TestScene(GameEngine* pGameEngine);
	~TestScene();


	virtual void Awake() override;

};

