#pragma once
#include "DebugLineShader.h"

class GameEngine;
class Renderer;

class DebugUtility
{
public:
	DebugUtility(GameEngine* gameEngine);
	~DebugUtility();

	void DrawDebugSphere(void);
	void DrawDebugBox(void);

	void SetDebugLineShader(void);

private:

	GameEngine* pGameEngine;
	Renderer* pRenderer;
	DebugLineShader* debugLineShader;

	ID3D11Buffer* vertexSphere;
	ID3D11Buffer* indexSphere;
	ID3D11Buffer* vertexBox;
	ID3D11Buffer* indexBox;
	unsigned int sphereIndexCnt;
	unsigned int spherevertCnt;

	unsigned int latitudeBands;
	unsigned int longitudeBands;
};

