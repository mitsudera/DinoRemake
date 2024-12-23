#include "AssetsManager.h"
#include "MeshData.h"
#include "GameEngine.h"
#include "MeshAnimData.h"
//#include "SkinMeshDataList.h"
//#include "SkeletonAnimData.h"
#include "DX11Texture.h"
#include "LambartShader.h"
#include "PhongShader.h"
#include "UIShader.h"
#include "Material.h"
#include "AnimationData.h"
#include "RenderTexture.h"
#include "ShadowShader.h"
#include "GausianBlurShader.h"
#include "LambartMaterial.h"
#include "FadeShader.h"
#include "UIMaterial.h"
#include "TerrainShader.h"
#include "NotEffectShader.h"

#define MESH_PATH "data/MODEL/mesh/"
#define SKINMESH_PATH "data/MODEL/skinmesh/"

#define ANIMATION_PATH "data/Animation/"


AssetsManager::AssetsManager()
{
	this->pGameEngine = nullptr;
	this->skinMeshCompute = nullptr;
}

AssetsManager::AssetsManager(GameEngine* pGameEngine)
{
	this->pGameEngine = pGameEngine;
	this->skinMeshCompute = nullptr;

}

AssetsManager::~AssetsManager()
{


}

void AssetsManager::Awake(void)
{
	//pGameEngine->GetRenderer()->CreateCSFile("shaders/CSskinmesh.hlsl", "CSFunc", &skinMeshCompute);
	
	CreateAllShader();
	CreateDefaultMaterial();
}

void AssetsManager::Uninit(void)
{

	for (int i = 0; i < this->MeshDataArray.size(); i++)
	{
		if(this->MeshDataArray[i]) delete this->MeshDataArray[i];

	}
	this->MeshDataArray.clear();


	for (AnimationData* data: AnimDataArray)
	{
		if (data) delete data;
	}
	AnimDataArray.clear();

	for (ShaderSet* data: ShaderSetArray)
	{
		data->Uninit();
		if (data) delete data;
	}
	ShaderSetArray.clear();

	for (PostEffectShader* data:PostEffectShaderArray)
	{
		if (data) delete data;
	}
	PostEffectShaderArray.clear();

	for (Material* data:MaterialArray)
	{
		if (data) delete data;
	}
	MaterialArray.clear();


	for (RenderTexture* data : RenderTextureArray)
	{
		if (data) delete data;
	}
	RenderTextureArray.clear();


	//for (int i = 0; i < this->KeyFrameAnimDataArray.size(); i++)
	//{
	//	delete this->KeyFrameAnimDataArray[i];
	//}
	//this->KeyFrameAnimDataArray.clear();

	//for (int i = 0; i < this->SkinMeshDataListArray.size(); i++)
	//{
	//	delete this->SkinMeshDataListArray[i];
	//}
	//this->SkinMeshDataListArray.clear();


	//for (int i = 0; i < this->SkeletonAnimDataArray.size(); i++)
	//{
	//	delete this->SkeletonAnimDataArray[i];
	//}
	//this->SkeletonAnimDataArray.clear();


	for (int i = 0; i < this->TextureArray.size(); i++)
	{
		delete this->TextureArray[i];
	}
	this->TextureArray.clear();


	if (skinMeshCompute) skinMeshCompute->Release();
}

MeshData* AssetsManager::LoadMeshFileFbx(string fileName)
{
	//既にロードしているデータか調べる
	for (MeshData* mesh : MeshDataTree)
	{
		string filePath = mesh->GetFileName();
		if ((MESH_PATH + fileName) == filePath)
		{
			return mesh;
		}
	}
	//ロードしてなかったら追加
	MeshData* meshdata = new MeshData;
	string path = MESH_PATH + fileName;
	meshdata->LoadFbxFile(path, this);
	this->MeshDataTree.push_back(meshdata);
	return meshdata;
}

AnimationData* AssetsManager::LoadAnimationData(string fileName)
{

	for (int i = 0; i < AnimDataArray.size(); i++)
	{

		string filePath = AnimDataArray[i]->GetFileName();
		if ((ANIMATION_PATH + fileName) == filePath)
		{
			return AnimDataArray[i];
		}
	}

	
	AnimationData* animdata = new AnimationData;
	string path = ANIMATION_PATH + fileName;
	animdata->LoadAnimation(path, this);
	this->AnimDataArray.push_back(animdata);
	return animdata;
}




int AssetsManager::AddMesh(MeshData* data)
{
	MeshDataArray.push_back(data);

	return (int)MeshDataArray.size()-1;
}
MeshData* AssetsManager::GetMeshData(int n)
{
	return this->MeshDataArray[n];
}



GameEngine* AssetsManager::GetGameEngine(void)
{
	return this->pGameEngine;
}


//int AssetsManager::LoadMeshAnim(string filepath)
//{
//	int p = -1;
//	BOOL find = FALSE;
//	for (int i = 0; i < KeyFrameAnimDataArray.size(); i++)
//	{
//		if ((MESH_ANIM_PATH + filepath) == KeyFrameAnimDataArray[i]->GetFilePath())
//		{
//			p = i;
//			find = TRUE;
//			break;
//		}
//	}
//
//	if (find == FALSE)
//	{
//
//		string path = MESH_ANIM_PATH + filepath;
//
//		KeyFrameAnimData* animdata = new KeyFrameAnimData;
//		animdata->LoadKeyFrameAnim(path);
//
//		this->KeyFrameAnimDataArray.push_back(animdata);
//		p = (int)KeyFrameAnimDataArray.size() - 1;
//	}
//
//	return p;
//}

//int AssetsManager::LoadSkinMesh(string filepath)
//{
//	int p = -1;
//	BOOL find = FALSE;
//	for (int i = 0; i < SkinMeshDataListArray.size(); i++)
//	{
//		if ((SKINMESH_PATH + filepath) == SkinMeshDataListArray[i]->GetFilePath())
//		{
//			p = i;
//			find = TRUE;
//			break;
//		}
//	}
//
//	if (find == FALSE)
//	{
//		string path = SKINMESH_PATH + filepath;
//
//
//		SkinMeshDataList* skinmeshdatalist = new SkinMeshDataList;
//
//		skinmeshdatalist->LoadSkinMeshDataList(path, this);
//
//		this->SkinMeshDataListArray.push_back(skinmeshdatalist);
//		p = (int)SkinMeshDataListArray.size() - 1;
//
//	}
//
//	return p;
//}
//
//SkinMeshDataList* AssetsManager::GetSkinMeshDataList(int n)
//{
//	return this->SkinMeshDataListArray[n];
//}
//
//SkeletonAnimData* AssetsManager::GetSkeletonAnimData(int n)
//{
//	return this->SkeletonAnimDataArray[n];
//}
//int AssetsManager::LoadSkeletonAnimData(string filepath)
//{
//	int p = -1;
//	BOOL find = FALSE;
//	for (int i = 0; i < SkeletonAnimDataArray.size(); i++)
//	{
//		if ((SKINMESH_ANIM_PATH + filepath) == SkeletonAnimDataArray[i]->GetFilePath())
//		{
//			p = i;
//			find = TRUE;
//			break;
//		}
//	}
//
//	if (find == FALSE)
//	{
//		string path = SKINMESH_ANIM_PATH + filepath;
//
//
//		SkeletonAnimData* skeletonAnimdata = new SkeletonAnimData;
//
//		
//		skeletonAnimdata->LoadSkeletonAnimData(path);
//
//		this->SkeletonAnimDataArray.push_back(skeletonAnimdata);
//		p = (int)SkeletonAnimDataArray.size() - 1;
//
//	}
//
//	return p;
//}



//DX11Texture* AssetsManager::GetTexture(int n)
//{
//
//
//	return this->TextureArray[n];
//}
DX11Texture* AssetsManager::LoadTexture(string filepath)
{
	for (DX11Texture* tex : TextureArray)
	{
		if (filepath == tex->GetFilePath())
		{
			return tex;
		}
	}


	DX11Texture* tex = new DX11Texture(this);
	tex->CreateSRV(filepath);
	this->TextureArray.push_back(tex);
	return tex;
}

void AssetsManager::SetSkinMeshCompute(void)
{
	GetGameEngine()->GetRenderer()->GetDeviceContext()->CSSetShader(skinMeshCompute, nullptr, 0);
}

void AssetsManager::CreateAllShader(void)
{
	//
	lambartShader = new LambartShader(this->pGameEngine->GetRenderer());
	ShaderSetArray.push_back(lambartShader);

	phongShader = new PhongShader(this->pGameEngine->GetRenderer());
	ShaderSetArray.push_back(phongShader);

	uiShader = new UIShader(this->pGameEngine->GetRenderer());
	ShaderSetArray.push_back(uiShader);

	shadowShader = new ShadowShader(this->pGameEngine->GetRenderer());
	ShaderSetArray.push_back(shadowShader);

	terrainShader = new TerrainShader(this->pGameEngine->GetRenderer());
	ShaderSetArray.push_back(terrainShader);


	//posteffect
	gausianBlur = new GausianBlurShader(this->pGameEngine->GetRenderer());
	PostEffectShaderArray.push_back(gausianBlur);

	fadeShader = new FadeShader(this->pGameEngine->GetRenderer());
	PostEffectShaderArray.push_back(fadeShader);

	notEffectShader = new NotEffectShader(this->pGameEngine->GetRenderer());
	PostEffectShaderArray.push_back(notEffectShader);


}

void AssetsManager::CreateDefaultMaterial(void)
{
	UIMaterial* uiMat = new UIMaterial(this);
	uiMat->SetName("UIMaterial");
	MaterialArray.push_back(uiMat);
}

LambartShader* AssetsManager::GetLambartShader(void)
{
	return this->lambartShader;
}

PhongShader* AssetsManager::GetPhongShader(void)
{
	return this->phongShader;
}

UIShader* AssetsManager::GetUIShader(void)
{
	return this->uiShader;
}


ShadowShader* AssetsManager::GetShadowShader(void)
{
	return this->shadowShader;
}

TerrainShader* AssetsManager::GetTerrainShader(void)
{
	return this->terrainShader;
}

GausianBlurShader* AssetsManager::GetGausianBlurShader(void)
{
	return this->gausianBlur;
}

FadeShader* AssetsManager::GetFadeShader(void)
{
	return this->fadeShader;
}

NotEffectShader* AssetsManager::GetNotEffectShader(void)
{
	return this->notEffectShader;
}

void AssetsManager::SetShader(ShaderSet::ShaderIndex index)
{
	switch (index)
	{

	case ShaderSet::Lambart:

		this->lambartShader->SetShaderRenderer();
		break;

	case ShaderSet::Phong:

		this->phongShader->SetShaderRenderer();
		break;

	case ShaderSet::UI:

		this->uiShader->SetShaderRenderer();
		break;
	case ShaderSet::Shadow:

		this->shadowShader->SetShaderRenderer();
		break;
	case ShaderSet::Terrain:
		this->terrainShader->SetShaderRenderer();
	}
}



int AssetsManager::CreateRenderTexture(int widht, int height, string name)
{
	RenderTexture* rtex = new RenderTexture(this);
	rtex->CreateRenderTexture(widht, height, name);
	RenderTextureArray.push_back(rtex);



	return RenderTextureArray.size() - 1;
}

int AssetsManager::GetRenderTextureIndex(string name)
{

	for (int i = 0; i < RenderTextureArray.size(); i++)
	{
		if (RenderTextureArray[i]->GetName() == name)
		{
			return i;
		}
	}

	return -1;
}

RenderTexture* AssetsManager::GetRenderTexture(int index)
{
	return this->RenderTextureArray[index];
}

ShaderSet* AssetsManager::GetShader(ShaderSet::ShaderIndex index)
{
	return ShaderSetArray[index];
}

void AssetsManager::DeleteRenderTexture(int index)
{
	if(this->RenderTextureArray[index]) delete this->RenderTextureArray[index];
	this->RenderTextureArray[index] = nullptr;
}

Material* AssetsManager::LoadMaterial(Material* material)
{
	if (material->GetName() != "")
	{
		for (Material* mat:MaterialArray)
		{
			if (mat->GetName() == material->GetName())
			{

				delete material;
				return mat;
			}
		}

	}

	this->MaterialArray.push_back(material);
	return material;
}

Material* AssetsManager::GetMaterial(string name)
{
	for (Material* mat : MaterialArray)
	{
		if (mat->GetName() == name)
		{
			return mat;
		}
	}
	return nullptr;
}
