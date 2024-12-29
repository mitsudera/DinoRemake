#pragma once
#include "component.h"
class BoneData;
class SkinMeshLinkerComponent;
class BoneComponent : public Component
{
public:
	BoneComponent(GameObject* gameObject);
	~BoneComponent();
	virtual void LateUpdate(void)override;
	virtual void DebugDraw(void)override;
	XMMATRIX GetInitMtxInverse(void);

	void SetBone(BoneData* data, SkinMeshLinkerComponent* linker);

	XMMATRIX& GetBoneMtx(void);
private:
	XMMATRIX initMtx;
	XMMATRIX initMtxInv;
	XMMATRIX boneMtx;
	SkinMeshLinkerComponent* linker;
};

