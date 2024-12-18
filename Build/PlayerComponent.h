#pragma once
#include "component.h"
class PlayerComponent :public Component
{
public:
	PlayerComponent(GameObject* gameObject);
	~PlayerComponent();

	virtual void Init(void) override;
	virtual void Uninit(void) override;
	virtual void Update(void) override;

	void SetContorol(BOOL enable);

	void SetOffSet(float f);

private:
	BOOL control;
	float PlayerOffset;


};

