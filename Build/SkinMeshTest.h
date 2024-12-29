#pragma once
#include "gameobject.h"
class SkinMeshTest : public GameObject
{
public:
	SkinMeshTest(Scene* scene);
	~SkinMeshTest();
	virtual void Awake(void) override;

};

