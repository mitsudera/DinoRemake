#pragma once
#include "ShaderSet.h"

class Renderer;


class TerrainShader : public ShaderSet
{
public:

	TerrainShader(Renderer* renderer);
	~TerrainShader();

	void SetMaterialCbuffer(MaterialCBuffer data);


private:



};

