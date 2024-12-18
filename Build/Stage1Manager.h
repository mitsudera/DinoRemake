#pragma once
#include "gameobject.h"
class Stage1Manager : public GameObject
{
public:
	Stage1Manager(Scene* scene);
	~Stage1Manager();

	virtual void Init(void) override;

};

