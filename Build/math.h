#pragma once
#include "CoreMinimal.h"
#include "FbxConvertDX11.h"
XMMATRIX mtxrotX(float x);
XMMATRIX mtxrotY(float y);
XMMATRIX mtxrotZ(float z);


XMMATRIX mtxrotZYX(float x, float y, float z);
XMMATRIX mtxrotZXY(float x, float y, float z);
XMMATRIX mtxrotYXZ(float x, float y, float z);

XMMATRIX mtxrotXYZ(float x, float y, float z);

XMVECTOR xonevec(void);
XMVECTOR yonevec(void);
XMVECTOR zonevec(void);

float XMFLOAT3Length(XMFLOAT3 p1, XMFLOAT3 p2);

XMVECTOR PxVec3ToXMVECTOR(const PxVec3& vec);

XMVECTOR PxQuatToXMVECTOR(const PxQuat& quat);

XMMATRIX PxMat44ToXMMATRIX(const PxMat44& mat);

PxVec3 XMVECTORToPxVec3(const XMVECTOR& vec);

PxQuat XMVECTORToPxQuat(const XMVECTOR& vec);

PxMat44 XMMATRIXToPxMat44(const XMMATRIX& mat);

PxVec3 XMFLOAT3ToPxVec3(const XMFLOAT3& vec);

XMFLOAT3 PxVec3ToXMFLOAT3(const PxVec3& vec);

PxVec3 XMFLOAT4ToPxVec3(const XMFLOAT4& vec);

XMFLOAT4 PxVec3ToXMFLOAT4(const PxVec3& vec);

PxQuat XMFLOAT4ToPxQuat(const XMFLOAT4& vec);

XMFLOAT4 PxQuatToXMFLOAT4(const PxQuat& quat);

