#include "TerrainColliderComponent.h"
#include "TerrainComponent.h"
TerrainColliderComponent::TerrainColliderComponent(GameObject* gameObject)
{
	this->pGameObject = gameObject;
}

TerrainColliderComponent::~TerrainColliderComponent()
{
}

void TerrainColliderComponent::Awake(void)
{
	ColliderComponent::Awake();
	this->shape = Shape::Terrain;
	this->pHeightMap = nullptr;

}

void TerrainColliderComponent::Uninit(void)
{
	ColliderComponent::Uninit();

}

void TerrainColliderComponent::Update(void)
{
	ColliderComponent::Update();
}

ID3D11Texture2D* TerrainColliderComponent::GetHeightMap(void)
{
	return this->pHeightMap;
}

void TerrainColliderComponent::SetHeightMap(ID3D11Texture2D* map)
{
	this->pHeightMap = map;
}
