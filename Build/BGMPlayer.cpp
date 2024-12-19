#include "BGMPlayer.h"
#include "SoundSpeakerComponent.h"

BGMPlayer::BGMPlayer(Scene* scene)
{
	pScene = scene;
}

BGMPlayer::~BGMPlayer()
{
}

void BGMPlayer::Awake(void)
{
	GameObject::Awake();
	this->name = "BGMPlayer";
	SoundSpeakerComponent* speaker = AddComponent<SoundSpeakerComponent>();


}
