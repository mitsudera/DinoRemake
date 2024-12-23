#pragma once
#include "component.h"
class UIManagerComponent :public Component
{
public:
	UIManagerComponent(GameObject* gameObject);
	~UIManagerComponent();

	// Component を介して継承されました
	virtual void Init(void) override;
	virtual void Uninit(void) override;
	virtual void Update(void) override;

};

