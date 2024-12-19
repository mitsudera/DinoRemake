#include "TextMesh.h"
#include "TextMeshComponent.h"
TextMesh::TextMesh(Scene* scene)
{
	pScene = scene;
}

TextMesh::~TextMesh()
{
}

void TextMesh::Awake(void)
{
	GameObject::Awake();
	this->layer = Layer::UI;

	this->name = "TextMesh";
	TextMeshComponent* text = AddComponent<TextMeshComponent>();

}
