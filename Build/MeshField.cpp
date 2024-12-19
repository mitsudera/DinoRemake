#include "MeshField.h"
#include "TerrainComponent.h"
#include "Material.h"
#include "LambartMaterial.h"
#include "PhongMaterial.h"
#include "GameEngine.h"
#include "AssetsManager.h"
#include "Scene.h"
#include "TerrainColliderComponent.h"
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

	TerrainColliderComponent* collider = AddComponent<TerrainColliderComponent>();


	meshField->CreateVetexBuffer(XMFLOAT2(1000.0f, 1000.0f), XMFLOAT2(10.0f, 10.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
	PhongMaterial* pho = new PhongMaterial(pScene->GetGameEngine()->GetAssetsManager());
	pho->LoadDiffuseTex("data/texture/gravel_diff.png");
	pho->LoadNormalTex("data/texture/gravel_nor.png");
	pho->diffuse = { 1.0f, 1.0f, 1.0f, 1.0f };
	pho->ambient = { 0.2f,0.2f,0.2f,1.0f };
	pho->shininess = 20.0f;
	pho->specular= { 0.2f,0.2f,0.2f,1.0f };
	meshField->LoadMaterial(pho);
	meshField->SetHasShadow(FALSE);

}
