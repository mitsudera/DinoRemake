#pragma once
#include "ShaderSet.h"

class Renderer;

struct TessCBuffer
{
	float cbEdgeFactor; //4�p�`�̕ӂ̕����ʂ̎w��
	float cbInsideFactor; //4�p�`�̓����̕����ʂ̎w��
	float dummy[10];

};
class TerrainShader : public ShaderSet
{
public:

	TerrainShader(Renderer* renderer);
	~TerrainShader();

	void SetMaterialCbuffer(MaterialCBuffer data);

	void SetTessBuffer(TessCBuffer data);

	virtual void Uninit(void)override;



private:

	ID3D11Buffer* tessBuffer;


};

