#include "DebugUtility.h"
#include "GameEngine.h"
#include "DebugLineShader.h"
#include "renderer.h"
DebugUtility::DebugUtility(GameEngine* gameEngine)
{
    pGameEngine = gameEngine;
    pRenderer = pGameEngine->GetRenderer();

    debugLineShader = new DebugLineShader(pRenderer);

    unsigned int vertexIndex = 0;
    latitudeBands = 20;
    longitudeBands = 20;
    float radius = 1.0f;
    unsigned int vertexCount = (latitudeBands-1) * (longitudeBands)+2;
    unsigned int indexCount = (latitudeBands * longitudeBands) * 2 + ((latitudeBands - 1) * longitudeBands) * 2;
    sphereIndexCnt = indexCount;
    spherevertCnt = vertexCount;
    DebugLineVertex* vertArray = new DebugLineVertex[vertexCount];
    unsigned int* indexArray = new unsigned int[indexCount];



    int vcnt = 0;
    for (unsigned int i = 0; i < latitudeBands+1; i++)
    {
        float y = radius-((radius * 2.0f) / latitudeBands) * (float)i;
        float theta = (float)i * (XM_PI / latitudeBands);
        if (i==0)
        {
            vertArray[vcnt].pos = { 0.0f,y,0.0f };
            vertArray[vcnt].color = { 0.0f,1.0f,0.0f,1.0f };
            vcnt++;
        }
        else if(i==latitudeBands)
        {
            vertArray[vcnt].pos = { 0.0f,y,0.0f };
            vertArray[vcnt].color = { 0.0f,1.0f,0.0f,1.0f };

            vcnt++;


        }
        else
        {
            for (unsigned int j = 0; j < longitudeBands; j++) {
                float phi = (float)j * (2.0f * XM_PI / longitudeBands); // Longitude angle 
                float x = radius * sinf(theta) * cosf(phi);
                float z = radius * sinf(theta) * sinf(phi);
                vertArray[vcnt].pos = { x, y, z }; 
                vertArray[vcnt].color = { 0.0f,1.0f,0.0f,1.0f };
                vcnt++;

            }        
        }
    }


    // 縦の線のインデックス
    int ic = 0;
    //for (int i = 0; i < longitudeBands; i++)
    //{
    //    for (int j = 0; j < latitudeBands; j++)
    //    {
    //        if (j==0)
    //        {
    //            indexArray[ic] = 0;
    //            ic++;
    //            indexArray[ic] = (i * j)+j + 1;
    //            ic++;
    //        }
    //        else if (j == longitudeBands-1)
    //        {
    //            indexArray[ic] = (i * j) + j;
    //            ic++;
    //            indexArray[ic] = vcnt-1;
    //            ic++;
    //        }
    //        else
    //        {
    //            indexArray[ic] = (i * (j)) + j;
    //            ic++;
    //            indexArray[ic] = (i * (j)) + j + 1;
    //            ic++;
    //        }
    //    }
    //}
    //横の線
    for (unsigned int i = 0; i < latitudeBands-1; i++)
    {
        for (unsigned int j = 0; j < longitudeBands; j++)
        {
            if (j == longitudeBands - 1)
            {

                indexArray[ic] = i * j + 1;
                ic++;
                indexArray[ic] = i * j + j + 2;
                ic++;

            }
            else
            {
                indexArray[ic] = i * j + j + 1;
                ic++;
                indexArray[ic] = i * j + j + 2;
                ic++;

            }
        }
    }



    HRESULT hr;

    // 頂点バッファ生成
    D3D11_BUFFER_DESC bd;
    ZeroMemory(&bd, sizeof(bd));
    bd.Usage = D3D11_USAGE_DYNAMIC;
    bd.ByteWidth = sizeof(DebugLineVertex) * vertexCount;
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

    hr = this->pRenderer->GetDevice()->CreateBuffer(&bd, NULL, &this->vertexSphere);

    if (FAILED(hr))
        return;

    // 頂点バッファへのポインタを取得
    D3D11_MAPPED_SUBRESOURCE msr;
    this->pRenderer->GetDeviceContext()->Map(this->vertexSphere, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

    DebugLineVertex* pVtx = (DebugLineVertex*)msr.pData;

    memcpy(pVtx, vertArray, sizeof(DebugLineVertex) * vertexCount);

    this->pRenderer->GetDeviceContext()->Unmap(this->vertexSphere, 0);


    // indexバッファ生成
    ZeroMemory(&bd, sizeof(bd));
    bd.Usage = D3D11_USAGE_DYNAMIC;
    bd.ByteWidth = sizeof(unsigned int) * indexCount;
    bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
    bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

    this->pRenderer->GetDevice()->CreateBuffer(&bd, NULL, &this->indexSphere);



    this->pRenderer->GetDeviceContext()->Map(this->indexSphere, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

    unsigned int* pIdx = (unsigned int*)msr.pData;

    memcpy(pIdx, indexArray, sizeof(unsigned int) * vertexCount);

    this->pRenderer->GetDeviceContext()->Unmap(this->indexSphere, 0);



    if (vertArray) delete[] vertArray;
    if (indexArray) delete[] indexArray;

    vertArray = new DebugLineVertex[8];
    indexArray = new unsigned int[24];
    vertArray[0].pos = { -0.5f,0.5f,0.5f };
    vertArray[0].color = { 0.0f,1.0f,0.0f,1.0f };
    vertArray[1].pos = { 0.5f,0.5f,0.5f };
    vertArray[1].color = { 0.0f,1.0f,0.0f,1.0f };
    vertArray[2].pos = { 0.5f,0.5f,-0.5f };
    vertArray[2].color = { 0.0f,1.0f,0.0f,1.0f };
    vertArray[3].pos = { -0.5f,0.5f,-0.5f };
    vertArray[3].color = { 0.0f,1.0f,0.0f,1.0f };
    vertArray[4].pos = { -0.5f,-0.5f,0.5f };
    vertArray[4].color = { 0.0f,1.0f,0.0f,1.0f };
    vertArray[5].pos = { 0.5f,-0.5f,0.5f };
    vertArray[5].color = { 0.0f,1.0f,0.0f,1.0f };
    vertArray[6].pos = { 0.5f,-0.5f,-0.5f };
    vertArray[6].color = { 0.0f,1.0f,0.0f,1.0f };
    vertArray[7].pos = { -0.5f,-0.5f,-0.5f };
    vertArray[7].color = { 0.0f,1.0f,0.0f,1.0f };
    ic = 0;
    indexArray[0] = 0;
    indexArray[1] = 1;
    indexArray[2] = 1;
    indexArray[3] = 2;
    indexArray[4] = 2;
    indexArray[5] = 3;
    indexArray[6] = 3;
    indexArray[7] = 0;
    indexArray[8] = 4;
    indexArray[9] = 5;
    indexArray[10] = 5;
    indexArray[11] = 6;
    indexArray[12] = 6;
    indexArray[13] = 7;
    indexArray[14] = 7;
    indexArray[15] = 4;
    indexArray[16] = 0;
    indexArray[17] = 4;
    indexArray[18] = 1;
    indexArray[19] = 5;
    indexArray[20] = 2;
    indexArray[21] = 6;
    indexArray[22] = 3;
    indexArray[23] = 7;

    ZeroMemory(&bd, sizeof(bd));
    bd.Usage = D3D11_USAGE_DYNAMIC;
    bd.ByteWidth = sizeof(DebugLineVertex) * 8;
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

    hr = this->pRenderer->GetDevice()->CreateBuffer(&bd, NULL, &this->vertexBox);

    if (FAILED(hr))
        return;

    // 頂点バッファへのポインタを取得
    this->pRenderer->GetDeviceContext()->Map(this->vertexBox, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

    pVtx = (DebugLineVertex*)msr.pData;

    memcpy(pVtx, vertArray, sizeof(DebugLineVertex) * 8);

    this->pRenderer->GetDeviceContext()->Unmap(this->vertexBox, 0);


    // indexバッファ生成
    ZeroMemory(&bd, sizeof(bd));
    bd.Usage = D3D11_USAGE_DYNAMIC;
    bd.ByteWidth = sizeof(unsigned int) * 24;
    bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
    bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

    this->pRenderer->GetDevice()->CreateBuffer(&bd, NULL, &this->indexBox);



    this->pRenderer->GetDeviceContext()->Map(this->indexBox, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

    pIdx = (unsigned int*)msr.pData;

    memcpy(pIdx, indexArray, sizeof(unsigned int) * 24);

    this->pRenderer->GetDeviceContext()->Unmap(this->indexBox, 0);



}

DebugUtility::~DebugUtility()
{
	debugLineShader->Uninit();
	delete debugLineShader;

    if (vertexSphere) vertexSphere->Release();
    if (indexSphere)indexSphere->Release();
    if (vertexBox) vertexBox->Release();
    if (indexBox)indexBox->Release();

}

void DebugUtility::DrawDebugSphere(void)
{
	// 頂点バッファ設定
	UINT stride = sizeof(DebugLineVertex);
	UINT worldOffset = 0;

	this->pRenderer->GetDeviceContext()->IASetVertexBuffers(0, 1, &this->vertexSphere, &stride, &worldOffset);
	this->pRenderer->GetDeviceContext()->IASetIndexBuffer(this->indexSphere, DXGI_FORMAT_R32_UINT, 0);

	this->pRenderer->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D_PRIMITIVE_TOPOLOGY_LINESTRIP);

    this->pRenderer->GetDeviceContext()->Draw(spherevertCnt, 0);
}

void DebugUtility::DrawDebugBox(void)
{
    // 頂点バッファ設定
    UINT stride = sizeof(DebugLineVertex);
    UINT worldOffset = 0;

    this->pRenderer->GetDeviceContext()->IASetVertexBuffers(0, 1, &this->vertexBox, &stride, &worldOffset);
    this->pRenderer->GetDeviceContext()->IASetIndexBuffer(this->indexBox, DXGI_FORMAT_R32_UINT, 0);

    this->pRenderer->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D_PRIMITIVE_TOPOLOGY_LINELIST);

    this->pRenderer->GetDeviceContext()->DrawIndexed(24, 0, 0);

}

void DebugUtility::SetDebugLineShader(void)
{
    debugLineShader->SetShaderRenderer();
}
