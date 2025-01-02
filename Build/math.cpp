#include"math.h"

XMMATRIX mtxrotX(float x)
{
	float sx = sinf(x);
	float cx = cosf(x);

	XMMATRIX mtxrotx = {
		1.0f,0.0f,0.0f,0.0f,
		0.0f,cx,-sx,0.0f,
		0.0f,sx,cx,0.0f,
		0.0f,0.0f,0.0f,1.0f,

	};
	return mtxrotx;
}
XMMATRIX mtxrotY(float y)
{
	float sy = sinf(y);
	float cy = cosf(y);

	XMMATRIX mtxroty = {
		cy,0.0f,sy,0.0f,
		0.0f,1.0f,0.0f,0.0f,
		-sy,0.0f,cy,0.0f,
		0.0f,0.0f,0.0f,1.0f,

	};
	return mtxroty;

}
XMMATRIX mtxrotZ(float z)
{
	float sz = sinf(z);
	float cz = cosf(z);

	XMMATRIX mtxrotz = {
		cz,-sz,0.0f,0.0f,
		sz,cz,0.0f,0.0f,
		0.0f,0.0f,1.0f,0.0f,
		0.0f,0.0f,0.0f,1.0f,

	};
	return mtxrotz;

}

XMMATRIX mtxrotZYX(float x, float y, float z)
{
	XMMATRIX mtxrotzyx;
	float sx = sinf(x);
	float cx = cosf(x);
	float sy = sinf(y);
	float cy = cosf(y);
	float sz = sinf(z);
	float cz = cosf(z);



	mtxrotzyx = {
		(cy * cz),(sx * sy * cz - cx * sz),(cx * sy * cz + sx * sz),0.0f,
		(cy * sz),(sx * sy * sz + cx * cz),(cx * sy * sz - sx * cz),0.0f,
		(-sy),(sx * cy),(cx * cy),0.0f,
		0.0f,0.0f,0.0f,1.0f,

	};

	return mtxrotzyx;
}

XMMATRIX mtxrotZXY(float x, float y, float z)
{
	XMMATRIX mtxrotzyx;
	float sx = sinf(x);
	float cx = cosf(x);
	float sy = sinf(y);
	float cy = cosf(y);
	float sz = sinf(z);
	float cz = cosf(z);



	mtxrotzyx = {
		(-sx * sy * sz + cy * cz),(-cx * sz),(sx * cy * sz + sy * cz),0.0f,
		(sx * sy * cz + cy * sz),(cx * cz),(-sx * cy * cz + sy * sz),0.0f,
		(-cx * sy),(sx),(cx * cy),0.0f,
		0.0f,0.0f,0.0f,1.0f,

	};

	return mtxrotzyx;
}
XMMATRIX mtxrotYXZ(float x, float y, float z)
{
	XMMATRIX mtxrotzyx;
	float sx = sinf(x);
	float cx = cosf(x);
	float sy = sinf(y);
	float cy = cosf(y);
	float sz = sinf(z);
	float cz = cosf(z);



	mtxrotzyx = {
		(sx * sy * sz + cy * cz),(sx * sy * cz - cy * sz),(cx * sy),0.0f,
		(cx * sz),(cx * cz),(-sx),0.0f,
		(sx * cy * sz - sy * cz),(sx * cy * cz + sy * sz),(cx * cy),0.0f,
		0.0f,0.0f,0.0f,1.0f,

	};

	return mtxrotzyx;
}

XMMATRIX mtxrotXYZ(float x, float y, float z)
{
	XMMATRIX mtxrotzyx;
	float sx = sinf(x);
	float cx = cosf(x);
	float sy = sinf(y);
	float cy = cosf(y);
	float sz = sinf(z);
	float cz = cosf(z);



	mtxrotzyx = {
		(cy * cz),(-cy * sz),(sy),0.0f,
		(sx * sy * cz + cx * sz),(-sx * sy * sz + cx * cz),(-sx * cy),0.0f,
		(-cx * sy * cz + sx * sz),(cx * sy * sz + sx * cz),(cx * cy),0.0f,
		0.0f,0.0f,0.0f,1.0f,

	};

	return mtxrotzyx;
}






XMVECTOR xonevec(void)
{
	XMFLOAT3 x = { 1.0f,0.0f,0.0f };

	XMVECTOR vec = XMLoadFloat3(&x);
	return vec;
}

XMVECTOR yonevec(void)
{
	XMFLOAT3 y = { 0.0f,1.0f,0.0f };

	XMVECTOR vec = XMLoadFloat3(&y);
	return vec;
}

XMVECTOR zonevec(void)
{
	XMFLOAT3 z = { 0.0f,0.0f,1.0f };

	XMVECTOR vec = XMLoadFloat3(&z);
	return vec;
}

float XMFLOAT3Length(XMFLOAT3 p1, XMFLOAT3 p2)
{
	XMVECTOR p1v = XMLoadFloat3(&p1);
	XMVECTOR p2v = XMLoadFloat3(&p2);
	XMVECTOR lenV = p2v - p1v;
	XMVECTOR len = XMVector3Length(lenV);
	float ans;
	XMStoreFloat(&ans, len);

	return ans;
}


// PhysXÇÃPxVec3ÇDirectXMathÇÃXMVECTORÇ…ïœä∑
XMVECTOR PxVec3ToXMVECTOR(const PxVec3& vec) {
	return XMVectorSet(vec.x, vec.y, vec.z, 0.0f);
}

// PhysXÇÃPxQuatÇDirectXMathÇÃXMVECTORÇ…ïœä∑
XMVECTOR PxQuatToXMVECTOR(const PxQuat& quat) {
	return XMVectorSet(quat.x, quat.y, quat.z, quat.w);
}

// PhysXÇÃPxMat44ÇDirectXMathÇÃXMMATRIXÇ…ïœä∑
XMMATRIX PxMat44ToXMMATRIX(const PxMat44& mat) {
	return XMMATRIX(
		mat.column0.x, mat.column0.y, mat.column0.z, mat.column0.w,
		mat.column1.x, mat.column1.y, mat.column1.z, mat.column1.w,
		mat.column2.x, mat.column2.y, mat.column2.z, mat.column2.w,
		mat.column3.x, mat.column3.y, mat.column3.z, mat.column3.w
	);
}

// DirectXMathÇÃXMVECTORÇPhysXÇÃPxVec3Ç…ïœä∑
PxVec3 XMVECTORToPxVec3(const XMVECTOR& vec) {
	XMFLOAT3 temp;
	XMStoreFloat3(&temp, vec);
	return PxVec3(temp.x, temp.y, temp.z);
}

// DirectXMathÇÃXMVECTORÇPhysXÇÃPxQuatÇ…ïœä∑
PxQuat XMVECTORToPxQuat(const XMVECTOR& vec) {
	XMFLOAT4 temp;
	XMStoreFloat4(&temp, vec);
	return PxQuat(temp.x, temp.y, temp.z, temp.w);
}

// DirectXMathÇÃXMMATRIXÇPhysXÇÃPxMat44Ç…ïœä∑
PxMat44 XMMATRIXToPxMat44(const XMMATRIX& mat) {
	PxMat44 result;
	XMStoreFloat4x4(reinterpret_cast<XMFLOAT4X4*>(&result), mat);
	return result;
}

// XMFLOAT3Ç©ÇÁPxVec3Ç÷ÇÃïœä∑
PxVec3 XMFLOAT3ToPxVec3(const XMFLOAT3& vec) {
	return PxVec3(vec.x, vec.y, vec.z);
}

// PxVec3Ç©ÇÁXMFLOAT3Ç÷ÇÃïœä∑
XMFLOAT3 PxVec3ToXMFLOAT3(const PxVec3& vec) {
	return XMFLOAT3(vec.x, vec.y, vec.z);
}

// XMFLOAT4Ç©ÇÁPxVec3Ç÷ÇÃïœä∑ (X, Y, Zê¨ï™ÇÃÇ›égóp)
PxVec3 XMFLOAT4ToPxVec3(const XMFLOAT4& vec) {
	return PxVec3(vec.x, vec.y, vec.z);
}

// PxVec3Ç©ÇÁXMFLOAT4Ç÷ÇÃïœä∑ (Wê¨ï™Ç0Ç…ê›íË)
XMFLOAT4 PxVec3ToXMFLOAT4(const PxVec3& vec) {
	return XMFLOAT4(vec.x, vec.y, vec.z, 0.0f);
}

// XMFLOAT4Ç©ÇÁPxQuatÇ÷ÇÃïœä∑
PxQuat XMFLOAT4ToPxQuat(const XMFLOAT4& vec) {
	return PxQuat(vec.x, vec.y, vec.z, vec.w);
}

// PxQuatÇ©ÇÁXMFLOAT4Ç÷ÇÃïœä∑
XMFLOAT4 PxQuatToXMFLOAT4(const PxQuat& quat) {
	return XMFLOAT4(quat.x, quat.y, quat.z, quat.w);
}
