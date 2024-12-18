#include "Stage1Manager.h"
#include "Stage1ManagerComponent.h"

Stage1Manager::Stage1Manager(Scene* scene)
{
	this->pScene = scene;
}

Stage1Manager::~Stage1Manager()
{
}

void Stage1Manager::Init(void)
{
	GameObject::Init();
	this->name = "Stage1Manager";
	AddComponent<Stage1ManagerComponent>();

}
