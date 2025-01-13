#pragma once
#include "PrimitiveComponent.h"
#include "LambartMaterial.h"
#include "PhongMaterial.h"
#include "UIMaterial.h"
#include "GameEngine.h"
#include "Material.h"
#include "AssetsManager.h"
#include "renderer.h"
#include "gameobject.h"
#include "Scene.h"
#include "ShadowMap.h"
#include "transformcomponent.h"
PrimitiveComponent::PrimitiveComponent()
{
	
}

PrimitiveComponent::PrimitiveComponent(GameObject* gameObject)
{
	this->pGameObject = gameObject;

}

PrimitiveComponent::~PrimitiveComponent()
{
	
}

void PrimitiveComponent::Awake(void)
{
	Component::Awake();
	this->pRenderer = pGameEngine->GetRenderer();
	this->pCBufferManager = pGameEngine->GetCBufferManager();
	this->pAssetsManager = pGameEngine->GetAssetsManager();

	this->pGameObject->GetScene()->AddScenePrimitiveComponent(this);
	attribute = Attribute::Primitive;
	alphaTest = FALSE;
	hasShadow = TRUE;
	drawShadow = TRUE;

	isFrustumCulling = FALSE;
}

void PrimitiveComponent::Update(void)
{
	Component::Update();
}

void PrimitiveComponent::Uninit(void)
{
	Component::Uninit();
	this->pGameObject->GetScene()->RemoveScenePrimitiveComponent(this);

}



void PrimitiveComponent::Draw(void)
{
	Component::Draw();



	pRenderer->SetAlphaTestEnable(this->alphaTest);
	if (this->alphaTest)
	{
		pRenderer->SetBlendState(BLEND_MODE::BLEND_MODE_ALPHABLEND);

	}
	if (drawShadow)
	{
		pGameEngine->GetShadowMap()->SetEnable(TRUE);
	}
	else
	{
		pGameEngine->GetShadowMap()->SetEnable(FALSE);

	}
}

void PrimitiveComponent::ShadowMapping(void)
{
	if (!hasShadow)
		return;
}

Material* PrimitiveComponent::GetMaterial(void)
{
	return this->material;
}

void PrimitiveComponent::SetMaterial(Material* matelial)
{
	this->material = matelial;
}

Material* PrimitiveComponent::LoadMaterial(Material* material)
{

	this->material = pGameEngine->GetAssetsManager()->LoadMaterial(material);
	return this->material;
}

Material* PrimitiveComponent::GetShadowMaterial(void)
{
	return this->shadowMaterial;
}

void PrimitiveComponent::SetCullingMode(int cullMode)
{
	this->cullMode = cullMode;
}

int PrimitiveComponent::GetCullingMode(void)
{
	return this->cullMode;
}

void PrimitiveComponent::SetAlphaTest(BOOL enable)
{
	this->alphaTest = enable;
}

BOOL PrimitiveComponent::GetAlphaTest(void)
{
	return this->alphaTest;
}

BOOL PrimitiveComponent::GetIsFrustumCulling(XMMATRIX frustum)
{
	if (!isFrustumCulling)
	{
		return FALSE;
	}


	// サイズをワールド座標に変換

	XMMATRIX wvp = GetWorldMtx() * frustum;

	if (IsInsideFrustum(XMVector3Transform(pivot, GetTransFormComponent()->GetLocalMtx()), XMLoadFloat3(&size), wvp))
	{
		return FALSE;

	}


	return TRUE;
}



void PrimitiveComponent::SetBoxCenterSize(std::vector<XMFLOAT3> vertices)
{
	isFrustumCulling = TRUE;

	if (vertices.empty())
	{
		pivot = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
		size = XMFLOAT3(0.0f, 0.0f, 0.0f);
		return;
	}

	XMFLOAT3 minPoint(FLT_MAX, FLT_MAX, FLT_MAX);
	XMFLOAT3 maxPoint(-FLT_MAX, -FLT_MAX, -FLT_MAX);

	for (const auto& vertex : vertices)
	{
		if (vertex.x < minPoint.x) minPoint.x = vertex.x;
		if (vertex.y < minPoint.y) minPoint.y = vertex.y;
		if (vertex.z < minPoint.z) minPoint.z = vertex.z;

		if (vertex.x > maxPoint.x) maxPoint.x = vertex.x;
		if (vertex.y > maxPoint.y) maxPoint.y = vertex.y;
		if (vertex.z > maxPoint.z) maxPoint.z = vertex.z;
	}

	XMFLOAT3 Center = XMFLOAT3(
		(minPoint.x + maxPoint.x) / 2.0f,
		(minPoint.y + maxPoint.y) / 2.0f,
		(minPoint.z + maxPoint.z) / 2.0f
	);

	pivot = XMLoadFloat3(&Center);

	size = XMFLOAT3(
		maxPoint.x - minPoint.x,
		maxPoint.y - minPoint.y,
		maxPoint.z - minPoint.z
	);
}


void PrimitiveComponent::SetBoxCenterSize(XMFLOAT3 center, XMFLOAT3 size)
{
	isFrustumCulling = TRUE;

	pivot = XMLoadFloat3(&center);
	this->size = size;
}

XMVECTOR PrimitiveComponent::GetBoxPivot(void)
{
	return this->pivot;
}

XMFLOAT3 PrimitiveComponent::GetBoxSize(void)
{
	return this->size;
}



BOOL PrimitiveComponent::GetHasShadow(void)
{
	return hasShadow;
}

void PrimitiveComponent::SetHasShadow(BOOL b)
{
	hasShadow = b;
}

BOOL PrimitiveComponent::GetDrawShadow(void)
{
	return drawShadow;
}

void PrimitiveComponent::SetDrawShadow(BOOL b)
{
	drawShadow = b;
}
