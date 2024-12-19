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

	// Material ‚ğ‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½
	virtual void SetBufferMaterial(void) override;



private:
	TerrainShader* pTerrainShader;




};

