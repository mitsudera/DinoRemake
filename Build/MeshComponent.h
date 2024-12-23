#pragma once
#include "PrimitiveComponent.h"



class GameEngine;

class DX11Texture;

class MeshData;

class Mesh
{

};

class MeshComponent :public PrimitiveComponent
{



public:

	MeshComponent();
	MeshComponent(GameObject* gameObject);
	~MeshComponent();

	virtual void Awake(void) override;
	virtual void Update(void) override;
	virtual void Uninit(void) override;

	virtual void Draw(void) override;

	virtual void ShadowMapping(void) override;


	void SetCullingMode(int cullMode);
	int GetCullingMode(void);

	void SetAlphaTest(BOOL enable);
	BOOL GetAlphaTest(void);
	void SetMeshData(MeshData* data);



protected:

	string meshFilePath;
	
	MeshData* meshData;




	
	int cullMode;


	BOOL isRoot;

};

