#include "SkinMeshLinkerComponent.h"
#include "SkinMeshTreeData.h"
#include "SkinMeshComponent.h"
#include "BoneComponent.h"
#include "transformcomponent.h"
#include "renderer.h"
#include "CBufferManager.h"
#include "GameEngine.h"
#include "AssetsManager.h"
#include "gameobject.h"
SkinMeshLinkerComponent::SkinMeshLinkerComponent(GameObject* gameObject)
{
	pGameObject = gameObject;
}

SkinMeshLinkerComponent::~SkinMeshLinkerComponent()
{
}

void SkinMeshLinkerComponent::Awake(void)
{
	PrimitiveComponent::Awake();
	pRenderer = pGameEngine->GetRenderer();
	pCBufferManager = pGameEngine->GetCBufferManager();
	boneMtxArray = new XMMATRIX[BONE_MAX];

	skinMeshShader = pGameEngine->GetAssetsManager()->GetSkinMeshShader();

}


void SkinMeshLinkerComponent::Update(void)
{
	PrimitiveComponent::Update();


}

void SkinMeshLinkerComponent::LateUpdate(void)
{
	PrimitiveComponent::LateUpdate();

	for (int i = 0; i < boneArray.size(); i++)
	{
		boneMtxArray[i] = boneArray[i]->GetBoneMtx();
	}


}

void SkinMeshLinkerComponent::Draw(void)
{
	PrimitiveComponent::Draw();
	skinMeshShader->SetBoneBuffer(boneMtxArray);
}

void SkinMeshLinkerComponent::ShadowMapping(void)
{
	PrimitiveComponent::ShadowMapping();
	skinMeshShader->SetBoneBuffer(boneMtxArray);
}

void SkinMeshLinkerComponent::Uninit(void)
{
	PrimitiveComponent::Uninit();
}

void SkinMeshLinkerComponent::AddBone(BoneComponent* bone)
{
	boneArray.push_back(bone);
}

vector<BoneComponent*>& SkinMeshLinkerComponent::GetBoneArray(void)
{
	return boneArray;
}

int SkinMeshLinkerComponent::GetBoneCount(void)
{
	return this->boneCount;
}

void SkinMeshLinkerComponent::SetBoneCount(int cnt)
{
	boneCount = cnt;
}

