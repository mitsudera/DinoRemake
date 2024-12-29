#include "SkinMeshPhongMaterial.h"
#include "SkinMeshPhongShader.h"
#include "DX11Texture.h"
#include "AssetsManager.h"

SkinMeshPhongMaterial::SkinMeshPhongMaterial(AssetsManager* assetsManager)
{
	this->pAssetsManager = assetsManager;
	this->pSkinMeshPhongShader = assetsManager->GetSkinMeshShader();
	this->pShader = assetsManager->GetSkinMeshShader();

}

SkinMeshPhongMaterial::SkinMeshPhongMaterial(SkinMeshPhongMaterial* phong)
{
	this->pAssetsManager = phong->pAssetsManager;

	this->pShader = phong->pShader;
	this->pSkinMeshPhongShader = phong->pSkinMeshPhongShader;

	this->diffuse = phong->diffuse;
	this->ambient = phong->ambient;
	this->emission = phong->emission;
	this->specular = phong->specular;
	this->shininess = phong->shininess;
	this->noDiffuseTex = phong->noDiffuseTex;
	this->noNormalTex = phong->noNormalTex;
	this->noArmTex = phong->noArmTex;
	this->textureDiffuse = phong->textureDiffuse;
	this->textureNormal = phong->textureNormal;
	this->textureArm = phong->textureArm;

}

SkinMeshPhongMaterial::~SkinMeshPhongMaterial()
{
}

void SkinMeshPhongMaterial::SetBufferMaterial(void)
{
	SkinMeshPhongShader::MaterialCBuffer mCBuffer;
	mCBuffer.ambient = this->ambient;
	mCBuffer.diffuse = this->diffuse;
	mCBuffer.emission = this->emission;
	mCBuffer.shininess = this->shininess;
	mCBuffer.specular = this->specular;
	mCBuffer.noDiffuseTex = this->noDiffuseTex;
	mCBuffer.noNormalTex = this->noNormalTex;
	mCBuffer.noArmTex = this->noArmTex;
	this->pSkinMeshPhongShader->SetMaterialCbuffer(mCBuffer);

	if (!noDiffuseTex) textureDiffuse->SetShaderResourcePS(0);
	if (!noNormalTex)textureNormal->SetShaderResourcePS(1);
	if (!noArmTex) textureArm->SetShaderResourcePS(2);


}



void SkinMeshPhongMaterial::LoadFbxMaterial(FbxSurfaceMaterial* fbxmaterial)
{

	// Phong�Ƀ_�E���L���X�g
	FbxSurfacePhong* phong = (FbxSurfacePhong*)fbxmaterial;
	//�A���r�G���g
	FbxDouble3 amb = phong->Ambient;

	ambient.x = (float)amb[0];
	ambient.y = (float)amb[1];
	ambient.z = (float)amb[2];

	//�f�B�t���[�Y
	FbxDouble3 dif = phong->Diffuse;

	diffuse.x = (float)dif[0];
	diffuse.y = (float)dif[1];
	diffuse.z = (float)dif[2];

	// ���ߓx
	FbxDouble transparency = phong->TransparencyFactor;
	diffuse.w = (float)transparency;

	//�G�~�b�V����
	FbxDouble3 emi = phong->Emissive;

	emission.x = (float)emi[0];
	emission.y = (float)emi[1];
	emission.z = (float)emi[2];

	//�X�y�L�����[
	FbxDouble3 spe = phong->Specular;

	specular.x = (float)spe[0];
	specular.y = (float)spe[1];
	specular.z = (float)spe[2];

	FbxDouble shine = phong->Shininess;
	shininess = (float)shine;


	// �v���p�e�B�擾�B
	const FbxProperty property = fbxmaterial->FindProperty(
		FbxSurfaceMaterial::sDiffuse    // const char* pName
	);                                  // bool pCaseSensitive = true



	// �v���p�e�B�������Ă��郌�C���[�h�e�N�X�`���̖������`�F�b�N
	int layerNum = property.GetSrcObjectCount<FbxFileTexture>();

	if (layerNum > 0)
	{
		FbxFileTexture* pFileTexture = property.GetSrcObject<FbxFileTexture>(0);

		FbxFileTexture::ETextureUse m_type = FbxFileTexture::ETextureUse(pFileTexture->GetTextureUse());


		//�f�B�t���[�Y�e�N�X�`���Ȃ�
		if (m_type == FbxFileTexture::ETextureUse::eStandard)
		{
			const char* fileName = pFileTexture->GetFileName();

			int slush = '/';
			char* path;
			path = new char[256];

			//�Ō��/���o�Ă���ꏊ
			const char* last = strrchr(fileName, slush);


			if (last == nullptr)
			{
				strcpy(path, "data/TEXTURE/");

				strcat(path, fileName);

			}
			else
			{
				strcpy(path, "data/TEXTURE");

				strcat(path, last);

			}

			this->LoadDiffuseTex(path);

			delete[]path;

			// �}�e���A���ݒ�
			noDiffuseTex = false;
		}

	}

	this->noDiffuseTex = true;
	this->noNormalTex = true;
	this->noArmTex = true;



	// �v���p�e�B�擾�B
	const FbxProperty propertynormal = fbxmaterial->FindProperty(
		FbxSurfaceMaterial::sBump    // const char* pName
	);                                  // bool pCaseSensitive = true



	// �v���p�e�B�������Ă��郌�C���[�h�e�N�X�`���̖������`�F�b�N
	layerNum = propertynormal.GetSrcObjectCount<FbxFileTexture>();

	if (layerNum > 0)
	{
		FbxFileTexture* pFileTextureNormal = propertynormal.GetSrcObject<FbxFileTexture>(0);

		FbxFileTexture::ETextureUse m_type = FbxFileTexture::ETextureUse(pFileTextureNormal->GetTextureUse());


		if (m_type == FbxFileTexture::ETextureUse::eStandard)
		{

			const char* fileName1 = pFileTextureNormal->GetFileName();
			int slush = '/';
			char* path;
			path = new char[256];

			//�Ō��/���o�Ă���ꏊ
			const char* last = strrchr(fileName1, slush);

			strcpy(path, "data/TEXTURE");
			strcat(path, last);

			this->LoadNormalTex(path);

			delete[]path;

			noNormalTex = FALSE;

		}


	}



}