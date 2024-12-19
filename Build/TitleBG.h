#pragma once
#include "gameobject.h"
class TitleBG :public GameObject
{
public:
	TitleBG(Scene* scene);
	~TitleBG();
	virtual void Awake(void) override;


};

