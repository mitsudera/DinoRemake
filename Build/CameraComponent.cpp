//=============================================================================
//
// カメラ処理 [camera.cpp]
// Author : 
//
//=============================================================================
#pragma once
#include "CameraComponent.h"
#include "Renderer.h"
#include "gameobject.h"
#include "GameEngine.h"
#include "Scene.h"
#include "CBufferManager.h"
#include "ShaderSet.h"
#include "primitivecomponent.h"
#include "Material.h"
#include "AssetsManager.h"
#include "component.h"
#include "transformcomponent.h"
#include "RenderTexture.h"
#include "PostEffectShader.h"
#include "DebugUtility.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	VIEW_ANGLE		(XMConvertToRadians(45.0f))						// ビュー平面の視野角
#define	VIEW_ASPECT		(16.0f/ 9.0f)	// ビュー平面のアスペクト比	
#define	VIEW_NEAR_Z		(10.0f)											// ビュー平面のNearZ値
#define	VIEW_FAR_Z		(100000.0f)										// ビュー平面のFarZ値

#define	VALUE_MOVE_CAMERA	(2.0f)										// カメラの移動量
#define	VALUE_ROTATE_CAMERA	(XM_PI * 0.01f)								// カメラの回転量

//*****************************************************************************
// グローバル変数
//*****************************************************************************
static int				ViewPortType = TYPE_FULL_SCREEN;


CameraComponent::CameraComponent()
{
	for (int i = 0; i < (int)GameObject::Layer::LayerMax; i++)
	{
		layerCulling[i] = FALSE;
	}

}

CameraComponent::CameraComponent(GameObject* gameObject)
{

	pRenderer = gameObject->GetScene()->GetGameEngine()->GetRenderer();

	gameObject->GetScene()->AddCamera(this);
	for (int i = 0; i < (int)GameObject::Layer::LayerMax; i++)
	{
		layerCulling[i] = FALSE;
	}

	// カメラバッファ生成
	D3D11_BUFFER_DESC hBufferDesc;
	hBufferDesc.ByteWidth = sizeof(CameraCBuffer);
	hBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	hBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	hBufferDesc.CPUAccessFlags = 0;
	hBufferDesc.MiscFlags = 0;
	hBufferDesc.StructureByteStride = sizeof(float);

	pRenderer->GetDevice()->CreateBuffer(&hBufferDesc, nullptr, &this->cameraBuffer);

	this->pGameObject = gameObject;
	this->pRenderer = gameObject->GetScene()->GetGameEngine()->GetRenderer();
}

CameraComponent::~CameraComponent()
{
	Uninit();
}

void CameraComponent::Awake(void)
{
	Component::Awake();

	this->attribute = Attribute::Camera;

	this->mode = TrackingMode::NONE;


	this->at = { 0.0f, 0.0f, -1.0f };
	this->up = { 0.0f, 1.0f, 0.0f };


	clearMode = ClearMode::Color;

	// 仮
	this->aspect = 16.0f / 9.0f;	// アスペクト比 
	this->angle = XMConvertToRadians(90.0f);	// 視野角
	this->nearZ = 10.0f;
	this->farZ = 1000.0f;

	this->len = 50.0f;

	this->mode = TrackingMode::NONE;
	for (int i = 0; i < (int)GameObject::Layer::LayerMax; i++)
	{
		layerCulling[i] = FALSE;
	}

	this->clearColor = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);

	// ビューポートタイプの初期化
	SetViewPort(VIEWPORT_TYPE::TYPE_FULL_SCREEN);
	this->mtxProj = XMMatrixPerspectiveFovLH(this->angle, this->aspect, this->nearZ, this->farZ);

	renderTextureIndex= pGameEngine->GetAssetsManager()->CreateRenderTexture(1920.0f, 1080.0f, "cameraRT");
	renderTexture = pGameEngine->GetAssetsManager()->GetRenderTexture(renderTextureIndex);
	postEffectIndex = 0;

}

void CameraComponent::Init(void)
{
	Component::Init();
}

void CameraComponent::Update(void)
{
	Component::Update();


}


void CameraComponent::Uninit(void)
{
	Component::Uninit();

	pGameEngine->GetAssetsManager()->DeleteRenderTexture(renderTextureIndex);
	this->cameraBuffer->Release();
}

void CameraComponent::Render(void)
{

	switch (this->mode)
	{
	case TrackingMode::PARENT:


		this->at = this->pGameObject->GetParent()->GetTransFormComponent()->GetWorldPos();
		this->mtxView = XMMatrixLookAtLH(XMLoadFloat3(&this->GetWorldPos()), XMLoadFloat3(&this->at), XMLoadFloat3(&this->up));

		break;
	case TrackingMode::SKY:


		this->mtxView = XMMatrixLookAtLH(XMLoadFloat3(&this->GetWorldPos()), XMLoadFloat3(&this->at), XMLoadFloat3(&this->up));

		break;
	case TrackingMode::NONE:

		this->mtxView = XMMatrixLookToLH(XMLoadFloat3(&this->GetWorldPos()), GetTransFormComponent()->GetAxisZ(), this->GetTransFormComponent()->GetAxisY());
		break;

	default:
		break;
	}

	pGameEngine->GetCBufferManager()->SetCameraBuffer(&GetWorldPos());

	pGameEngine->GetCBufferManager()->SetViewMtx(&this->mtxView);


	pGameEngine->GetCBufferManager()->SetProjectionMtx(&this->mtxProj);


	//ビューポートセット
	pRenderer->GetDeviceContext()->RSSetViewports(1, &vp);


	if (!postEffectEnable)
	{
		//描画ターゲットのセット
		pRenderer->GetDeviceContext()->OMSetRenderTargets(1, &this->renderTarget, this->depthTarget);
		const float cc[4] = { clearColor.x,clearColor.y,clearColor.z,clearColor.w };

		//描画ターゲットのクリア
		switch (clearMode)
		{

		case ClearMode::None:


			break;
		case ClearMode::Color:



			pRenderer->GetDeviceContext()->ClearRenderTargetView(this->renderTarget, cc);
			pRenderer->GetDeviceContext()->ClearDepthStencilView(this->depthTarget, D3D11_CLEAR_DEPTH, 1.0f, 0);

			break;

		case ClearMode::SkySphere:


			//スカイスフィアで背景クリアをする場合

			layerCulling[(int)GameObject::Layer::Sky] = TRUE;
			pRenderer->SetDepthEnable(FALSE);
			this->sky->GetTransFormComponent()->SetPosition(this->GetWorldPos());


			for (PrimitiveComponent* com : skyComArray)
			{
				com->GetTransFormComponent()->UpdateMatrix();
				com->GetMaterial()->GetShaderSet()->SetShaderRenderer();
				com->Draw();
			}




			pRenderer->SetDepthEnable(TRUE);


		}


	}
	else
	{
		this->renderTexture->SetRTV(RenderTexture::BindMode::BOTH,0);
		const float cc[4] = { clearColor.x,clearColor.y,clearColor.z,clearColor.w };

		//描画ターゲットのクリア
		switch (clearMode)
		{

		case ClearMode::None:


			break;
		case ClearMode::Color:



			pRenderer->GetDeviceContext()->ClearRenderTargetView(this->renderTexture->GetRenderTargetView(), cc);
			pRenderer->GetDeviceContext()->ClearDepthStencilView(this->renderTexture->GetDepthStencilView(), D3D11_CLEAR_DEPTH, 1.0f, 0);
			break;

		case ClearMode::SkySphere:


			//スカイスフィアで背景クリアをする場合

			layerCulling[(int)GameObject::Layer::Sky] = TRUE;
			pRenderer->SetDepthEnable(FALSE);
			this->sky->GetTransFormComponent()->SetPosition(this->GetWorldPos());


			for (PrimitiveComponent* com:skyComArray)
			{
				com->GetTransFormComponent()->UpdateMatrix();
				com->GetMaterial()->GetShaderSet()->SetShaderRenderer();
				com->Draw();
			}


			pRenderer->SetDepthEnable(TRUE);


		}


	}


	//シェーダー毎に描画
	for (int i = 0; i < ShaderSet::ShaderIndex::MAXShader; i++)
	{
			pGameObject->GetScene()->GetGameEngine()->GetAssetsManager()->SetShader((ShaderSet::ShaderIndex)i);

		for (PrimitiveComponent* com : pGameObject->GetScene()->GetAllPrimitiveComponent())
		{
			if (!com->GetActive())
				continue;

			//レイヤーのカリングチェック
			if (layerCulling[(int)com->GetGameObject()->GetLayer()] || com->GetGameObject()->GetLayer() == GameObject::Layer::Text)
				continue;

			if (com->GetMaterial() == nullptr)
			{
				com->Draw();
				continue;

			}

			//現在セットしてるシェーダーを使っている場合描画
			if (com->GetMaterial()->GetShaderSet()->GetShaderIndex() != i)
				continue;


			com->Draw();


		}
	}

	pGameEngine->GetDebugUtility()->SetDebugLineShader();
	

#ifdef DEBUG
	for (Component* com : pGameObject->GetScene()->GetAllComponent())
	{
		if (!com->GetActive())
			continue;
		com->DebugDraw();
	}

#endif




	pRenderer->GetDeviceContext()->OMSetRenderTargets(0, nullptr, nullptr);

	if (postEffectEnable)
	{
		this->shaderArray[postEffectIndex]->PostEffectDraw(this->renderTexture->GetSRV(), this->renderTarget);

	}
	for (PrimitiveComponent* com : pGameObject->GetScene()->GetAllPrimitiveComponent())
	{
		if (!com->GetActive())
			continue;

		//レイヤーのカリングチェック
		if (com->GetGameObject()->GetLayer() != GameObject::Layer::Text)
			continue;



		com->Draw();


	}

}



void CameraComponent::SetMode(TrackingMode mode)
{
	this->mode = mode;

}

XMMATRIX CameraComponent::GetView(void)
{
	return this->mtxView;
}

ID3D11RenderTargetView* CameraComponent::GetRenderTarget(void)
{
	return this->renderTarget;
}

void CameraComponent::SetRenderTarget(ID3D11RenderTargetView* rtv)
{
	this->renderTarget = rtv;
}

ID3D11DepthStencilView* CameraComponent::GetDepthStencilView(void)
{
	return this->depthTarget;
}

void CameraComponent::SetDepthStencilView(ID3D11DepthStencilView* dsv)
{
	this->depthTarget = dsv;
}

void CameraComponent::SetClearMode(ClearMode mode)
{
	this->clearMode = mode;
}

void CameraComponent::SetClearColor(XMFLOAT4 color)
{
	this->clearColor = color;
}

void CameraComponent::SetSkyCom(GameObject* sky)
{
	PrimitiveComponent* com = sky->GetComponent<PrimitiveComponent>();
	if (com != nullptr)
		skyComArray.push_back(com);

	for (GameObject* obj : sky->GetChild())
	{
		SetSkyCom(obj);
	}
	clearMode = ClearMode::SkySphere;
}

void CameraComponent::SetSky(GameObject* sky)
{
	this->sky = sky;
	SetSkyCom(sky);
}

void CameraComponent::SetMainCamera(void)
{
	this->pGameEngine->SetMainCamera(this);
}

void CameraComponent::SetPostEffect(PostEffectShader* shader)
{
	this->shaderArray.push_back(shader);
}

void CameraComponent::SetPostEffectEnable(BOOL enable)
{
	this->postEffectEnable = enable;
}

void CameraComponent::SetTrackingMode(TrackingMode mode)
{
	this->mode = mode;
}

CameraComponent::TrackingMode CameraComponent::GetTrackingMode(void)
{
	return this->mode;
}

XMFLOAT3 CameraComponent::GetAtPos(void)
{
	return this->at;
}

void CameraComponent::SetNear(float f)
{
	this->nearZ = f;
	SetProjectionMtx();
}

void CameraComponent::SetFar(float f)
{
	this->farZ = f;
	SetProjectionMtx();

}

void CameraComponent::SetProjectionMtx(void)
{
	this->mtxProj = XMMatrixPerspectiveFovLH(this->angle, this->aspect, this->nearZ, this->farZ);

}

void CameraComponent::SetViewPort(int m_type)
{

	ViewPortType = m_type;

	XMFLOAT2 screenSize = GetGameObject()->GetScene()->GetGameEngine()->GetWindowSize();


	// ビューポート設定
	switch (ViewPortType)
	{
	case TYPE_FULL_SCREEN:
		vp.Width = (FLOAT)screenSize.x;
		vp.Height = (FLOAT)screenSize.y;
		vp.MinDepth = 0.0f;
		vp.MaxDepth = 1.0f;
		vp.TopLeftX = 0;
		vp.TopLeftY = 0;
		break;

	case TYPE_LEFT_HALF_SCREEN:
		vp.Width = (FLOAT)screenSize.x / 2;
		vp.Height = (FLOAT)screenSize.y;
		vp.MinDepth = 0.0f;
		vp.MaxDepth = 1.0f;
		vp.TopLeftX = 0;
		vp.TopLeftY = 0;
		break;

	case TYPE_RIGHT_HALF_SCREEN:
		vp.Width = (FLOAT)screenSize.x / 2;
		vp.Height = (FLOAT)screenSize.y;
		vp.MinDepth = 0.0f;
		vp.MaxDepth = 1.0f;
		vp.TopLeftX = (FLOAT)screenSize.x / 2;
		vp.TopLeftY = 0;
		break;

	case TYPE_UP_HALF_SCREEN:
		vp.Width = (FLOAT)screenSize.x;
		vp.Height = (FLOAT)screenSize.y / 2;
		vp.MinDepth = 0.0f;
		vp.MaxDepth = 1.0f;
		vp.TopLeftX = 0;
		vp.TopLeftY = 0;
		break;

	case TYPE_DOWN_HALF_SCREEN:
		vp.Width = (FLOAT)screenSize.x;
		vp.Height = (FLOAT)screenSize.y / 2;
		vp.MinDepth = 0.0f;
		vp.MaxDepth = 1.0f;
		vp.TopLeftX = 0;
		vp.TopLeftY = (FLOAT)screenSize.x / 2;
		break;
	case TYPE_VIEWPORT:
		vp.Width = (FLOAT)screenSize.x * 0.6f;
		vp.Height = (FLOAT)screenSize.y * 0.6f + GetSystemMetrics(SM_CYCAPTION);
		vp.MinDepth = 0.0f;
		vp.MaxDepth = 1.0f;
		vp.TopLeftX = (FLOAT)screenSize.x * 0.2f;
		vp.TopLeftY = (FLOAT)screenSize.y * 0.1f;
		break;
	}
}




int CameraComponent::GetViewPortType(void)
{
	return ViewPortType;
}


void CameraComponent::SetLookObject(GameObject* gameObject)
{
	this->lookObject = gameObject;
}

