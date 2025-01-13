#pragma once
#include "gameobject.h"
class Rock5 :public GameObject
{
public:
	Rock5(Scene* scene);
	~Rock5();
	virtual void Awake(void) override;

};

