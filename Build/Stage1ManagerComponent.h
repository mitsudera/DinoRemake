#pragma once
#include "component.h"
class Stage1ManagerComponent :public Component
{

public:
	Stage1ManagerComponent(GameObject* gameObject);
	~Stage1ManagerComponent();
	// Component ����Čp������܂���
	virtual void Awake(void) override;
	virtual void Init(void)override;
	virtual void Uninit(void) override;
	virtual void Update(void) override;
private:



};

