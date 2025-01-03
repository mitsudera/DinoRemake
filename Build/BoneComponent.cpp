#include "BoneComponent.h"
#include "SkinMeshTreeData.h"
#include "SkinMeshLinkerComponent.h"
#include "transformcomponent.h"
#include "gameobject.h"
#include "GameEngine.h"
#include "DebugUtility.h"
#include "CBufferManager.h"
BoneComponent::BoneComponent(GameObject* gameObject)
{
	pGameObject = gameObject;
}
BoneComponent::~BoneComponent()
{
}
void BoneComponent::LateUpdate(void)
{
	Component::LateUpdate();

}
void BoneComponent::DebugDraw(void)
{

	XMMATRIX world = XMMatrixIdentity();
	world = GetTransFormComponent()->GetWorldMtx(world);
	this->pGameEngine->GetCBufferManager()->SetWorldMtx(&world);

	pGameEngine->GetDebugUtility()->DrawDebugBox();

}
XMMATRIX BoneComponent::GetInitMtxInverse(void)
{
	return this->initMtxInv;
}
void BoneComponent::SetBone(BoneData* data, SkinMeshLinkerComponent* linker)
{

	this->GetTransFormComponent()->SetLocalMtx(data->GetLocalOffset());

	this->initMtx = data->GetWorldOffset();
	this->initMtxInv = XMMatrixInverse(nullptr,initMtx);

	this->linker = linker;


	this->GetTransFormComponent()->UpdateMatrix();

	//this->initMtxInv = XMMatrixInverse(nullptr, GetTransFormComponent()->GetWorldMtx());


	linker->AddBone(this);

}

XMMATRIX& BoneComponent::GetBoneMtx(void)
{
	initMtx;
	XMMATRIX mtx = GetWorldMtx();
	XMFLOAT3 p = GetWorldPos();
	boneMtx = XMMatrixTranspose(XMMatrixMultiply(initMtxInv, GetWorldMtx()));
	this;
	return boneMtx;
}
