#pragma once
#include "component.h"
class TutorialManagerComponent :public Component
{
public:
	TutorialManagerComponent(GameObject* gameObject);
	~TutorialManagerComponent();

	// Component ����Čp������܂���
	virtual void Init(void) override;
	virtual void Uninit(void) override;
	virtual void Update(void) override;


private:
	GameObject* bgmPlayer;

};

