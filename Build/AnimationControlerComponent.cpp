#include "AnimationControlerComponent.h"
#include "AssetsManager.h"
#include "MeshData.h"
#include "gameobject.h"
#include "GameEngine.h"
#include "Scene.h"
#include "MeshComponent.h"
#include "AnimationData.h"
#include "transformcomponent.h"
#include "input.h"

AnimationControlerComponent::AnimationControlerComponent(GameObject* gameObject)
{
	pGameObject = gameObject;
	pAssetsManager = pGameObject->GetScene()->GetGameEngine()->GetAssetsManager();

}

AnimationControlerComponent::~AnimationControlerComponent()
{

}

void AnimationControlerComponent::Awake(void)
{
	Component::Awake();
	defaultAnimIndex = 0;
}

void AnimationControlerComponent::Init(void)
{
	Component::Init();

	timeCnt = 0.0f;
}

void AnimationControlerComponent::Update(void)
{
	Component::Update();

	this->activeAnim->UpdateAnimation(pGameObject);

	for (pair<AnimParameter, string>& condition : conditionArray)
	{
		if (condition.first.isTrigger)
		{
			condition.first.value = FALSE;
		}
	}
}

void AnimationControlerComponent::Uninit(void)
{
	Component::Uninit();
}

void AnimationControlerComponent::LoadDefaulAnimation(string fileName, string name)
{
	AnimationNode* node = new AnimationNode(this);
	node->CreateNode(fileName, name, TRUE);
	activeAnim = node;
	AnimNodeArray.push_back(node);
}

void AnimationControlerComponent::LoadAnimation(string fileName, string name, BOOL loop)
{
	AnimationNode* node = new AnimationNode(this);
	node->CreateNode(fileName, name, loop);
	AnimNodeArray.push_back(node);
	
}

void AnimationControlerComponent::CreateTransition(
	string beforeAnimName,//このアニメーションから
	string afterAnimName,//このアニメーションに
	string conditionName,//このコンディションが
	BOOL needCondition,//この値になった時に
	float transitionTime)//この時間をかけて移行する
{

	AnimationNode* beforeNode = nullptr;
	AnimationNode* afterNode = nullptr;

	for (AnimationNode* node:AnimNodeArray)
	{
		if (node->GetName()==beforeAnimName)
		{
			beforeNode = node;
			break;
		}
		
	}
	if (beforeNode == nullptr)
		return;

	for (AnimationNode* node:AnimNodeArray)
	{
		if (node->GetName()==afterAnimName)
		{
			afterNode = node;
		}
		
	}
	if (afterNode == nullptr)
		return;

	int conditionIndex = -1;
	for (int i = 0; i < conditionArray.size(); i++)
	{
		if (conditionArray[i].second==conditionName)
		{
			conditionIndex = i;

		}
	}
	if (conditionIndex == -1)
		return;

	AnimationTransition* transition = new AnimationTransition(this);
	transition->CreateTransition(beforeNode, afterNode, transitionTime, conditionIndex, needCondition);
	beforeNode->AddTransition(transition);
}

void AnimationControlerComponent::CreateTransition(string beforeAnimName, string afterAnimName, string conditionName, BOOL needCondition, int transitionFrame)
{
	AnimationNode* beforeNode = nullptr;
	AnimationNode* afterNode = nullptr;

	for (AnimationNode* node : AnimNodeArray)
	{
		if (node->GetName() == beforeAnimName)
		{
			beforeNode = node;
			break;
		}

	}
	if (beforeNode == nullptr)
		return;

	for (AnimationNode* node : AnimNodeArray)
	{
		if (node->GetName() == afterAnimName)
		{
			afterNode = node;
		}

	}
	if (afterNode == nullptr)
		return;

	int conditionIndex = -1;
	for (int i = 0; i < conditionArray.size(); i++)
	{
		if (conditionArray[i].second == conditionName)
		{
			conditionIndex = i;

		}
	}
	if (conditionIndex == -1)
		return;

	float transitionTime = ((float)transitionFrame) / 60.0f;

	AnimationTransition* transition = new AnimationTransition(this);
	transition->CreateTransition(beforeNode, afterNode, transitionTime, conditionIndex, needCondition);
	beforeNode->AddTransition(transition);

}

void AnimationControlerComponent::CreateTransition(string beforeAnimName, string afterAnimName, string conditionName, BOOL needCondition)
{
	AnimationNode* beforeNode = nullptr;
	AnimationNode* afterNode = nullptr;

	for (AnimationNode* node : AnimNodeArray)
	{
		if (node->GetName() == beforeAnimName)
		{
			beforeNode = node;
			break;
		}

	}
	if (beforeNode == nullptr)
		return;

	for (AnimationNode* node : AnimNodeArray)
	{
		if (node->GetName() == afterAnimName)
		{
			afterNode = node;
		}

	}
	if (afterNode == nullptr)
		return;

	int conditionIndex = -1;
	for (int i = 0; i < conditionArray.size(); i++)
	{
		if (conditionArray[i].second == conditionName)
		{
			conditionIndex = i;
		}
	}
	if (conditionIndex == -1)
		return;


	AnimationTransition* transition = new AnimationTransition(this);
	transition->CreateTransition(beforeNode, afterNode, 0.25f, conditionIndex, needCondition);
	beforeNode->AddTransition(transition);

}

void AnimationControlerComponent::CreateNotLoopAnimExitTransition(
	string beforeAnimName,//このアニメーションから
	string afterAnimName,//このアニメーションに
	float transitionTime)//この時間をかけて移行する
{

	AnimationNode* beforeNode = nullptr;
	AnimationNode* afterNode = nullptr;

	for (AnimationNode* node : AnimNodeArray)
	{
		if (node->GetName() == beforeAnimName)
		{
			beforeNode = node;
			break;
		}

	}
	if (beforeNode == nullptr)
		return;

	for (AnimationNode* node : AnimNodeArray)
	{
		if (node->GetName() == afterAnimName)
		{
			afterNode = node;
		}

	}
	if (afterNode == nullptr)
		return;


	AnimationTransition* transition = new AnimationTransition(this);
	transition->CreateExitTransition(beforeNode, afterNode, transitionTime);
	beforeNode->SetNotLoopExitTransition(transition);

}

void AnimationControlerComponent::CreateNotLoopAnimExitTransition(string beforeAnimName, string afterAnimName, int transitionFrame)
{
	AnimationNode* beforeNode = nullptr;
	AnimationNode* afterNode = nullptr;

	for (AnimationNode* node : AnimNodeArray)
	{
		if (node->GetName() == beforeAnimName)
		{
			beforeNode = node;
			break;
		}

	}
	if (beforeNode == nullptr)
		return;

	for (AnimationNode* node : AnimNodeArray)
	{
		if (node->GetName() == afterAnimName)
		{
			afterNode = node;
		}

	}
	if (afterNode == nullptr)
		return;

	float transitionTime = ((float)transitionFrame) / 60.0f;

	AnimationTransition* transition = new AnimationTransition(this);
	transition->CreateExitTransition(beforeNode, afterNode, transitionTime);
	beforeNode->SetNotLoopExitTransition(transition);

}

void AnimationControlerComponent::CreateNotLoopAnimExitTransition(string beforeAnimName, string afterAnimName)
{
	AnimationNode* beforeNode = nullptr;
	AnimationNode* afterNode = nullptr;

	for (AnimationNode* node : AnimNodeArray)
	{
		if (node->GetName() == beforeAnimName)
		{
			beforeNode = node;
			break;
		}

	}
	if (beforeNode == nullptr)
		return;

	for (AnimationNode* node : AnimNodeArray)
	{
		if (node->GetName() == afterAnimName)
		{
			afterNode = node;
		}

	}
	if (afterNode == nullptr)
		return;


	AnimationTransition* transition = new AnimationTransition(this);
	transition->CreateExitTransition(beforeNode, afterNode, 0.25f);
	beforeNode->SetNotLoopExitTransition(transition);

}

AssetsManager* AnimationControlerComponent::GetAssetsmanager(void)
{
	return this->pAssetsManager;
}

GameEngine* AnimationControlerComponent::GetGameEngine(void)
{
	return this->pGameEngine;
}

void AnimationControlerComponent::UpdateAnimation(MtxNode* node, GameObject* gameObject)
{

	XMMATRIX frameMtx = node->GetFrameMtx(timeCnt);

	gameObject->GetTransFormComponent()->SetLocalMtx(frameMtx);

	for (int i = 0; i < node->GetChildCnt(); i++)
	{
		MtxNode* child = node->GetChild(i);
		GameObject* childObj = gameObject->GetChild(i);

		UpdateAnimation(child, childObj);

	}

}
void AnimationControlerComponent::CreateCondition(string name, AnimParameter initValue)
{


	conditionArray.push_back(make_pair(initValue, name));

}
void AnimationControlerComponent::SetCondition(string name, BOOL setValue)
{
	for (pair<AnimParameter,string>& condition:conditionArray)
	{
		if (condition.second == name)
		{
			condition.first.value = setValue;
		}
	}
}

BOOL AnimationControlerComponent::GetCondition(string name)
{
	for (pair<AnimParameter, string> condition : conditionArray)
	{
		if (condition.second == name)
		{
			return condition.first.value;
		}
	}
	return 0;
}

BOOL AnimationControlerComponent::GetCondition(int index)
{
	return this->conditionArray[index].first.value;
}

void AnimationControlerComponent::SetActiveAnimation(Animation* animation)
{
	this->activeAnim = animation;
}

AnimationTransition::AnimationTransition(AnimationControlerComponent* controler)
{
	this->controler = controler;
	this->pAssetsManager = controler->GetAssetsmanager();
	this->pGameEngine = controler->GetGameEngine();
}

AnimationTransition::~AnimationTransition()
{
}

void AnimationTransition::CreateTransition(AnimationNode* beforeAnimNode, AnimationNode* afterAnimNode, float transitionTime, int coditionIndex,BOOL needCondition)
{
	this->beforeAnimNode = beforeAnimNode;
	this->beforeAnimData = beforeAnimNode->GetAnimData();
	this->afterAnimNode = afterAnimNode;
	this->afterAnimData = afterAnimNode->GetAnimData();
	this->transitionTime = transitionTime;
	this->needConditionIndex = coditionIndex;
	this->needCondition = needCondition;
}

void AnimationTransition::CreateExitTransition(AnimationNode* beforeAnimNode, AnimationNode* afterAnimNode, float transitionTime)
{
	this->beforeAnimNode = beforeAnimNode;
	this->beforeAnimData = beforeAnimNode->GetAnimData();
	this->afterAnimNode = afterAnimNode;
	this->afterAnimData = afterAnimNode->GetAnimData();
	this->transitionTime = transitionTime;

}



void AnimationTransition::UpdateAnimation(GameObject* gameObject)
{
	MtxNode* root1 = beforeAnimData->GetMtxTreeRoot();
	MtxNode* root2 = afterAnimData->GetMtxTreeRoot();


	weight2 = timeCnt / transitionTime;
	weight1 = 1.0f - weight2;

	for (int i = 0; i < root1->GetChildCnt(); i++)
	{
		MtxNode* child1 = root1->GetChild(i);
		MtxNode* child2 = root2->GetChild(i);
		GameObject* childObj = gameObject->GetChild(i);

		UpdateMtx(child1,child2, childObj);

	}



	float deltaTime = pGameEngine->GetDeltaTime();
	timeCnt += deltaTime;
	beforeAnimCnt += deltaTime;
	afterAnimCnt += deltaTime;


	if (timeCnt > transitionTime)
	{
		float overTime = timeCnt - transitionTime;
		afterAnimNode->StartAnimation(overTime);
	}



}

float AnimationTransition::GetTransitionTime(void)
{
	return transitionTime;
}

BOOL AnimationTransition::CheckCondition(void)
{
	if (controler->GetCondition(this->needConditionIndex) == needCondition)
	{
		return TRUE;

	}
	return FALSE;
}

void AnimationTransition::StartTransition(float beforeAnimCnt, float afterAnimCnt)
{
	timeCnt = afterAnimCnt;
	this->afterAnimCnt = afterAnimCnt;
	this->beforeAnimCnt = beforeAnimCnt;
	this->controler->SetActiveAnimation(this);

}

void AnimationTransition::UpdateMtx(MtxNode* node1, MtxNode* node2 , GameObject* gameObject)
{

	XMMATRIX frameMtx1 = node1->GetFrameMtx(beforeAnimCnt);
	XMMATRIX frameMtx2 = node2->GetFrameMtx(afterAnimCnt);

	XMMATRIX blendMtx = (frameMtx1 * weight1) + (frameMtx2 * weight2);
	

	gameObject->GetTransFormComponent()->SetLocalMtx(blendMtx);

	for (int i = 0; i < node1->GetChildCnt(); i++)
	{
		MtxNode* child1 = node1->GetChild(i);
		MtxNode* child2 = node2->GetChild(i);
		GameObject* childObj = gameObject->GetChild(i);

		UpdateMtx(child1, child2, childObj);

	}


}


AnimationNode::AnimationNode(AnimationControlerComponent* controler)
{
	this->controler = controler;
	this->pAssetsManager = controler->GetAssetsmanager();
	this->pGameEngine = controler->GetGameEngine();
	this->exitTransition = nullptr;
}

AnimationNode::~AnimationNode()
{
}

void AnimationNode::UpdateAnimation(GameObject* gameObject)
{
	MtxNode* root = animData->GetMtxTreeRoot();

	for (int i = 0; i < root->GetChildCnt(); i++)
	{
		MtxNode* child = root->GetChild(i);
		GameObject* childObj = gameObject->GetChild(i);

		UpdateMtx(child, childObj);
	}

	timeCnt += pGameEngine->GetDeltaTime();

	if (loop)
	{
		if (timeCnt > endTime)
		{
			timeCnt -= endTime;
		}



	}
	else
	{
		if (timeCnt > exitTime)
		{

			float overTime = timeCnt - exitTime;
			if(exitTransition!=nullptr) exitTransition->StartTransition(timeCnt, overTime);
		}
	}
	for (AnimationTransition* transition : transitionArray)
	{

		if (transition->CheckCondition())
		{
			transition->StartTransition(timeCnt, 0.0f);
			break;
		}
	}


}

void AnimationNode::CreateNode(string fileName, string name, BOOL loop)
{
	this->animData = pAssetsManager->LoadAnimationData(fileName);
	this->name = name;
	this->loop = loop;
	this->endTime = ((float)animData->GetFrameNum()) / 60.0f;
	
}

void AnimationNode::SetLoop(BOOL loop)
{
	this->loop = loop;
}

AnimationData* AnimationNode::GetAnimData(void)
{
	return this->animData;
}

string AnimationNode::GetName(void)
{
	return this->name;
}

void AnimationNode::AddTransition(AnimationTransition* transition)
{
	this->transitionArray.push_back(transition);
}

void AnimationNode::SetNotLoopExitTransition(AnimationTransition* transition)
{
	this->exitTransition = transition;
	this->exitTime = transition->GetTransitionTime();
}

void AnimationNode::StartAnimation(float startTime)
{
	this->timeCnt = startTime;
	controler->SetActiveAnimation(this);
}

void AnimationNode::UpdateMtx(MtxNode* node, GameObject* gameObject)
{
	XMMATRIX frameMtx = node->GetFrameMtx(timeCnt);

	gameObject->GetTransFormComponent()->SetLocalMtx(frameMtx);

	for (int i = 0; i < node->GetChildCnt(); i++)
	{
		MtxNode* child = node->GetChild(i);
		GameObject* childObj = gameObject->GetChild(i);

		UpdateMtx(child, childObj);

	}

}

Animation::Animation()
{
	timeCnt = 0.0f;
}

Animation::~Animation()
{
}

float Animation::GetTimeCnt(void)
{
	return this->timeCnt;
}

void Animation::SetTimeCnt(float cnt)
{
	this->timeCnt = cnt;
}
