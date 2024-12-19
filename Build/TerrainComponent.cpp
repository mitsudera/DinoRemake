#include "TerrainComponent.h"
#include "renderer.h"
#include "gameobject.h"
#include "transformcomponent.h"
#include "CBufferManager.h"
#include "AssetsManager.h"
#include "Material.h"
TerrainComponent::TerrainComponent(GameObject* gameObject)
{
	pGameObject = gameObject;
}

TerrainComponent::~TerrainComponent()
{
}

void TerrainComponent::Awake(void)
{
	PrimitiveComponent::Awake();

}

void TerrainComponent::Update(void)
{
	PrimitiveComponent::Update();

}

void TerrainComponent::Uninit(void)
{
	PrimitiveComponent::Uninit();
	
	if (vertexBuffer) vertexBuffer->Release();
}

void TerrainComponent::Draw(void)
{
	PrimitiveComponent::Draw();
	if (this->alphaTest == TRUE)
	{
		this->pRenderer->SetAlphaTestEnable(TRUE);
	}



	this->pRenderer->SetCullingMode(CULL_MODE::CULL_MODE_BACK);

	UINT stride = sizeof(VERTEX_3D);
	UINT worldOffset = 0;

	pRenderer->GetDeviceContext()->IASetVertexBuffers(0, 1, &this->vertexBuffer, &stride, &worldOffset);
	XMMATRIX world = XMMatrixIdentity();
	world = this->pGameObject->GetTransFormComponent()->GetWorldMtx(world);
	pCBufferManager->SetWorldMtx(&world);


	pAssetsManager->GetMaterial(this->materialIndex)->SetBufferMaterial();

	this->pRenderer->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	this->pRenderer->GetDeviceContext()->Draw(4, 0);

	this->pRenderer->SetAlphaTestEnable(FALSE);


}

void TerrainComponent::CreateVetexBuffer(XMFLOAT2 scale,XMFLOAT2 uvScale,XMFLOAT4 color)
{

	// 頂点バッファ生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	this->pRenderer->GetDevice()->CreateBuffer(&bd, NULL, &this->vertexBuffer);



	vertexArray[0].Position = { -scale.x,0.0f,scale.y };
	vertexArray[0].Normal = { 0.0f,1.0f,0.0 };
	vertexArray[0].Diffuse = color;
	vertexArray[0].TexCoord = { 0.0f,0.0f };


	vertexArray[1].Position = { scale.x,0.0f,scale.y };
	vertexArray[1].Normal = { 0.0f,1.0f,0.0 };
	vertexArray[1].Diffuse = color;
	vertexArray[1].TexCoord = { uvScale.x,0.0f };

	vertexArray[2].Position = { -scale.x,0.0f ,-scale.y };
	vertexArray[2].Normal = { 0.0f,1.0f,0.0 };
	vertexArray[2].Diffuse = color;
	vertexArray[2].TexCoord = { 0.0f,uvScale.y };

	vertexArray[3].Position = { scale.x ,0.0f,-scale.y };
	vertexArray[3].Normal = { 0.0f,1.0f,0.0 };
	vertexArray[3].Diffuse = color;
	vertexArray[3].TexCoord = { uvScale.x,uvScale.y };

	// タンジェントベクトルの計算
	XMFLOAT3 edge1, edge2;
	edge1.x = vertexArray[1].Position.x - vertexArray[0].Position.x;
	edge1.y = vertexArray[1].Position.y - vertexArray[0].Position.y;
	edge1.z = vertexArray[1].Position.z - vertexArray[0].Position.z;

	edge2.x = vertexArray[2].Position.x - vertexArray[0].Position.x;
	edge2.y = vertexArray[2].Position.y - vertexArray[0].Position.y;
	edge2.z = vertexArray[2].Position.z - vertexArray[0].Position.z;

	XMFLOAT2 deltaUV1, deltaUV2;
	deltaUV1.x = vertexArray[1].TexCoord.x - vertexArray[0].TexCoord.x;
	deltaUV1.y = vertexArray[1].TexCoord.y - vertexArray[0].TexCoord.y;

	deltaUV2.x = vertexArray[2].TexCoord.x - vertexArray[0].TexCoord.x;
	deltaUV2.y = vertexArray[2].TexCoord.y - vertexArray[0].TexCoord.y;

	float f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);


	XMFLOAT3 tangent;
	tangent.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
	tangent.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
	tangent.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
	tangent = XMFLOAT3Normalize(tangent);

	// 各頂点にタンジェントベクトルを設定
	for (int n = 0; n < 4; n++)
	{
		vertexArray[n].Tangent = tangent;



		XMVECTOR nv = XMLoadFloat3(&vertexArray[n].Normal);
		XMVECTOR tv = XMLoadFloat3(&vertexArray[n].Tangent);

		XMVECTOR binv = XMVector3Cross(nv, tv);
		binv = XMVector3Normalize(binv);

		XMFLOAT3 binor;

		XMStoreFloat3(&binor, binv);

		vertexArray[n].BiNormal = binor;

	}


	//頂点バッファの中身を埋める

	D3D11_MAPPED_SUBRESOURCE msr;
	this->pRenderer->GetDeviceContext()->Map(this->vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* pVtx = (VERTEX_3D*)msr.pData;

	memcpy(pVtx, vertexArray, sizeof(VERTEX_3D) * 4);

	this->pRenderer->GetDeviceContext()->Unmap(this->vertexBuffer, 0);

}

ID3D11Texture2D* TerrainComponent::GetHeightMap(void)
{
	if (this->heightMap)
	{
		return this->heightMap;
	}
	return nullptr;
}

float TerrainComponent::GetHeight(XMFLOAT3 pos)
{
	XMFLOAT2 samplePos;
	if (this->heightMap)
	{//未完成
		//// ワールド座標をテクスチャ座標に変換
		//samplePos.x = pos.x / terrainWidth; // terrainWidthは地形の幅
		//samplePos.y = pos.z / terrainHeight; // terrainHeightは地形の高さ

		//// テクスチャをマップしてデータにアクセス
		//D3D11_MAPPED_SUBRESOURCE mappedResource;
		//HRESULT hr = pRenderer->GetDeviceContext()->Map(this->heightMap, 0, D3D11_MAP_READ, 0, &mappedResource);
		//if (SUCCEEDED(hr))
		//{
		//	// テクスチャから高さの値を取得
		//	unsigned char* data = reinterpret_cast<unsigned char*>(mappedResource.pData);
		//	int textureWidth = this->heightMapDesc.Width;
		//	int textureHeight = this->heightMapDesc.Height;

		//	// テクスチャ内のピクセル位置を計算
		//	int x = static_cast<int>(samplePos.x * textureWidth);
		//	int y = static_cast<int>(samplePos.y * textureHeight);

		//	// 座標がテクスチャの範囲内にあることを確認
		//	x = max(0, min(x, textureWidth - 1));
		//	y = max(0, min(y, textureHeight - 1));

		//	// 高さの値を取得（テクスチャフォーマットがDXGI_FORMAT_R8_UNORMであると仮定）
		//	float height = data[y * mappedResource.RowPitch + x] / 255.0f;

		//	// テクスチャのアンマップ
		//	pRenderer->GetDeviceContext()->Unmap(this->heightMap, 0);

		//	return height;
		//}
	}

	return GetTransFormComponent()->GetWorldPos().y;
}
