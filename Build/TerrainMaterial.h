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

	// Material ‚ğ‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½
	virtual void SetBufferMaterial(void) override;

	void LoadHeghtMap(string filePath);

	void SetTessEdgeFacter(float facter);
	void SetTessInsideFacter(float facter);

private:
	TerrainShader* pTerrainShader;

	int heightMapTexIndex;

	float tessEdgeFacter;
	float tessInsideFacter;

};

