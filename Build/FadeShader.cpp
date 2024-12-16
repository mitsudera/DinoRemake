#include "FadeShader.h"
#include "renderer.h"
#include "CBufferManager.h"

FadeShader::FadeShader(Renderer* renderer)
{
	pRenderer = renderer;


}

FadeShader::~FadeShader()
{
}

void FadeShader::Init(void)
{

	PostEffectShader::Init();
	AddShader("shaders/Fade.hlsl", "PS_Main");

	// 定数バッファ生成
	D3D11_BUFFER_DESC hBufferDesc;
	hBufferDesc.ByteWidth = sizeof(FadeCbuffer);
	hBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	hBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	hBufferDesc.CPUAccessFlags = 0;
	hBufferDesc.MiscFlags = 0;
	hBufferDesc.StructureByteStride = sizeof(float);



	FadeCbuffer initData;

	initData.fade.x = 1.0f;
	pRenderer->GetDevice()->CreateBuffer(&hBufferDesc, nullptr, &this->fadeBuffer);

	pRenderer->GetDeviceContext()->UpdateSubresource(fadeBuffer, 0, NULL, &initData, 0, 0);


}

void FadeShader::PostEffectDraw(ID3D11ShaderResourceView* srv, ID3D11RenderTargetView* rtv)
{
	pCBufferManager->SetCBufferVSPS(fadeBuffer, CBufferManager::BufferSlot::Free1);

	PostEffectShader::PostEffectDraw(srv, rtv);
}
