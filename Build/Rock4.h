#pragma once
#include "gameobject.h"
class Rock4 :public GameObject
{
public:
	Rock4(Scene* scene);
	~Rock4();
	virtual void Awake(void) override;

};

