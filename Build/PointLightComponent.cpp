#include "PointLightComponent.h"
#include "gameobject.h"
#include "LightManager.h"
#include "GameEngine.h"
PointLightComponent::PointLightComponent(GameObject* gameObject)
{
	this->pGameObject = gameObject;
	
}

PointLightComponent::~PointLightComponent()
{
}

void PointLightComponent::Awake(void)
{
	Component::Awake();
	index= pGameEngine->GetLightmanager()->AddLight(this);

}

void PointLightComponent::Uninit(void)
{
	Component::Uninit();
}

void PointLightComponent::Update(void)
{
	Component::Update();
}


POINT_LIGHT_PARAM& PointLightComponent::GetLightParam(void)
{
	return this->param;
}


