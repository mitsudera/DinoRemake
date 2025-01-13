#pragma once
#include "gameobject.h"
class Rock3 :public GameObject
{
public:
	Rock3(Scene* scene);
	~Rock3();
	virtual void Awake(void) override;

};

