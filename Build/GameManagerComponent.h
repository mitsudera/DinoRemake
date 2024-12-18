#pragma once
#include "component.h"

class Scene;


class GameObject;

class CameraComponent;


class GameManagerComponent :public Component
{
public:
	GameManagerComponent(GameObject* gameObject);
	~GameManagerComponent();
	// Component ÇâÓÇµÇƒåpè≥Ç≥ÇÍÇ‹ÇµÇΩ
	virtual void Init(void) override;
	virtual void Uninit(void) override;
	virtual void Update(void) override;
private:
	Scene* gameScene;

	CameraComponent* gameCamera;
	CameraComponent* debugCamera;
	GameObject* player;

	void SetCameraModeGame(void);
	void SetCameraModeDebug(void);
	

};

