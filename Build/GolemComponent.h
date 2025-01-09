#pragma once
#include "EnemyComponent.h"
class GolemComponent : public EnemyComponent
{
public:
	GolemComponent(GameObject* gameObject);
	~GolemComponent();

	virtual void Init(void)override;


private:


};
