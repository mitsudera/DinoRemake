#pragma once
#include "gameobject.h"
class TitlePlayer : public GameObject
{
public:
	TitlePlayer(Scene* scene);
	~TitlePlayer();
	virtual void Awake(void) override;

};

