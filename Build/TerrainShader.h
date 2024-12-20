#pragma once
#include "ShaderSet.h"

class Renderer;

struct TessCBuffer
{
	float cbEdgeFactor; //4角形の辺の分割量の指定
	float cbInsideFactor; //4角形の内部の分割量の指定
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

