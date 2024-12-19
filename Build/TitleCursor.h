#pragma once
#include "gameobject.h"
class TitleCursor :public GameObject
{
public:
	TitleCursor(Scene* scene);
	~TitleCursor();
	virtual void Awake(void) override;

};

