#pragma once
#include "gameobject.h"
class TitleManager:public GameObject
{
public:
	TitleManager(Scene* scene);
	~TitleManager();
	virtual void Awake(void) override;
};

