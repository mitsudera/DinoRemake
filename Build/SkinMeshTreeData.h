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

class SkinMeshTreeNode
{
public:
	enum class Attribute :int
	{
		Root,
		Null,
		Mesh,
		Bone,
	};

	SkinMeshTreeNode();
	~SkinMeshTreeNode();

	virtual void LoadNode(FbxNode* node, SkinMeshTreeNode* parent, SkinMeshTreeData* skinMeshTree);
	void LoadChild(FbxNode* node);

	string GetName(void);
	vector<SkinMeshTreeNode*>& GetChildArray(void);

	Attribute GetAttribute(void);

	virtual void Destroy(void);

protected:
	AssetsManager* pAssetsManager;
	Renderer* pRenderer;

	SkinMeshTreeData* skinMeshTree;

	vector <SkinMeshTreeNode*> childArray;
	string name;
	SkinMeshTreeNode* parent;
	string fileName;
	XMMATRIX	worldOffset;
	XMMATRIX	localOffset;
	XMFLOAT3	posOffset;
	XMFLOAT3	sclOffset;
	XMFLOAT3	rotOffset;
	Attribute nodeAttribute;
};

class SkinMeshData:public SkinMeshTreeNode
{
public:
	SkinMeshData(AssetsManager* p);
	~SkinMeshData();
	//void LoadSkinMesh(FbxMesh* mesh, SkinMeshData* parent,SkinMeshTreeData* skinMeshTree);
	virtual void LoadNode(FbxNode* node, SkinMeshTreeNode* parent, SkinMeshTreeData* skinMeshTree) override;


	virtual void Destroy(void)override;


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


	Material* material;
	Material* shadowMaterial;

	int boneNum;


};


class BoneData :public SkinMeshTreeNode
{
public:
	BoneData(AssetsManager* p);
	~BoneData();
	//void LoadBone(FbxSkeleton* bone, BoneData* parent, SkinMeshTreeData* skinMeshTree);
	virtual void LoadNode(FbxNode* node, SkinMeshTreeNode* parent, SkinMeshTreeData* skinMeshTree) override;

	

	XMMATRIX GetWorldOffset(void);
	XMMATRIX GetLocalOffset(void);

	XMFLOAT3 GetPosOffset(void);
	XMFLOAT3 GetSclOffset(void);
	XMFLOAT3 GetRotOffset(void);

private:

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

	vector<SkinMeshTreeNode*>& GetNodeArray(void);

	XMMATRIX GetInitMtx(string name);

private:
	AssetsManager* pAssetsManager;
	vector<SkinMeshTreeNode*> nodeArray;
	string fileName;
	string name;
	int boneNum;

	pair<XMMATRIX,string>* linkMtxArray;

};

