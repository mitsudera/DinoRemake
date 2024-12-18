#pragma once
#include "gameobject.h"
class TutorialManager :public GameObject
{
public:
	TutorialManager(Scene* scene);
	~TutorialManager();
	virtual void Init(void) override;

};

