#include "Text.h"
#include "TextWriteComponent.h"

Text::Text(Scene* scene)
{
	pScene = scene;
}

Text::~Text()
{
}

void Text::Awake(void)
{
	GameObject::Awake();
	this->layer = Layer::Text;

	this->name = "Text";
	TextWriteComponent* text = AddComponent<TextWriteComponent>();

}