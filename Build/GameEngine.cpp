#include "GameEngine.h"
#include "Main.h"
#include "renderer.h"
#include "AssetsManager.h"
#include "input.h"
#include "SceneManager.h"
#include "Scene.h"
#include "CBufferManager.h"
#include "LightManager.h"
#include "CameraComponent.h"
#include "ShadowMap.h"
#include "SoundEngine.h"
#include "WicFactory.h"
#include "DebugUtility.h"
#include "PhysixEngine.h"

GameEngine::GameEngine(Main* main)
{
	this->main = main;
	accumulatedTime = 0.0f;
	fixedDeltaTime = 1.0f / 60.0f;
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

	this->physixEngine = new PhysxEngine(this);

	this->soundEngine = new SoundEngine(this);

	this->cBufferManager = new CBufferManager(this);


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

	accumulatedTime += GetDeltaTime();
	while (accumulatedTime >= fixedDeltaTime)
	{
		this->FixedUpdate();
		accumulatedTime -= fixedDeltaTime;
	}


	this->mouseDeltaX = input->GetMouseX() - oldMousePosX;
	this->mouseDeltaY = input->GetMouseY() - oldMousePosY;


	this->oldMousePosX = input->GetMouseX();
	this->oldMousePosY = input->GetMouseY();

	this->input->Update();
 	this->activeScene->Update();



	this->LateUpdate();

}

void GameEngine::FixedUpdate()
{
	this->physixEngine->Update();

}

void GameEngine::LateUpdate()
{
	this->activeScene->LateUpdate();
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

	delete physixEngine;

	delete lightManager;

	delete debugUtility;

	delete cBufferManager;

	delete shadowMap;

	delete wicFactory;

	delete sceneManager;
	delete soundEngine;

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

PhysxEngine* GameEngine::GetPhysixEngine(void)
{
	return this->physixEngine;
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
	this->windowSize.x = (float)width;
	this->windowSize.y = (float)height;
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

float GameEngine::GetFixedDeltaTime(void)
{
	return fixedDeltaTime;
}



