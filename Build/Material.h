#pragma once
#include "Coreminimal.h"

class Renderer;

class ShaderSet;

class AssetsManager;

class DX11Texture;

class Material
{
public:
	Material();
	~Material();

	void SetShaderRenderer(void);

	virtual void SetBufferMaterial(void) = 0;

	void SetBufferShadowMapping(void);

	ShaderSet* GetShaderSet(void);


	void LoadDiffuseTex(string fName);
	void LoadNormalTex(string fName);
	void LoadArmTex(string fName);

	void SetName(string name);
	string GetName(void);

	DX11Texture* GetDiffuseTexture(void);

	XMFLOAT4	ambient;
	XMFLOAT4	diffuse;
	XMFLOAT4	specular;
	XMFLOAT4	emission;
	float		shininess;
	int			noDiffuseTex;
	int			noNormalTex;
	int			noArmTex;



protected:
	DX11Texture* textureDiffuse;
	DX11Texture* textureNormal;
	DX11Texture* textureArm;




	string name;

	ShaderSet* pShader;
	AssetsManager* pAssetsManager;

};

