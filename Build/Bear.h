#pragma once
#include "gameobject.h"
class Bear : public GameObject
{
public:
	Bear(Scene* scene);
	~Bear();

	virtual void Awake(void) override;


};

