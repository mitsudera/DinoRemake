#pragma once
#include "Material.h"
#include "TerrainShader.h"

class DX11Texture;


class TerrainMaterial :public Material
{
public:
	TerrainMaterial(AssetsManager* assetsManager);
	TerrainMaterial(TerrainMaterial* phong);
	~TerrainMaterial();

	// Material を介して継承されました
	virtual void SetBufferMaterial(void) override;

	void LoadHeghtMap(string filePath);

	void SetTessEdgeFacter(float facter);
	void SetTessInsideFacter(float facter);
	void SetHeightFacter(float facter);
private:
	TerrainShader* pTerrainShader;

	int heightMapTexIndex;

	float tessEdgeFacter;
	float tessInsideFacter;
	float heightFacter;

};

