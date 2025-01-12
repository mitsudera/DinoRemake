#pragma once
#include "gameobject.h"
class Tree1 :public GameObject
{
public:
	Tree1(Scene* scene);
	~Tree1();
	virtual void Awake(void) override;

};

