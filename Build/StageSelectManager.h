#pragma once
#include "gameobject.h"
class StageSelectManager :public GameObject
{
public:
	StageSelectManager(Scene* scene);
	~StageSelectManager();
	virtual void Awake(void) override;

};

