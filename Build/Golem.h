#pragma once
#include "gameobject.h"
class Golem : public GameObject
{
public:
	Golem(Scene* scene);
	~Golem();

	virtual void Awake(void) override;


};

