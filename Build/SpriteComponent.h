#pragma once
#include "primitivecomponent.h"
#include "ShaderSet.h"
class SpriteComponent : public PrimitiveComponent
{
public:
	SpriteComponent(GameObject* gameObject);
	~SpriteComponent();

	virtual void Init(void) override;
	virtual void Update(void) override;
	virtual void Uninit(void) override;
	virtual void Draw(void) override;

	void CreateVertexBuffer(void);

	void SetSpriteCenter(string texPath, XMFLOAT3 pos, float width, float height);
	void SetSpriteLeftDown(string texPath, XMFLOAT3 pos, float width, float height);

	void SetFullScreen(string texPath);

	void SetTexSlice(XMINT2 slice);

	void SetSliceTexIndex(int index);

	void SetColor(XMFLOAT4 diffuse);

	void SetTexture(string path);

	void SetLRRev(BOOL enable);

private:
	VERTEX_3D vertexArray[4];

	int texIndex;
	ID3D11Buffer* vertexBuffer;
	XMINT2 texSlice;//テクスチャスライス数
	int sliceIndex;
	int sliceMax;

	BOOL texLRrev;

};

