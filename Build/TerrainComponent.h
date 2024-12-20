#pragma once
#include "primitivecomponent.h"
#include "ShaderSet.h"
class TerrainComponent :public PrimitiveComponent
{
public:
	TerrainComponent(GameObject* gameObject);
	~TerrainComponent();
	virtual void Awake(void) override;
	virtual void Update(void) override;
	virtual void Uninit(void) override;

	virtual void Draw(void) override;

	void CreateVetexBuffer(XMFLOAT2 uvScale, XMFLOAT2 scale, XMFLOAT4 color);

	ID3D11Texture2D* GetHeightMap(void);

	float GetHeight(XMFLOAT3 pos);

private:

	VERTEX_3D vertexArray[6];
	ID3D11Buffer* vertexBuffer;
	ID3D11Texture2D* heightMap;


};

