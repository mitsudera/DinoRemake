#include "BGMPlayer.h"
#include "SoundSpeakerComponent.h"

BGMPlayer::BGMPlayer(Scene* scene)
{
	pScene = scene;
}

BGMPlayer::~BGMPlayer()
{
}

void BGMPlayer::Init(void)
{
	GameObject::Init();
	this->name = "BGMPlayer";
	SoundSpeakerComponent* speaker = AddComponent<SoundSpeakerComponent>();


}
