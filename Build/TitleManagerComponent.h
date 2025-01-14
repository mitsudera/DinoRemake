#pragma once
#include "component.h"

class FadeShader;

class TitleManagerComponent :public Component
{
public:
	TitleManagerComponent(GameObject* gameObject);
	~TitleManagerComponent();

	// Component ‚ğ‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½
	virtual void Init(void) override;
	virtual void Uninit(void) override;
	virtual void Update(void) override;

private:
	GameObject* logo;
	GameObject* loading;

};

