#include "SkinMeshComponent.h"
#include "SkinMeshTreeData.h"
#include "renderer.h"
#include "transformcomponent.h"
#include "GameEngine.h"
#include "CBufferManager.h"
#include "Material.h"
#include "SkinMeshLinkerComponent.h"
#include "BoneComponent.h"

#define TEXTURE_PATH	"data/TEXTURE/"

SkinMeshComponent::SkinMeshComponent(GameObject* pGameObject)
{
	this->pGameObject = pGameObject;
}

SkinMeshComponent::~SkinMeshComponent()
{
}

void SkinMeshComponent::Awake(void)
{
	PrimitiveComponent::Awake();

	attribute = Attribute::Primitive;

	cullMode = CULL_MODE::CULL_MODE_BACK;
	this->alphaTest = FALSE;


	hasShadow = TRUE;

}

void SkinMeshComponent::Update(void)
{
	PrimitiveComponent::Update();

}

void SkinMeshComponent::LateUpdate(void)
{
	PrimitiveComponent::LateUpdate();






}

void SkinMeshComponent::Uninit(void)
{
	PrimitiveComponent::Uninit();
	if (vertexArray) delete[]vertexArray;


	if (vertexBuffer) vertexBuffer->Release();
}

void SkinMeshComponent::Draw(void)
{
	PrimitiveComponent::Draw();

	if (this->alphaTest == TRUE)
	{
		this->pRenderer->SetAlphaTestEnable(TRUE);
	}



	this->pRenderer->SetCullingMode((CULL_MODE)cullMode);
	// 頂点バッファ設定
	UINT stride = sizeof(SkinMeshVertex);
	UINT worldOffset = 0;

	this->pRenderer->GetDeviceContext()->IASetVertexBuffers(0, 1, &this->vertexBuffer, &stride, &worldOffset);

	skinMeshData->BufferSetIndex();



	XMMATRIX world = XMMatrixIdentity();
	world = GetTransFormComponent()->GetWorldMtx(world);
	this->pGameEngine->GetCBufferManager()->SetWorldMtx(&world);


	this->material->SetBufferMaterial();

	this->pRenderer->GetDeviceContext()->DrawIndexed(skinMeshData->GetIndexNum(), 0, 0);

	this->pRenderer->SetAlphaTestEnable(FALSE);

}

void SkinMeshComponent::ShadowMapping(void)
{
	PrimitiveComponent::ShadowMapping();

	if (this->alphaTest == TRUE)
	{
		this->pRenderer->SetAlphaTestEnable(TRUE);
	}



	this->pRenderer->SetCullingMode((CULL_MODE)cullMode);
	// 頂点バッファ設定
	UINT stride = sizeof(SkinMeshVertex);
	UINT worldOffset = 0;

	this->pRenderer->GetDeviceContext()->IASetVertexBuffers(0, 1, &this->vertexBuffer, &stride, &worldOffset);

	skinMeshData->BufferSetIndex();



	XMMATRIX world = XMMatrixIdentity();
	world = GetTransFormComponent()->GetWorldMtx(world);
	this->pGameEngine->GetCBufferManager()->SetWorldMtx(&world);


	this->shadowMaterial->SetBufferMaterial();

	this->pRenderer->GetDeviceContext()->DrawIndexed(skinMeshData->GetIndexNum(), 0, 0);

	this->pRenderer->SetAlphaTestEnable(FALSE);


}


void SkinMeshComponent::SetSkinMeshData(SkinMeshData* data, SkinMeshLinkerComponent* linker)
{
	this->skinMeshData = data;
	this->linker = linker;
	this->vertNum = data->GetVertNum();
	CreateVertexArray(vertNum, data->GetVertexArray());

	this->boneCnt = linker->GetBoneCount();




	this->material = data->GetMaterial();
	this->linker->SetMaterial(this->material);

	this->shadowMaterial = data->GetShadowMaterial();
	this->GetTransFormComponent()->SetPosition(data->GetPosOffset());
	this->GetTransFormComponent()->SetRotation(data->GetRotOffset());
	this->GetTransFormComponent()->SetScale(data->GetSclOffset());

	this->GetTransFormComponent()->UpdateMatrix();



}

void SkinMeshComponent::CreateVertexArray(int n, SkinMeshVertex* vertexArray)
{
	this->vertexArray = new SkinMeshVertex[n];
	for (int i = 0; i < n; i++)
	{
		this->vertexArray[i] = vertexArray[i];
	}
	// 頂点バッファ生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(SkinMeshVertex) * n;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	this->pRenderer->GetDevice()->CreateBuffer(&bd, NULL, &this->vertexBuffer);

	// 頂点バッファへのポインタを取得
	D3D11_MAPPED_SUBRESOURCE msr;
	this->pRenderer->GetDeviceContext()->Map(this->vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	SkinMeshVertex* pVtx = (SkinMeshVertex*)msr.pData;

	memcpy(pVtx, this->vertexArray, sizeof(SkinMeshVertex) * n);

	this->pRenderer->GetDeviceContext()->Unmap(this->vertexBuffer, 0);



}
