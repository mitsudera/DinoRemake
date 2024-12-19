#pragma once
#include "gameobject.h"
class TextMesh :public GameObject
{
public:
	TextMesh(Scene* scene);
	~TextMesh();
	virtual void Awake(void) override;



};

