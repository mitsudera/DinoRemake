#include "SceneManager.h"
#include "Scene.h"
#include "GameEngine.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "TutorialScene.h"
#include "StageSelectScene.h"
#include "SoundEngine.h"
#include "Stage1Scene.h"
#include "Stage2Scene.h"
#include "TestScene.h"
SceneManager::SceneManager(GameEngine* pGameEngine)
{
	this->pGameEngine = pGameEngine;

	this->defaultScene = SCENE::TITLE;

	TestScene* testScene = new TestScene(pGameEngine);
	this->SceneList.push_back(testScene);

	TitleScene* titleScene = new TitleScene(pGameEngine);
	this->SceneList.push_back(titleScene);

	TutorialScene* tutorialScene = new TutorialScene(pGameEngine);
	this->SceneList.push_back(tutorialScene);

	StageSelectScene* stageSelectScene = new StageSelectScene(pGameEngine);
	this->SceneList.push_back(stageSelectScene);

	Stage1Scene* stage1 = new Stage1Scene(pGameEngine);
	this->SceneList.push_back(stage1);

	Stage2Scene* stage2 = new Stage2Scene(pGameEngine);
	this->SceneList.push_back(stage2);


}

SceneManager::~SceneManager()
{
	for (Scene* scene :SceneList)
	{
		delete scene;
	}
}


void SceneManager::SetScene(SCENE scene)
{
	this->pGameEngine->GetSoundEngine()->StopAllSound();

	this->pGameEngine->SetActiveScene(this->SceneList[(int)scene]);

}

void SceneManager::SetDefaultScene(void)
{
	SetScene(defaultScene);
}
