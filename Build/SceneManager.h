#pragma once
#include"Coreminimal.h"



class GameEngine;
class Scene;



class SceneManager
{
public:


	enum class SCENE :int
	{
		TITLE,
		TUORIAL,
		STAGE_SELECT,
		STAGE1,
		STAGE2,
		MAX_SCENE,
	};


	SceneManager(GameEngine* pGameEngine);
	~SceneManager();

	void SetScene(SCENE scene);
	void SetDefaultScene(void);

private:
	
	
	GameEngine* pGameEngine;
	vector<Scene*> SceneList;
	SCENE defaultScene;

};

