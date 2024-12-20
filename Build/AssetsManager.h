#pragma once
#include "CoreMinimal.h"
#include "ShaderSet.h"


class MeshData;

class KeyFrameAnimData; 

//class SkinMeshDataList;
//
//class SkeletonAnimData;

class DX11Texture;

class GameEngine;

class Material;

class AnimationData;

class RenderTexture;
//shader
class LambartShader;
class PhongShader;
class UIShader;
class ShadowShader;
class TerrainShader;

//posteffect
class PostEffectShader;
class GausianBlurShader;
class FadeShader;
class NotEffectShader;
class AssetsManager
{


public:
	AssetsManager();
	AssetsManager(GameEngine* pGameEngine);
	~AssetsManager();

	void Awake(void);
	void Uninit(void);




	int LoadMeshNode(string filepath);

	int LoadAnimationData(string filepath);
	AnimationData* GetAnimationData(int index);


	MeshData* GetMeshTree(int n);

	int AddMesh(MeshData* data);


	MeshData* GetMeshData(int n);

	//KeyFrameAnimData* GetKeyFrameAnimData(int n);


	GameEngine* GetGameEngine(void);


	//SkinMeshDataList* GetSkinMeshDataList(int n);
	//int LoadSkinMesh(string filepath);

	//SkeletonAnimData* GetSkeletonAnimData(int n);
	//int LoadSkeletonAnimData(string filepath);


	DX11Texture* GetTexture(int n);
	int LoadTexture(string filepath);

	void SetSkinMeshCompute(void);

	void CreateAllShader(void);
	void CreateDefaultMaterial(void);

	LambartShader* GetLambartShader(void);
	PhongShader* GetPhongShader(void);
	UIShader* GetUIShader(void);
	ShadowShader* GetShadowShader(void);
	TerrainShader* GetTerrainShader(void);

	GausianBlurShader* GetGausianBlurShader(void);
	FadeShader* GetFadeShader(void);
	NotEffectShader* GetNotEffectShader(void);

	void SetShader(ShaderSet::ShaderIndex index);

	int LoadMaterial(Material* material);

	Material* GetMaterial(int index);

	int GetMaterialIndex(string name);

	int CreateRenderTexture(int widht, int height, string name);
	int GetRenderTextureIndex(string name);
	RenderTexture* GetRenderTexture(int index);

	ShaderSet* GetShader(ShaderSet::ShaderIndex index);

	void DeleteRenderTexture(int index);

private:

	GameEngine* pGameEngine;
	vector<MeshData*> MeshDataTree;//メッシュデータのルートの配列
	vector<MeshData*> MeshDataArray;
	vector<AnimationData*> AnimDataArray;
	vector<RenderTexture*> RenderTextureArray;
	vector<ShaderSet*> ShaderSetArray;
	vector<PostEffectShader*> PostEffectShaderArray;

	//vector<KeyFrameAnimData*>  KeyFrameAnimDataArray;
	//vector<SkinMeshDataList*> SkinMeshDataListArray;
	//vector<SkeletonAnimData*> SkeletonAnimDataArray;
	vector<Material*> MaterialArray;

	vector<DX11Texture*> TextureArray;

	ID3D11ComputeShader* skinMeshCompute;

	LambartShader* lambartShader;
	PhongShader* phongShader;
	UIShader* uiShader;
	ShadowShader* shadowShader;
	TerrainShader* terrainShader;

	GausianBlurShader* gausianBlur;
	FadeShader* fadeShader;
	NotEffectShader* notEffectShader;
};

