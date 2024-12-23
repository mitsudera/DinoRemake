#pragma once
#include "component.h"

class AssetsManager;
class MeshData;
class MtxNode;
class AnimationControlerComponent;
class AnimationData;
class AnimationNode;

struct AnimParameter
{
	BOOL value;
	BOOL isTrigger;
};

class Animation
{
public:
	Animation();
	~Animation();

	virtual void UpdateAnimation(GameObject* gameObject)=0;

	float GetTimeCnt(void);
	void SetTimeCnt(float cnt);

protected:
	AnimationControlerComponent* controler;
	AssetsManager* pAssetsManager;
	GameEngine* pGameEngine;
	float timeCnt;


};

class AnimationTransition:public Animation
{
public:
	AnimationTransition(AnimationControlerComponent* controler);
	~AnimationTransition();

	void CreateTransition(AnimationNode* beforeAnimNode, AnimationNode* afterAnimNode, float transitionTime, int coditionIndex,BOOL needCondition);
	void CreateExitTransition(AnimationNode* beforeAnimNode, AnimationNode* afterAnimNode, float transitionTime);

	virtual void UpdateAnimation(GameObject* gameObject) override;
	float GetTransitionTime(void);

	BOOL CheckCondition(void);

	void StartTransition(float beforeAnimCnt,float afterAnimCnt);

private:
	AnimationNode* beforeAnimNode;
	AnimationNode* afterAnimNode;
	float transitionTime;
	AnimationData* beforeAnimData;
	AnimationData* afterAnimData;
	float beforeAnimCnt;
	float afterAnimCnt;
 
	float weight1;
	float weight2;

	BOOL needCondition;//�ڍs����true�ɂȂ�������false�ɂȂ��������H
	int needConditionIndex;//�ڍs����true�ɂȂ�������false�ɂȂ��������H


	void UpdateMtx(MtxNode* node1, MtxNode* node2, GameObject* gameObject);

};

class AnimationNode :public Animation
{
public:
	AnimationNode(AnimationControlerComponent* controler);
	~AnimationNode();

	virtual void UpdateAnimation(GameObject* gameObject)override;

	void CreateNode(string fileName, string name,BOOL loop);
	void SetLoop(BOOL loop);
	AnimationData* GetAnimData(void);
	string GetName(void);


	void AddTransition(AnimationTransition* transition);

	void SetNotLoopExitTransition(AnimationTransition* transition);

	void StartAnimation(float startTime);

private:
	AnimationData* animData;
	vector<AnimationTransition*> transitionArray;
	AnimationTransition* exitTransition;
	float endTime;
	float exitTime;
	BOOL loop;
	string name;

	void UpdateMtx(MtxNode* node, GameObject* gameObject);
};

//����̂̓��b�V���R���|�[�l���g�̃��[�g
class AnimationControlerComponent : public Component
{
public:

	enum class ANIM_STATE:int
	{
		STOP,
		TRANSFER,
		ANIMATION,
	};


	AnimationControlerComponent(GameObject* gameObject);
	~AnimationControlerComponent();


	virtual void Awake(void) override;
	virtual void Init(void) override;
	virtual void Update(void) override;
	virtual void Uninit(void) override;

	void LoadDefaulAnimation(string fileName, string name);
	void LoadAnimation(string fileName, string name, BOOL loop);

	void CreateTransition(
		string beforeAnimName,//���̃A�j���[�V��������
		string afterAnimName,//���̃A�j���[�V������
		string conditionName,//���̃R���f�B�V������
		BOOL needCondition,//���̒l�ɂȂ�������
		float transitionTime);//���̎��Ԃ������Ĉڍs����

	void CreateTransition(
		string beforeAnimName,//���̃A�j���[�V��������
		string afterAnimName,//���̃A�j���[�V������
		string conditionName,//���̃R���f�B�V������
		BOOL needCondition,//���̒l�ɂȂ�������
		int transitionFrame);//���̎��Ԃ������Ĉڍs����

	//transitionTime��0.25�b�Œ�
	void CreateTransition(
		string beforeAnimName,//���̃A�j���[�V��������
		string afterAnimName,//���̃A�j���[�V������
		string conditionName,//���̃R���f�B�V������
		BOOL needCondition);//���̒l�ɂȂ�������
	

	//���[�v���Ȃ��A�j���[�V�����p
	void CreateNotLoopAnimExitTransition(
		string beforeAnimName,//���̃A�j���[�V��������
		string afterAnimName,//���̃A�j���[�V������
		float transitionTime);//���̎��Ԃ������Ĉڍs����

	void CreateNotLoopAnimExitTransition(
		string beforeAnimName,//���̃A�j���[�V��������
		string afterAnimName,//���̃A�j���[�V������
		int transitionFrame);//���̎��Ԃ������Ĉڍs����

	//transitionTime��0.25�b�Œ�
	void CreateNotLoopAnimExitTransition(
		string beforeAnimName,//���̃A�j���[�V��������
		string afterAnimName);//���̃A�j���[�V������



	void CreateCondition(string name, AnimParameter initValue);
	void SetCondition(string name, BOOL setValue);
	BOOL GetCondition(string name);
	BOOL GetCondition(int index);


	void SetActiveAnimation(Animation* animation);


	AssetsManager* GetAssetsmanager(void);
	GameEngine* GetGameEngine(void);

protected:
	
	void UpdateAnimation(MtxNode* node, GameObject* gameObject);

	AssetsManager* pAssetsManager;

	vector<AnimationNode*> AnimNodeArray;

	vector<pair<AnimParameter,string>> conditionArray;

	Animation* activeAnim;

	float timeCnt;
	int framenum;
	BOOL animation;

	float animSpeed;

	BOOL frameBlendMode;

	int defaultAnimIndex;








};

