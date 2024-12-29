#pragma once
#include "ShaderSet.h"

class Renderer;
class CBufferManager;
constexpr auto BONE_MAX = (64);

struct SkinMeshVertex
{

	XMFLOAT3	Position;
	XMFLOAT3	Normal;
	XMFLOAT4	Diffuse;
	XMFLOAT2	TexCoord;
	XMFLOAT3	Tangent;
	XMFLOAT3	BiNormal;
	XMFLOAT4	BoneWeight;
	XMUINT4		BoneIndex;

};


class SkinMeshPhongShader : public ShaderSet
{

public:

	SkinMeshPhongShader(Renderer* renderer);
	~SkinMeshPhongShader();

	void SetMaterialCbuffer(MaterialCBuffer data);

	void SetBoneBuffer(XMMATRIX* bone);
private:

	ID3D11Buffer* boneBuffer;
	CBufferManager* pCBufferManager;
};

