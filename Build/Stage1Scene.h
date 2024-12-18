#pragma once
#include "Scene.h"
class Stage1Scene : public Scene
{
public:
	Stage1Scene(GameEngine* pStage1Engine);
	~Stage1Scene();


	virtual void Init() override;

};

