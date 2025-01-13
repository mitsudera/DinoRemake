#pragma once
#include "gameobject.h"
class Rock1 :public GameObject
{
public:
	Rock1(Scene* scene);
	~Rock1();
	virtual void Awake(void) override;

};

