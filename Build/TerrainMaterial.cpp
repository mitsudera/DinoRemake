#include "TerrainMaterial.h"
#include "TerrainShader.h"
#include "DX11Texture.h"
#include "AssetsManager.h"

TerrainMaterial::TerrainMaterial(AssetsManager* assetsManager)
{
	this->pAssetsManager = assetsManager;
	this->pTerrainShader = assetsManager->GetTerrainShader();
	this->pShader = assetsManager->GetTerrainShader();

}

TerrainMaterial::TerrainMaterial(TerrainMaterial* terrain)
{
	this->pAssetsManager = terrain->pAssetsManager;

	this->pShader = terrain->pShader;
	this->pTerrainShader = terrain->pTerrainShader;

	this->diffuse = terrain->diffuse;
	this->ambient = terrain->ambient;
	this->emission = terrain->emission;
	this->specular = terrain->specular;
	this->shininess = terrain->shininess;
	this->noDiffuseTex = terrain->noDiffuseTex;
	this->noNormalTex = terrain->noNormalTex;
	this->noArmTex = terrain->noArmTex;
	this->textureDiffuseIndex = terrain->textureDiffuseIndex;
	this->textureNormalIndex = terrain->textureNormalIndex;
	this->textureArmIndex = terrain->textureArmIndex;

}

TerrainMaterial::~TerrainMaterial()
{
}

void TerrainMaterial::SetBufferMaterial(void)
{
	TerrainShader::MaterialCBuffer mCBuffer;
	mCBuffer.ambient = this->ambient;
	mCBuffer.diffuse = this->diffuse;
	mCBuffer.emission = this->emission;
	mCBuffer.shininess = this->shininess;
	mCBuffer.specular = this->specular;
	mCBuffer.noDiffuseTex = this->noDiffuseTex;
	mCBuffer.noNormalTex = this->noNormalTex;
	mCBuffer.noArmTex = this->noArmTex;
	this->pTerrainShader->SetMaterialCbuffer(mCBuffer);

	if (!noDiffuseTex) pAssetsManager->GetTexture(textureDiffuseIndex)->SetShaderResourcePS(0);
	if (!noNormalTex) pAssetsManager->GetTexture(textureNormalIndex)->SetShaderResourcePS(1);
	if (!noArmTex) pAssetsManager->GetTexture(textureArmIndex)->SetShaderResourcePS(2);


}


