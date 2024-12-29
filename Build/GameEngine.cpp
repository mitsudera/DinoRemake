#include "GameEngine.h"
#include "Main.h"
#include "renderer.h"
#include "AssetsManager.h"
#include "input.h"
#include "SceneManager.h"
#include "Scene.h"
#include "CBufferManager.h"
#include "LightManager.h"
#include "CollisionManager.h"
#include "CameraComponent.h"
#include "ShadowMap.h"
#include "SoundEngine.h"
#include "WicFactory.h"
#include "DebugUtility.h"

GameEngine::GameEngine(Main* main)
{
	this->main = main;


}

GameEngine::~GameEngine()
{
}

void GameEngine::Awake()
{
	
	this->windowSize.x = screenWidth;
	this->windowSize.y = screenHeight;


	this->renderer = new Renderer(this);
	this->renderer->InitRenderer(*main->GetInstanceHandle(), main->GetWindowHangle(), true);

	this->soundEngine = new SoundEngine(this);

	this->cBufferManager = new CBufferManager(this);

	this->collisionManager = new CollisionManager(this);

	this->debugUtility = new DebugUtility(this);

	this->lightManager = new LightManager(this);
	lightManager->Awake();


	this->assetsManager = new AssetsManager(this);
	this->assetsManager->Awake();

	this->wicFactory = new WicFactory(this);

	this->input = new Input();
	this->input->Awake(*main->GetInstanceHandle(), main->GetWindowHangle());

	this->shadowMap = new ShadowMap(this);
	this->shadowMap->CreateShadowMap(ShadowMap::ShadowQuality::High);


	this->sceneManager = new SceneManager(this);
	this->sceneManager->SetDefaultScene();


	SetFullScreen(FALSE);


}

void GameEngine::Update()
{
	if (activeScene != nextScene)
	{
		SwichScene();
	}

	this->mouseDeltaX = input->GetMouseX() - oldMousePosX;
	this->mouseDeltaY = input->GetMouseY() - oldMousePosY;


	this->oldMousePosX = input->GetMouseX();
	this->oldMousePosY = input->GetMouseY();

	this->input->Update();
 	this->activeScene->Update();

	this->activeScene->LateUpdate();

	collisionManager->Update();
	lightManager->Update();



}

void GameEngine::Draw()
{
	this->shadowMap->ShadowMapping();



	renderer->Clear();

	this->activeScene->Draw();


	renderer->Present();

}

void GameEngine::Uninit()
{

	this->activeScene->Uninit();

	this->input->Uninit();
	delete input;

	this->assetsManager->Uninit();
	delete assetsManager;


	delete lightManager;

	delete debugUtility;

	delete cBufferManager;

	delete shadowMap;

	delete wicFactory;

	delete sceneManager;
	delete soundEngine;
	delete collisionManager;

	this->renderer->UninitRenderer();
	delete renderer;

}

long GameEngine::GetMouseMoveX(void)
{
	return mouseDeltaX;
}

long GameEngine::GetMouseMoveY(void)
{
	return mouseDeltaY;
}

float GameEngine::GetDeltaTime(void)
{
	return main->GetDeltaTime();
}

XMFLOAT2 GameEngine::GetWindowSize(void)
{
	return this->windowSize;
}

AssetsManager* GameEngine::GetAssetsManager(void)
{
	return this->assetsManager;
}

Renderer* GameEngine::GetRenderer(void)
{
	return this->renderer;
}

CBufferManager* GameEngine::GetCBufferManager(void)
{
	return this->cBufferManager;
}

Input* GameEngine::GetInput(void)
{
	return this->input;
}

CollisionManager* GameEngine::GetCollisionManager(void)
{
	return this->collisionManager;
}

LightManager* GameEngine::GetLightmanager(void)
{
	return this->lightManager;
}

ShadowMap* GameEngine::GetShadowMap(void)
{
	return this->shadowMap;
}

SoundEngine* GameEngine::GetSoundEngine(void)
{
	return this->soundEngine;
}

WicFactory* GameEngine::GetWicFactory(void)
{
	return this->wicFactory;
}

DebugUtility* GameEngine::GetDebugUtility(void)
{
	return this->debugUtility;
}


Scene* GameEngine::GetActiveScene(void)
{
	return this->activeScene;
}

void GameEngine::SetActiveScene(Scene* scene)
{
	this->nextScene = scene;

}

SceneManager* GameEngine::GetSceneManager(void)
{
	return this->sceneManager;
}

void GameEngine::SetFullScreen(BOOL flag)
{
	if (flag == fullscreen)
		return;

	fullscreen = flag;
	main->ToggleFullScreen();

}

void GameEngine::ChengeWindowSize(int width, int height)
{
	this->windowSize.x = width;
	this->windowSize.y = height;
	if (fullscreen)
		return;

	main->ChengeWindowSize(width, height);
}

void GameEngine::SetMainCamera(CameraComponent* camera)
{
	this->mainCamera = camera;
}

CameraComponent* GameEngine::GetMainCamera(void)
{
	return this->mainCamera;
}

HWND GameEngine::GetWindowHandle(void)
{
	return main->GetWindowHangle();
}

void GameEngine::Exit(void)
{
	this->main->Exit();
}

void GameEngine::SetNextScene(Scene* scene)
{
	this->nextScene = scene;
}

void GameEngine::SwichScene(void)
{
	if (this->activeScene) this->activeScene->Uninit();
	this->activeScene = nextScene;
	activeScene->Awake();
	activeScene->Init();
}



