#pragma once
#include "Material.h"

class PhongShader;

class DX11Texture;

class PhongMaterial :public Material
{
public:
	PhongMaterial(AssetsManager* assetsManager);
	PhongMaterial(PhongMaterial* phong);
	~PhongMaterial();

	// Material を介して継承されました
	virtual void SetBufferMaterial(void) override;

	void LoadFbxMaterial(FbxSurfaceMaterial* fbxmaterial);


private:
	PhongShader* pPhongShader;




};

