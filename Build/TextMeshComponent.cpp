#include "TextMeshComponent.h"
#include "renderer.h"
#include "gameobject.h"
#include "GameEngine.h"
#include "Scene.h"
#include "AssetsManager.h"
#include "DX11Texture.h"
#include "UIMaterial.h"
#include "GameEngine.h"
#include "gameobject.h"
#include "AssetsManager.h"
#include "Scene.h"
#include "CBufferManager.h"
#include "RenderTexture.h"

TextMeshComponent::TextMeshComponent(GameObject* gameObject)
{
	pGameObject = gameObject;
}

TextMeshComponent::~TextMeshComponent()
{

}

void TextMeshComponent::Awake(void)
{
	PrimitiveComponent::Awake();
	CreateVertexBuffer();
	this->material = pGameObject->GetScene()->GetGameEngine()->GetAssetsManager()->GetMaterial("UIMaterial");
	SetAlphaTest(TRUE);
}

void TextMeshComponent::Update(void)
{
	PrimitiveComponent::Update();
}

void TextMeshComponent::Uninit(void)
{
	PrimitiveComponent::Uninit();
	if (vertexBuffer) vertexBuffer->Release();
}

void TextMeshComponent::Draw(void)
{
	PrimitiveComponent::Draw();

	//頂点バッファの中身を埋める

	D3D11_MAPPED_SUBRESOURCE msr;
	this->GetGameObject()->GetScene()->GetGameEngine()->GetRenderer()->GetDeviceContext()->Map(this->vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* pVtx = (VERTEX_3D*)msr.pData;

	memcpy(pVtx, vertexArray, sizeof(VERTEX_3D) * 4);

	this->GetGameObject()->GetScene()->GetGameEngine()->GetRenderer()->GetDeviceContext()->Unmap(this->vertexBuffer, 0);


	pRenderer->SetCullingMode(CULL_MODE::CULL_MODE_BACK);
	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;

	pRenderer->GetDeviceContext()->IASetVertexBuffers(0, 1, &this->vertexBuffer, &stride, &offset);
	pRenderer->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	

	pRenderer->GetDeviceContext()->Draw(4, 0);

}

void TextMeshComponent::CreateVertexBuffer(void)
{

	// 頂点バッファ生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	this->pRenderer->GetDevice()->CreateBuffer(&bd, NULL, &this->vertexBuffer);

}


void TextMeshComponent::CreateTextMeshCenter(string text, XMFLOAT3 pos, float width, float height, XMFLOAT4 color)
{
	//this->texIndex = pGameObject->GetScene()->GetGameEngine()->GetAssetsManager()->LoadTexture(texPath);





	XMFLOAT2 screenHW = pGameEngine->GetWindowSize();
	float z = pos.z;

	float w = (width / screenHW.x) * 2.0f;
	float h = (height / screenHW.y) * 2.0f;
	float l = (pos.x / screenHW.x) - w * 0.5;
	float t = (pos.y / screenHW.y) - h * 0.5;





	vertexArray[0].Position = { l,t + h,z };
	vertexArray[0].Diffuse = { color.x,color.y,color.z,color.w };
	vertexArray[0].TexCoord = { 0.0f,0.0f };


	vertexArray[1].Position = { l + w,t + h,z };
	vertexArray[1].Diffuse = { color.x,color.y,color.z,color.w };
	vertexArray[1].TexCoord = { 1.0f,0.0f };

	vertexArray[2].Position = { l,t ,z };
	vertexArray[2].Diffuse = { color.x,color.y,color.z,color.w };
	vertexArray[2].TexCoord = { 0.0f,1.0f };

	vertexArray[3].Position = { l + w ,t,z };
	vertexArray[3].Diffuse = { color.x,color.y,color.z,color.w };
	vertexArray[3].TexCoord = { 1.0f,1.0f };


}

//void TextMeshComponent::CreateTextMeshLeftDown(string text, XMFLOAT3 pos, float width, float height)
//{
//
//	XMFLOAT2 screenHW = pGameEngine->GetWindowSize();
//	float z = pos.z;
//
//	float w = (width / screenHW.x) * 2.0f;
//	float h = (height / screenHW.y) * 2.0f;
//	float l = ((pos.x / screenHW.x) - 0.5f) * 2.0f;
//	float t = ((pos.y / screenHW.y) - 0.5f) * 2.0f;
//
//
//
//
//
//	vertexArray[0].Position = { l,t + h,z };
//	vertexArray[0].Diffuse = { 1.0f,1.0f,1.0f,1.0f };
//	vertexArray[0].TexCoord = { 0.0f,0.0f };
//
//
//	vertexArray[1].Position = { l + w,t + h,z };
//	vertexArray[1].Diffuse = { 1.0f,1.0f,1.0f,1.0f };
//	vertexArray[1].TexCoord = { 1.0f,0.0f };
//
//	vertexArray[2].Position = { l,t ,z };
//	vertexArray[2].Diffuse = { 1.0f,1.0f,1.0f,1.0f };
//	vertexArray[2].TexCoord = { 0.0f,1.0f };
//
//	vertexArray[3].Position = { l + w ,t,z };
//	vertexArray[3].Diffuse = { 1.0f,1.0f,1.0f,1.0f };
//	vertexArray[3].TexCoord = { 1.0f,1.0f };
//
//
//}
//
