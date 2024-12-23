#include "Material.h"
#include "renderer.h"
#include "ShaderSet.h"
#include "AssetsManager.h"

Material::Material()
{
	this->noDiffuseTex = 1;
	this->noNormalTex = 1;
	this->noArmTex = 1;
	this->ambient = { 1.0f,1.0f,1.0f,1.0f };
	this->diffuse= { 1.0f,1.0f,1.0f,1.0f };
	this->specular= { 0.0f,0.0f,0.0f,0.0f };
	this->emission = { 0.0f,0.0f,0.0f,0.0f };
	this->shininess = 10.0f;
}

Material::~Material()
{
}


void Material::SetShaderRenderer(void)
{
	pShader->SetShaderRenderer();

}

void Material::SetBufferShadowMapping(void)
{
}

ShaderSet* Material::GetShaderSet(void)
{
	return this->pShader;
}


void Material::LoadDiffuseTex(string fName)
{
	textureDiffuse = pAssetsManager->LoadTexture(fName);
	this->noDiffuseTex = 0;
}

void Material::LoadNormalTex(string fName)
{
	textureNormal = pAssetsManager->LoadTexture(fName);
	this->noNormalTex = 0;

}

void Material::LoadArmTex(string fName)
{
	textureArm = pAssetsManager->LoadTexture(fName);
	this->noArmTex = 0;

}

void Material::SetName(string name)
{
	this->name = name;
}

string Material::GetName(void)
{
	return this->name;
}

DX11Texture* Material::GetDiffuseTexture(void)
{
	return this->textureDiffuse;
}
