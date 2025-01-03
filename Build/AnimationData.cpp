#include "AnimationData.h"

MtxNode::MtxNode()
{
}

MtxNode::~MtxNode()
{
}

void MtxNode::LoadAnimation(FbxNode* node, MtxNode* parent, AnimationData* animdata)
{
	using namespace fbxsdk;
	name = node->GetName();
	pAnimData = animdata;
	this->parent = parent;
	if (parent == nullptr)
	{
		this->isRoot = TRUE;
		this->attribute = Attribute::Root;

		
	}
	else
	{

		if (node->GetNodeAttribute()->GetAttributeType() == FbxNodeAttribute::eMesh)
		{
			this->attribute = Attribute::Mesh;
		}
		else if (node->GetNodeAttribute()->GetAttributeType() == FbxNodeAttribute::eSkeleton)
		{
			this->attribute = Attribute::Bone;
		}
		else
		{
			this->attribute = Attribute::Null;
		}
		this->isRoot = FALSE;


		CreateFrameMtxArray(pAnimData->GetFrameNum());

		for (int i = 0; i < pAnimData->GetFrameNum(); i++)
		{
			FbxMatrix framemtx = node->EvaluateLocalTransform(pAnimData->GetStartTime() + pAnimData->GetOneFrameValue() * i);

			XMMATRIX frameMtx = FbxMatrixConvertToXMMATRIX(framemtx);

			this->frameMtxArray[i] = frameMtx;
		}
	}


	for (int i = 0; i < node->GetChildCount(); i++)
	{
		FbxNode* child = node->GetChild(i);

		if (child->GetNodeAttribute()->GetAttributeType() == FbxNodeAttribute::eMesh)
		{
			MtxNode* childNode = new MtxNode();
			childNode->LoadAnimation(child, this, pAnimData);
			childArray.push_back(childNode);
		}
		else if (child->GetNodeAttribute()->GetAttributeType() == FbxNodeAttribute::eSkeleton)
		{
			MtxNode* childNode = new MtxNode();
			childNode->LoadAnimation(child, this, pAnimData);
			childArray.push_back(childNode);
		}
		else
		{
			MtxNode* childNode = new MtxNode();
			childNode->LoadAnimation(child, this, pAnimData);
			childArray.push_back(childNode);

		}
	}




}


void MtxNode::CreateFrameMtxArray(int n)
{
	this->frameMtxArray = new XMMATRIX[n];

}

XMMATRIX MtxNode::GetFrameMtx(float time)
{

	float frame = time * 60.0f;
	float frame2weight = frame - (float)(int)frame;
	float frame1weight = 1.0f - frame2weight;;



	int frame1 = int(frame);
	
	if (frame1 >= (float)pAnimData->GetFrameNum()-1)
	{
		frame1 %= pAnimData->GetFrameNum();
	}
	int frame2 = frame1 + 1;


	if (frame2 >= pAnimData->GetFrameNum()-1)
	{
		frame2 = 0;
	}

	XMMATRIX mtx1 = this->frameMtxArray[frame1];
	XMMATRIX mtx2 = this->frameMtxArray[frame2];

	return (mtx1 * frame1weight) + (mtx2 * frame2weight);

}

int MtxNode::GetChildCnt(void)
{
	return this->childArray.size();
}

MtxNode* MtxNode::GetChild(int n)
{
	return this->childArray[n];
}


AnimationData::AnimationData()
{
}

AnimationData::~AnimationData()
{
}

int AnimationData::GetFrameNum(void)
{
	return frameNum;
}

int AnimationData::GetFrameRate(void)
{
	return frameRate;
}

LONGLONG AnimationData::GetStartTime(void)
{
	return startTime;
}

LONGLONG AnimationData::GetOneFrameValue(void)
{
	return oneFrameValue;
}

string AnimationData::GetFileName(void)
{
	return fileName;
}

MtxNode* AnimationData::GetMtxTreeRoot(void)
{
	return mtxTreeRoot;
}

void AnimationData::LoadAnimation(string fileName, AssetsManager* assetsManager)
{

	this->fileName = fileName;

	FbxManager* manager;
	FbxIOSettings* ioSettings;

	manager = FbxManager::Create();
	ioSettings = FbxIOSettings::Create(manager, IOSROOT);



	// Importer�𐶐�
	FbxImporter* importer = FbxImporter::Create(manager, "");

	if (importer->Initialize(fileName.c_str(), -1, manager->GetIOSettings()) == false)
	{
		// �C���|�[�g�G���[
	}


	//Scene�I�u�W�F�N�g��FBX�t�@�C�����̏��𗬂�����
	FbxScene* scene = FbxScene::Create(manager, "scene");
	importer->Import(scene);

	

	int meshcount = scene->GetSrcObjectCount<FbxMesh>();

	//�A�j���[�V�������ꗗ���i�[����z��̐錾
	FbxArray<FbxString*> animation_names;

	//�V�[������A�j���[�V�����ꗗ���擾���i�[
	scene->FillAnimStackNameArray(animation_names);

	int animcount = animation_names.GetCount();
	int framenum = 0;
	FbxTime start_time = 0;
	FbxTime end_time = 0;
	FbxLongLong oneFrameValue = FbxTime::GetOneFrameValue(FbxTime::eFrames60);

	FbxTime totalframe = 0;

	if (animcount > 0)
	{
		//�A�j���ԍ�0�Ԃ�����FbxTakeInfo���擾
		auto take_info = scene->GetTakeInfo(animation_names[0]->Buffer());
		//�J�n����
		start_time = take_info->mLocalTimeSpan.GetStart();
		//�I������
		end_time = take_info->mLocalTimeSpan.GetStop();

		oneFrameValue = FbxTime::GetOneFrameValue(FbxTime::eFrames60);

		totalframe = (end_time - start_time) / oneFrameValue;

		framenum = (int)totalframe.Get();//�A�j���[�V�����̍��v�t���[����



	}

	this->startTime = start_time.Get();
	this->oneFrameValue = oneFrameValue;

	this->frameNum = framenum;

	this->mtxTreeRoot = new MtxNode();

	this->mtxTreeRoot->LoadAnimation(scene->GetRootNode(), nullptr, this);


}
