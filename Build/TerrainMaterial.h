#pragma once
#include "Material.h"

class TerrainShader;

class DX11Texture;

class TerrainMaterial :public Material
{
public:
	TerrainMaterial(AssetsManager* assetsManager);
	TerrainMaterial(TerrainMaterial* phong);
	~TerrainMaterial();

	// Material を介して継承されました
	virtual void SetBufferMaterial(void) override;



private:
	TerrainShader* pTerrainShader;




};

