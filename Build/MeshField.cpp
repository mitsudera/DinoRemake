#include "MeshField.h"
#include "TerrainComponent.h"
#include "Material.h"
#include "LambartMaterial.h"
#include "PhongMaterial.h"
#include "GameEngine.h"
#include "AssetsManager.h"
#include "Scene.h"
#include "TerrainColliderComponent.h"
#include "TerrainMaterial.h"
MeshField::MeshField(Scene* scene)
{
	pScene = scene;
}

MeshField::~MeshField()
{
}

void MeshField::Awake(void)
{
	GameObject::Awake();
	this->name = "Field";

	this->layer = Layer::Field;
	TerrainComponent* meshField = AddComponent<TerrainComponent>();
	meshField->LoadHeightMap("data/texture/heightMap.png");


	TerrainColliderComponent* collider = AddComponent<TerrainColliderComponent>();


	meshField->CreateVetexBuffer(XMINT2(65, 65), XMFLOAT2(1024.0f, 1024.0f));
	TerrainMaterial* mat = new TerrainMaterial(pScene->GetGameEngine()->GetAssetsManager());
	//PhongMaterial* mat = new PhongMaterial(pScene->GetGameEngine()->GetAssetsManager());
	mat->LoadDiffuseTex("data/texture/gravel_diff.png");
	mat->LoadNormalTex("data/texture/gravel_nor.png");
	//mat->LoadHeghtMap("data/texture/heightmap_1.png");
	mat->diffuse = { 1.0f, 1.0f, 1.0f, 1.0f };
	mat->ambient = { 0.2f,0.2f,0.2f,1.0f };
	mat->shininess = 20.0f;
	mat->specular= { 0.1f,0.1f,0.1f,1.0f };
	mat->SetTessEdgeFacter(16.0f);
	mat->SetTessInsideFacter(16.0f);
	mat->SetHeightFacter(10.0f);
	mat->SetUVScale(XMFLOAT2(10.0f, 10.0f));
	mat->SetHeghtMapUVScale(XMFLOAT2(1.0f, 1.0f));
	meshField->LoadMaterial(mat);
	meshField->SetHasShadow(FALSE);


}
