#pragma once
#include "gameobject.h"
class Loading :public GameObject
{
public:
	Loading(Scene* scene);
	~Loading();
	virtual void Awake(void) override;


};

