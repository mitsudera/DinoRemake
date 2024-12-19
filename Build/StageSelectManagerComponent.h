#pragma once
#include "component.h"
class StageSelectManagerComponent :public Component
{
public:

	enum class Select: int
	{
		Stage1,
		Stage2,
		Back,
		Max,
	};

	StageSelectManagerComponent(GameObject* gameObject);
	~StageSelectManagerComponent();

	// Component ÇâÓÇµÇƒåpè≥Ç≥ÇÍÇ‹ÇµÇΩ
	virtual void Awake(void) override;
	virtual void Init(void)override;
	virtual void Uninit(void) override;
	virtual void Update(void) override;

private:

	GameObject* cursor;
	GameObject* soundPlayer;

	float animCnt;
	Select select;
	int cursorIndex;
	float animWait;

};

