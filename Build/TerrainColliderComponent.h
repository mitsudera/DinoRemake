#pragma once
#include "ColliderComponent.h"
class TerrainColliderComponent : public ColliderComponent
{
public:
	TerrainColliderComponent(GameObject* gameObject);
	~TerrainColliderComponent();

	virtual void Init(void) override;
	virtual void Uninit(void) override;
	virtual void Update(void) override;

	ID3D11Texture2D* GetHeightMap(void);
	void SetHeightMap(ID3D11Texture2D* map);

protected:

	ID3D11Texture2D* pHeightMap;

};

