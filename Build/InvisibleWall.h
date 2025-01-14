#pragma once
#include "gameobject.h"
class InvisibleWall :public GameObject
{
public:
	InvisibleWall(Scene* scene);
	~InvisibleWall();
	virtual void Awake(void) override;

};

