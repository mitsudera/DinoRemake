#pragma once
#include "gameobject.h"
class Player :public GameObject
{
public:
	Player(Scene* scene);
	~Player();

	virtual void Awake(void) override;
};

