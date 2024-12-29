#pragma once
#include "Coreminimal.h"
#include "SkinMeshPhongShader.h"
class AssetsManager;
class SkinMeshTreeData;
class BoneData;
class Material;
class Renderer;

struct CONTROLPOINT
{
	XMFLOAT3 pos;
	float* weight;

};



class SkinMeshData
{
public:
	SkinMeshData(AssetsManager* p);
	~SkinMeshData();
	void LoadSkinMesh(FbxMesh* mesh, SkinMeshData* parent,SkinMeshTreeData* skinMeshTree);

	vector <SkinMeshData*>& GetChildArray(void);

	string GetName(void);


	ID3D11Buffer* GetIndexBuffer(void);

	int GetCotrolPointNum(void);
	CONTROLPOINT* GetControlPoint(void);

	int GetVertNum(void);
	SkinMeshVertex* GetVertexArray(void);
	int* GetCPIndexArray(void);

	SkinMeshTreeData* GetSkinMeshTree(void);
	void BufferSetIndex(void);

	int GetIndexNum(void);

	Material* GetMaterial(void);
	Material* GetShadowMaterial(void);

	XMFLOAT3 GetPosOffset(void);
	XMFLOAT3 GetSclOffset(void);
	XMFLOAT3 GetRotOffset(void);


private:
	AssetsManager* pAssetsManager;
	Renderer* pRenderer;
	SkinMeshTreeData* skinMeshTree;

	string name;


	SkinMeshVertex* vertexArray;
	int vertNum;
	int* cpIndexArray;
	void CreateVertexArray(int n);
	
	CONTROLPOINT* cpArray;
	int cpNum;
	void CreateCpArray(int n);

	ID3D11Buffer* indexBuffer;
	int indexNum;
	void CreateIndexBuffer(int n);


	SkinMeshData* parent;
	vector <SkinMeshData*> childArray;
	string fileName;
	Material* material;
	Material* shadowMaterial;

	int boneNum;

	XMMATRIX	worldOffset;
	XMMATRIX	localOffset;
	XMFLOAT3	posOffset;
	XMFLOAT3	sclOffset;
	XMFLOAT3	rotOffset;

	vector<string> boneName;
};


class BoneData
{
public:
	BoneData(AssetsManager* p);
	~BoneData();
	void LoadBone(FbxSkeleton* bone, BoneData* parent, SkinMeshTreeData* skinMeshTree);
	vector <BoneData*>& GetChildArray(void);
	string GetName(void);
	
	XMMATRIX GetInitMtxInverse(void);

	XMMATRIX GetWorldOffset(void);
	XMMATRIX GetLocalOffset(void);

	XMFLOAT3 GetPosOffset(void);
	XMFLOAT3 GetSclOffset(void);
	XMFLOAT3 GetRotOffset(void);

private:
	AssetsManager* pAssetsManager;
	SkinMeshTreeData* skinMeshTree;

	BoneData* parent;
	vector <BoneData*> childArray;
	string name;

	XMMATRIX initMatrixInverse;

	XMMATRIX	worldOffset;
	XMMATRIX	localOffset;
	XMFLOAT3	posOffset;
	XMFLOAT3	sclOffset;
	XMFLOAT3	rotOffset;


};

class SkinMeshTreeData
{
public:
	SkinMeshTreeData(AssetsManager* p);
	~SkinMeshTreeData();
	void LoadFbxFile(string fileName);

	AssetsManager* GetAssetsMnager(void);
	string GetFileName(void);

	int GetBoneNum(void);

	vector<SkinMeshData*>& GetRootMeshArray(void);
	BoneData* GetRootBone(void);

	void AddBone(BoneData* bone);

	XMMATRIX GetInitMtx(string name);

private:
	AssetsManager* pAssetsManager;
	vector<BoneData*> boneArray;
	vector<SkinMeshData*>rootMeshArray;
	BoneData* rootBone;
	string fileName;
	string name;
	int boneNum;

	pair<XMMATRIX,string>* linkMtxArray;

};

