#pragma once
#include "primitivecomponent.h"
#include "ShaderSet.h"

class RenderTexture;

class TextMeshComponent :public PrimitiveComponent
{
public:
	TextMeshComponent(GameObject* gameObject);
	~TextMeshComponent();

	virtual void Awake(void) override;
	virtual void Update(void) override;
	virtual void Uninit(void) override;
	virtual void Draw(void) override;

	void CreateVertexBuffer(void);

	void CreateTextMeshCenter(string text, XMFLOAT3 pos, float width, float height, XMFLOAT4 color);

private:

	int texIndex;

	



	VERTEX_3D vertexArray[4];
	ID3D11Buffer* vertexBuffer;
	string outputText;


};

