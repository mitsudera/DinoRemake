#include "TitleCursor.h"
#include "Scene.h"
#include "SpriteComponent.h"
TitleCursor::TitleCursor(Scene* scene)
{
	pScene = scene;
}

TitleCursor::~TitleCursor()
{
}

void TitleCursor::Init(void)
{

	GameObject::Init();
	this->layer = Layer::UI;

	this->name = "cursor";
	SpriteComponent* sprite = AddComponent<SpriteComponent>();

	sprite->SetTexSlice(XMINT2(7, 1));
	sprite->SetSliceTexIndex(0);
	sprite->SetAlphaTest(TRUE);
}
