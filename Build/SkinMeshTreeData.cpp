#include "SkinMeshTreeData.h"
#include "GameEngine.h"
#include "AssetsManager.h"
#include "DX11Texture.h"
#include "Material.h"
#include "LambartMaterial.h"
#include "PhongMaterial.h"
#include "ShaderSet.h"
#include "SkinMeshShadowMappingMaterial.h"
#include "renderer.h"
#include "SkinMeshPhongMaterial.h"

SkinMeshData::SkinMeshData(AssetsManager* p)
{
	pAssetsManager = p;
}

SkinMeshData::~SkinMeshData()
{
	this->indexBuffer->Release();
	delete[] vertexArray;
	delete[] cpIndexArray;
	for (SkinMeshData* skinmesh:childArray)
	{
		delete skinmesh;
	}
}

void SkinMeshData::LoadSkinMesh(FbxMesh* mesh, SkinMeshData* parent, SkinMeshTreeData* skinMeshTree)
{
	using namespace fbxsdk;
	this->pAssetsManager = skinMeshTree->GetAssetsMnager();
	this->pRenderer = pAssetsManager->GetGameEngine()->GetRenderer();
	this->skinMeshTree = skinMeshTree;
	FbxNode* node = mesh->GetNode();
	name = mesh->GetNode()->GetName();
	fileName = skinMeshTree->GetFileName();
	this->parent = parent;

	int PolygonNum = mesh->GetPolygonCount();               //総ポリゴン数
	if (PolygonNum == 0)
	{
		return;
	}

	int PolygonVertexNum = mesh->GetPolygonVertexCount();   //ポリゴン頂点インデックス数
	//int* indexArray = mesh->GetPolygonVertices();             //ポリゴン頂点インデックス配列

	int controlNum = mesh->GetControlPointsCount();         // 頂点座標数
	FbxVector4* src = mesh->GetControlPoints();             // 頂点座標配列
	CreateVertexArray(PolygonVertexNum);
	unsigned int indexnum = PolygonNum * 3;



	//頂点配列を埋める
	FbxStringList uvSetNameList;
	mesh->GetUVSetNames(uvSetNameList);
	FbxVector2* uv = new FbxVector2[PolygonVertexNum];


	bool bIsUnmapped = false;

	this->boneNum = skinMeshTree->GetBoneNum();


	CreateCpArray(controlNum);
	for (int i = 0; i < controlNum; i++)
	{
		this->cpArray[i].pos.x = (float)src[i][0];
		this->cpArray[i].pos.y = (float)src[i][1];
		this->cpArray[i].pos.z = (float)src[i][2];

		this->cpArray[i].weight = new float[this->boneNum];

		for (int j = 0; j < boneNum; j++)
		{
			cpArray[i].weight[j] = 0.0f;
		}
	}

	FbxSkin* skin = (FbxSkin*)mesh->GetDeformer(0);
	for (int i = 0; i < boneNum; i++)
	{
		FbxCluster* cluster = skin->GetCluster(i);


		FbxAMatrix initmat;
		cluster->GetTransformLinkMatrix(initmat);

		string na = cluster->GetLink()->GetName();

		int pointNum = cluster->GetControlPointIndicesCount();
		int* pointAry = cluster->GetControlPointIndices();
		double* weightAry = cluster->GetControlPointWeights();

		for (int j = 0; j < pointNum; ++j)
		{


			// 頂点インデックスとウェイトを取得
			int   index = pointAry[j];
			float weight = (float)weightAry[j];
			this->cpArray[index].weight[i] = weight;


		}


	}



	int vcnt = 0;

	for (int p = 0; p < PolygonNum; p++)
	{



		int IndexNumInPolygon = mesh->GetPolygonSize(p);  // p番目のポリゴンの頂点数



		if (IndexNumInPolygon == 3)
		{
			FbxVector4 positions[3];
			FbxVector4 normals[3];
			FbxVector2 uvs[3];

			for (int n = 0; n < IndexNumInPolygon; n++)
			{
				FbxVector4 nor;

				mesh->GetPolygonVertexNormal(
					p,				// ポリゴン番号
					n,				// 何番目の頂点
					nor);			// 法線の
				vertexArray[vcnt].Normal.x = (float)nor[0];
				vertexArray[vcnt].Normal.y = (float)nor[1];
				vertexArray[vcnt].Normal.z = (float)nor[2];

				normals[n] = nor;

				// UV値取得。
				FbxString name = uvSetNameList.GetStringAt(0);
				mesh->GetPolygonVertexUV(p, n, name, uv[vcnt], bIsUnmapped);
				vertexArray[vcnt].TexCoord.x = (float)uv[vcnt][0];
				vertexArray[vcnt].TexCoord.y = 1.0f - (float)uv[vcnt][1];

				uvs[n] = uv[vcnt];


				//// ポリゴンpを構成するn番目の頂点のインデックス番号
				int IndexNumber = mesh->GetPolygonVertex(p, n);
				vertexArray[vcnt].Position = cpArray[IndexNumber].pos;



				float boneWeight[4] = { 0.0f,0.0f,0.0f,0.0f };
				int boneIndex[4] = { -1,-1,-1,-1 };
				for (int i = 0; i < 4; i++)
				{
					float maxWeight = 0.001f;
					int index = -1;
					for (int j = 0; j < boneNum; j++)
					{
						if (j == boneIndex[0] || j == boneIndex[1] || j == boneIndex[2] || j == boneIndex[3])
							continue;

						if (maxWeight < cpArray[IndexNumber].weight[j])
						{
							maxWeight = cpArray[IndexNumber].weight[j];
							index = j;
						}

					}
					if (index != -1)
					{
						boneWeight[i] = maxWeight;
						boneIndex[i] = index;


					}
				}



				vertexArray[vcnt].BoneWeight.x = boneWeight[0];
				vertexArray[vcnt].BoneIndex.x = (unsigned int)boneIndex[0];
				
				vertexArray[vcnt].BoneWeight.y = boneWeight[1];
				vertexArray[vcnt].BoneIndex.y = (unsigned int)boneIndex[1];
				
				vertexArray[vcnt].BoneWeight.z = boneWeight[2];
				vertexArray[vcnt].BoneIndex.z = (unsigned int)boneIndex[2];
				
				vertexArray[vcnt].BoneWeight.w = boneWeight[3];
				vertexArray[vcnt].BoneIndex.w = (unsigned int)boneIndex[3];
				
				positions[n] = src[IndexNumber];

				this->cpIndexArray[vcnt] = IndexNumber;


				vertexArray[vcnt].Diffuse = { 1.0f,1.0f,1.0f,1.0f };

				vcnt++;

			}


			// タンジェントベクトルの計算
			FbxVector4 edge1 = positions[1] - positions[0];
			FbxVector4 edge2 = positions[2] - positions[0];
			FbxVector2 deltaUV1 = uvs[1] - uvs[0];
			FbxVector2 deltaUV2 = uvs[2] - uvs[0];

			float f = 1.0f / (float)(deltaUV1[0] * deltaUV2[1] - deltaUV2[0] * deltaUV1[1]);

			FbxVector4 tangent;
			tangent[0] = f * (deltaUV2[1] * edge1[0] - deltaUV1[1] * edge2[0]);
			tangent[1] = f * (deltaUV2[1] * edge1[1] - deltaUV1[1] * edge2[1]);
			tangent[2] = f * (deltaUV2[1] * edge1[2] - deltaUV1[1] * edge2[2]);
			tangent[3] = 0.0f;

			// 各頂点にタンジェントベクトルを設定
			for (int n = 0; n < IndexNumInPolygon; n++)
			{
				vertexArray[vcnt - IndexNumInPolygon + n].Tangent.x = (float)tangent[0];
				vertexArray[vcnt - IndexNumInPolygon + n].Tangent.y = (float)tangent[1];
				vertexArray[vcnt - IndexNumInPolygon + n].Tangent.z = (float)tangent[2];
				vertexArray[vcnt - IndexNumInPolygon + n].Tangent = XMFLOAT3Normalize(vertexArray[vcnt - IndexNumInPolygon + n].Tangent);



				XMVECTOR nv = XMLoadFloat3(&vertexArray[vcnt - IndexNumInPolygon + n].Normal);
				XMVECTOR tv = XMLoadFloat3(&vertexArray[vcnt - IndexNumInPolygon + n].Tangent);

				XMVECTOR binv = XMVector3Cross(nv, tv);
				binv = XMVector3Normalize(binv);

				XMFLOAT3 binor;

				XMStoreFloat3(&binor, binv);

				vertexArray[vcnt - IndexNumInPolygon + n].BiNormal = binor;

			}

		}

	}

	//インデックス配列を埋める
	unsigned int* indexArray = nullptr;
	indexArray = new unsigned int[indexnum];
	int ic = 0;

	for (int i = 0; i < PolygonNum; i++)
	{

		indexArray[i * 3 ] = ic;
		ic++;
		indexArray[i * 3 + 1] = ic;
		ic++;
		indexArray[i * 3 + 2] = ic;
		ic++;
	}


	// インデックスバッファ生成
	this->CreateIndexBuffer(indexnum);

	{//インデックスバッファの中身を埋める

		// インデックスバッファのポインタを取得
		D3D11_MAPPED_SUBRESOURCE msr;
		this->pAssetsManager->GetGameEngine()->GetRenderer()->GetDeviceContext()->Map(this->indexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

		unsigned int* pIdx = (unsigned int*)msr.pData;


		for (unsigned int i = 0; i < indexnum; i++)
		{
			pIdx[i] = indexArray[i];
		}

		this->pAssetsManager->GetGameEngine()->GetRenderer()->GetDeviceContext()->Unmap(this->indexBuffer, 0);
	}



	FbxMatrix worldOffset = node->EvaluateGlobalTransform(FBXSDK_TIME_INFINITE);//オフセット行列の取得
	this->worldOffset = FbxMatrixConvertToXMMATRIX(worldOffset);

	FbxMatrix localOffset = node->EvaluateLocalTransform(FBXSDK_TIME_INFINITE);
	this->localOffset = FbxMatrixConvertToXMMATRIX(localOffset);

	FbxVector4 pos = node->EvaluateLocalTranslation(FBXSDK_TIME_INFINITE);
	FbxVector4 scl = node->EvaluateLocalScaling(FBXSDK_TIME_INFINITE);
	FbxVector4 rot = node->EvaluateLocalRotation(FBXSDK_TIME_INFINITE);

	this->posOffset.x = (float)pos[0];
	this->posOffset.y = (float)pos[1];
	this->posOffset.z = (float)pos[2];

	this->sclOffset.x = (float)scl[0];
	this->sclOffset.y = (float)scl[1];
	this->sclOffset.z = (float)scl[2];

	this->rotOffset.x = (float)rot[0];
	this->rotOffset.y = (float)rot[1];
	this->rotOffset.z = (float)rot[2];

	// マテリアルの数

	int mtlcnt = node->GetMaterialCount();


	// マテリアル情報を取得
	for (int i = 0; i < mtlcnt; i++)
	{
		FbxSurfaceMaterial* fbxmaterial = node->GetMaterial(i);

		FbxClassId id = fbxmaterial->GetClassId();

		if (fbxmaterial != 0)
		{
			// マテリアル解析
			// LambertかPhongか
			//lambart



			if (id == (FbxSurfaceLambert::ClassId))
			{

				LambartMaterial* lambart = new LambartMaterial(this->pAssetsManager);

				lambart->LoadFbxMaterial(fbxmaterial);

				lambart->SetName(this->fileName + fbxmaterial->GetName());

				this->material = pAssetsManager->LoadMaterial(lambart);


			}
			//phong
			else if (id == (FbxSurfacePhong::ClassId))
			{

				SkinMeshPhongMaterial* phong = new SkinMeshPhongMaterial(this->pAssetsManager);

				phong->LoadFbxMaterial(fbxmaterial);

				phong->SetName(this->fileName + fbxmaterial->GetName());


				this->material = pAssetsManager->LoadMaterial(phong);


			}
			else
			{

			}
			SkinMeshShadowMappingMaterial* shadowMat = new SkinMeshShadowMappingMaterial(this->pAssetsManager);

			shadowMat->SetShadowMaterial(this->material);

			this->shadowMaterial = pAssetsManager->LoadMaterial(shadowMat);



		}
	}
	delete[] uv;
	delete[] indexArray;
	for (int i = 0; i < node->GetChildCount(); i++)
	{
		FbxNode* child = node->GetChild(i);

		if (child->GetNodeAttribute()->GetAttributeType() == FbxNodeAttribute::eMesh)
		{
			SkinMeshData* childData = new SkinMeshData(pAssetsManager);
			childData->LoadSkinMesh(child->GetMesh(), this, skinMeshTree);
			childArray.push_back(childData);

		}



	}


}

vector<SkinMeshData*>& SkinMeshData::GetChildArray(void)
{
	return childArray;
}

string SkinMeshData::GetName(void)
{
	return this->name;
}

ID3D11Buffer* SkinMeshData::GetIndexBuffer(void)
{
	return this->indexBuffer;
}

int SkinMeshData::GetCotrolPointNum(void)
{
	return this->cpNum;
}

CONTROLPOINT* SkinMeshData::GetControlPoint(void)
{
	return cpArray;
}

int SkinMeshData::GetVertNum(void)
{
	return this->vertNum;
}

SkinMeshVertex* SkinMeshData::GetVertexArray(void)
{
	return this->vertexArray;
}

int* SkinMeshData::GetCPIndexArray(void)
{
	return cpIndexArray;
}

SkinMeshTreeData* SkinMeshData::GetSkinMeshTree(void)
{
	return this->skinMeshTree;
}

void SkinMeshData::CreateVertexArray(int n)
{
	this->vertNum = n;
	this->cpIndexArray = new int[n];
	this->vertexArray = new SkinMeshVertex[n];
}

void SkinMeshData::CreateCpArray(int n)
{
	this->cpArray = new CONTROLPOINT[n];
	this->cpNum = n;

}

void SkinMeshData::CreateIndexBuffer(int n)
{
	this->indexNum = n;
	// インデックスバッファ生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(unsigned int) * n;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	this->pAssetsManager->GetGameEngine()->GetRenderer()->GetDevice()->CreateBuffer(&bd, NULL, &this->indexBuffer);

}

void SkinMeshData::BufferSetIndex(void)
{

	// プリミティブトポロジ設定
	this->pAssetsManager->GetGameEngine()->GetRenderer()->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// インデックスバッファ設定
	this->pAssetsManager->GetGameEngine()->GetRenderer()->GetDeviceContext()->IASetIndexBuffer(this->indexBuffer, DXGI_FORMAT_R32_UINT, 0);

}

int SkinMeshData::GetIndexNum(void)
{
	return this->indexNum;
}

Material* SkinMeshData::GetMaterial(void)
{
	return this->material;
}

Material* SkinMeshData::GetShadowMaterial(void)
{
	return this->shadowMaterial;
}

XMFLOAT3 SkinMeshData::GetPosOffset(void)
{
	return this->posOffset;
}

XMFLOAT3 SkinMeshData::GetSclOffset(void)
{
	return this->sclOffset;
}

XMFLOAT3 SkinMeshData::GetRotOffset(void)
{
	return this->rotOffset;
}



SkinMeshTreeData::SkinMeshTreeData(AssetsManager* p)
{
	pAssetsManager = p;
}

SkinMeshTreeData::~SkinMeshTreeData()
{
	delete rootBone;
	for (SkinMeshData* skinmesh : rootMeshArray)
	{
		delete skinmesh;
	}
}

void SkinMeshTreeData::LoadFbxFile(string fileName)
{
	this->fileName = fileName;
	this->name = fileName + "root";
	FbxManager* manager;
	FbxIOSettings* ioSettings;
	manager = FbxManager::Create();
	ioSettings = FbxIOSettings::Create(manager, IOSROOT);
	// Importerを生成
	FbxImporter* importer = FbxImporter::Create(manager, "");

	if (importer->Initialize(fileName.c_str(), -1, manager->GetIOSettings()) == false)
	{
		// インポートエラー
	}

	//SceneオブジェクトにFBXファイル内の情報を流し込む
	FbxScene* scene = FbxScene::Create(manager, "scene");
	importer->Import(scene);
	importer->Destroy(); // シーンを流し込んだらImporterは解放

	FbxNode* root = scene->GetRootNode();

	this->boneNum = scene->GetSrcObjectCount<FbxSkeleton>();

	this->linkMtxArray = new pair<XMMATRIX, string>[boneNum];
	FbxSkin* skin = scene->GetSrcObject<FbxSkin>(0);

	for (int i = 0; i < boneNum; i++)
	{
		FbxCluster* cluster = skin->GetCluster(i);


		FbxAMatrix initmat;
		cluster->GetTransformLinkMatrix(initmat);

		linkMtxArray[i].second = cluster->GetLink()->GetName();

		linkMtxArray[i].first = FbxMatrixConvertToXMMATRIX(initmat);

	}
	for (int i = 0; i < root->GetChildCount(); i++)
	{
		FbxNode* child = root->GetChild(i);

		if (child->GetNodeAttribute()->GetAttributeType() == FbxNodeAttribute::eMesh)
		{
			SkinMeshData* childData = new SkinMeshData(pAssetsManager);
			childData->LoadSkinMesh(child->GetMesh(), nullptr, this);
			rootMeshArray.push_back(childData);

		}
		if (child->GetNodeAttribute()->GetAttributeType() == FbxNodeAttribute::eSkeleton)
		{
			BoneData* childData = new BoneData(pAssetsManager);
			childData->LoadBone(child->GetSkeleton(), nullptr, this);
			rootBone = childData;

		}



	}






	scene->Destroy();
	manager->Destroy();//fbxファイルの読み込みが終わったらマネージャーは解放する


}

AssetsManager* SkinMeshTreeData::GetAssetsMnager(void)
{
	return this->pAssetsManager;
}

string SkinMeshTreeData::GetFileName(void)
{
	return fileName;
}

int SkinMeshTreeData::GetBoneNum(void)
{
	return this->boneNum;
}

vector<SkinMeshData*>& SkinMeshTreeData::GetRootMeshArray(void)
{
	return rootMeshArray;
}

BoneData* SkinMeshTreeData::GetRootBone(void)
{
	return rootBone;
}

void SkinMeshTreeData::AddBone(BoneData* bone)
{
	boneArray.push_back(bone);
}

XMMATRIX SkinMeshTreeData::GetInitMtx(string name)
{
	for (int i = 0; i < boneNum; i++)
	{
		if (linkMtxArray[i].second==name)
		{
			return linkMtxArray[i].first;
		}
	}

	return XMMatrixIdentity();
}

BoneData::BoneData(AssetsManager* p)
{ 
	this->pAssetsManager = p;
}

BoneData::~BoneData()
{
	for (BoneData* data : childArray)
	{
		delete data;
	}
}

void BoneData::LoadBone(FbxSkeleton* bone, BoneData* parent, SkinMeshTreeData* skinMeshTree)
{
	using namespace fbxsdk;

	this->skinMeshTree = skinMeshTree;
	FbxNode* node = bone->GetNode();

	this->name = node->GetName();

	//FbxMatrix worldOffset = node->EvaluateGlobalTransform(FBXSDK_TIME_INFINITE);//オフセット行列の取得
	//this->worldOffset = FbxMatrixConvertToXMMATRIX(worldOffset);


	this->worldOffset = skinMeshTree->GetInitMtx(this->name);

	FbxMatrix localOffset = node->EvaluateLocalTransform(FBXSDK_TIME_INFINITE);
	this->localOffset = FbxMatrixConvertToXMMATRIX(localOffset);

	FbxVector4 pos = node->EvaluateLocalTranslation(FBXSDK_TIME_INFINITE);
	FbxVector4 scl = node->EvaluateLocalScaling(FBXSDK_TIME_INFINITE);
	FbxVector4 rot = node->EvaluateLocalRotation(FBXSDK_TIME_INFINITE);

	this->posOffset.x = (float)pos[0];
	this->posOffset.y = (float)pos[1];
	this->posOffset.z = (float)pos[2];

	this->sclOffset.x = (float)scl[0];
	this->sclOffset.y = (float)scl[1];
	this->sclOffset.z = (float)scl[2];

	this->rotOffset.x = (float)(rot[0] / 180.0) * XM_PI;
	this->rotOffset.y = (float)(rot[1] / 180.0) * XM_PI;
	this->rotOffset.z = (float)(rot[2] / 180.0) * XM_PI;



	XMMATRIX invMat = XMMatrixInverse(nullptr, this->localOffset);

	if (parent==nullptr)
	{
		initMatrixInverse = invMat;
	}
	else
	{
		initMatrixInverse = XMMatrixMultiply(invMat, parent->GetInitMtxInverse());

	}

	//initMatrixInverse = XMMatrixInverse(nullptr, this->worldOffset);

	skinMeshTree->AddBone(this);

	for (int i = 0; i < node->GetChildCount(); i++)
	{
		FbxNode* child = node->GetChild(i);

		if (child->GetNodeAttribute()->GetAttributeType() == FbxNodeAttribute::eSkeleton)
		{
			BoneData* childData = new BoneData(pAssetsManager);
			childData->LoadBone(child->GetSkeleton(), this, skinMeshTree);
			childArray.push_back(childData);

		}



	}

}

vector<BoneData*>& BoneData::GetChildArray(void)
{
	return childArray;
}

string BoneData::GetName(void)
{
	return this->name;
}

XMMATRIX BoneData::GetInitMtxInverse(void)
{
	return this->initMatrixInverse;
}

XMMATRIX BoneData::GetWorldOffset(void)
{
	return this->worldOffset;
}

XMMATRIX BoneData::GetLocalOffset(void)
{
	return this->localOffset;
}

XMFLOAT3 BoneData::GetPosOffset(void)
{
	return this->posOffset;
}

XMFLOAT3 BoneData::GetSclOffset(void)
{
	return this->sclOffset;
}

XMFLOAT3 BoneData::GetRotOffset(void)
{
	return this->rotOffset;
}

