#pragma once
#include "gameobject.h"
class Text :public GameObject
{
public:
	Text(Scene* scene);
	~Text();
	virtual void Awake(void) override;



};

