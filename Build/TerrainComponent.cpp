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

	this->pRenderer->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_4_CONTROL_POINT_PATCHLIST);
	this->pRenderer->GetDeviceContext()->Draw(4, 0);

	this->pRenderer->SetAlphaTestEnable(FALSE);


}

void TerrainComponent::CreateVetexBuffer(XMFLOAT2 scale,XMFLOAT2 uvScale,XMFLOAT4 color)
{

	// ���_�o�b�t�@����
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	this->pRenderer->GetDevice()->CreateBuffer(&bd, NULL, &this->vertexBuffer);


	VERTEX_3D vert[4];


	vert[0].Position = { -scale.x,0.0f,scale.y };
	vert[0].Normal = { 0.0f,1.0f,0.0 };
	vert[0].Diffuse = color;
	vert[0].TexCoord = { 0.0f,0.0f };


	vert[1].Position = { scale.x,0.0f,scale.y };
	vert[1].Normal = { 0.0f,1.0f,0.0 };
	vert[1].Diffuse = color;
	vert[1].TexCoord = { uvScale.x,0.0f };

	vert[2].Position = { -scale.x,0.0f ,-scale.y };
	vert[2].Normal = { 0.0f,1.0f,0.0 };
	vert[2].Diffuse = color;
	vert[2].TexCoord = { 0.0f,uvScale.y };

	vert[3].Position = { scale.x ,0.0f,-scale.y };
	vert[3].Normal = { 0.0f,1.0f,0.0 };
	vert[3].Diffuse = color;
	vert[3].TexCoord = { uvScale.x,uvScale.y };

	// �^���W�F���g�x�N�g���̌v�Z
	XMFLOAT3 edge1, edge2;
	edge1.x = vert[1].Position.x - vert[0].Position.x;
	edge1.y = vert[1].Position.y - vert[0].Position.y;
	edge1.z = vert[1].Position.z - vert[0].Position.z;

	edge2.x = vert[2].Position.x - vert[0].Position.x;
	edge2.y = vert[2].Position.y - vert[0].Position.y;
	edge2.z = vert[2].Position.z - vert[0].Position.z;

	XMFLOAT2 deltaUV1, deltaUV2;
	deltaUV1.x = vert[1].TexCoord.x - vert[0].TexCoord.x;
	deltaUV1.y = vert[1].TexCoord.y - vert[0].TexCoord.y;

	deltaUV2.x = vert[2].TexCoord.x - vert[0].TexCoord.x;
	deltaUV2.y = vert[2].TexCoord.y - vert[0].TexCoord.y;

	float f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);


	XMFLOAT3 tangent;
	tangent.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
	tangent.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
	tangent.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
	tangent = XMFLOAT3Normalize(tangent);

	// �e���_�Ƀ^���W�F���g�x�N�g����ݒ�
	for (int n = 0; n < 4; n++)
	{
		vert[n].Tangent = tangent;



		XMVECTOR nv = XMLoadFloat3(&vert[n].Normal);
		XMVECTOR tv = XMLoadFloat3(&vert[n].Tangent);

		XMVECTOR binv = XMVector3Cross(nv, tv);
		binv = XMVector3Normalize(binv);

		XMFLOAT3 binor;

		XMStoreFloat3(&binor, binv);

		vert[n].BiNormal = binor;

	}

	vertexArray[0] = vert[0];
	vertexArray[1] = vert[1];
	vertexArray[2] = vert[2];
	vertexArray[3] = vert[3];

	//���_�o�b�t�@�̒��g�𖄂߂�

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
	{//������
		//// ���[���h���W���e�N�X�`�����W�ɕϊ�
		//samplePos.x = pos.x / terrainWidth; // terrainWidth�͒n�`�̕�
		//samplePos.y = pos.z / terrainHeight; // terrainHeight�͒n�`�̍���

		//// �e�N�X�`�����}�b�v���ăf�[�^�ɃA�N�Z�X
		//D3D11_MAPPED_SUBRESOURCE mappedResource;
		//HRESULT hr = pRenderer->GetDeviceContext()->Map(this->heightMap, 0, D3D11_MAP_READ, 0, &mappedResource);
		//if (SUCCEEDED(hr))
		//{
		//	// �e�N�X�`�����獂���̒l���擾
		//	unsigned char* data = reinterpret_cast<unsigned char*>(mappedResource.pData);
		//	int textureWidth = this->heightMapDesc.Width;
		//	int textureHeight = this->heightMapDesc.Height;

		//	// �e�N�X�`�����̃s�N�Z���ʒu���v�Z
		//	int x = static_cast<int>(samplePos.x * textureWidth);
		//	int y = static_cast<int>(samplePos.y * textureHeight);

		//	// ���W���e�N�X�`���͈͓̔��ɂ��邱�Ƃ��m�F
		//	x = max(0, min(x, textureWidth - 1));
		//	y = max(0, min(y, textureHeight - 1));

		//	// �����̒l���擾�i�e�N�X�`���t�H�[�}�b�g��DXGI_FORMAT_R8_UNORM�ł���Ɖ���j
		//	float height = data[y * mappedResource.RowPitch + x] / 255.0f;

		//	// �e�N�X�`���̃A���}�b�v
		//	pRenderer->GetDeviceContext()->Unmap(this->heightMap, 0);

		//	return height;
		//}
	}

	return GetTransFormComponent()->GetWorldPos().y;
}
