#pragma once
#include "gameobject.h"
class RedEnemy : public GameObject
{
public:
	RedEnemy(Scene* scene);
	~RedEnemy();

	virtual void Awake(void) override;


};

