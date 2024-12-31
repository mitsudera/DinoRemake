//=============================================================================
//
// �����蔻�菈�� [collision.cpp]
// Author : 
//
//=============================================================================
#include "collision.h"
#include "TerrainColliderComponent.h"
//=============================================================================
// ����(dot)
//=============================================================================
float dotProduct(XMVECTOR* v1, XMVECTOR* v2)
{
#if 0
	float ans = v1->x * v2->x + v1->y * v2->y + v1->z * v2->z;
#else
	// �_�C���N�g�w�ł́A�A�A
	XMVECTOR temp = XMVector3Dot(*v1, *v2);
	float ans = 0.0f;
	XMStoreFloat(&ans, temp);
#endif

	return(ans);
}


//=============================================================================
// �O��(cross)
//=============================================================================
void crossProduct(XMVECTOR* ret, XMVECTOR* v1, XMVECTOR* v2)
{
#if 0
	ret->x = v1->y * v2->z - v1->z * v2->y;
	ret->y = v1->z * v2->x - v1->x * v2->z;
	ret->z = v1->x * v2->y - v1->y * v2->x;
#else
	// �_�C���N�g�w�ł́A�A�A
	* ret = XMVector3Cross(*v1, *v2);
#endif

}


//=============================================================================
// ���C�L���X�g
// p0, p1, p2�@�|���S���̂R���_
// pos0 �n�_
// pos1 �I�_
// hit�@��_�̕ԋp�p
// normal �@���x�N�g���̕ԋp�p
// �������Ă���ꍇ�ATRUE��Ԃ�
//=============================================================================
BOOL RayCast(XMFLOAT3 xp0, XMFLOAT3 xp1, XMFLOAT3 xp2, XMFLOAT3 xpos0, XMFLOAT3 xpos1, XMFLOAT3* hit, XMFLOAT3* normal)
{
	XMVECTOR	p0 = XMLoadFloat3(&xp0);
	XMVECTOR	p1 = XMLoadFloat3(&xp1);
	XMVECTOR	p2 = XMLoadFloat3(&xp2);
	XMVECTOR	pos0 = XMLoadFloat3(&xpos0);
	XMVECTOR	pos1 = XMLoadFloat3(&xpos1);

	XMVECTOR	nor;	// �|���S���̖@��
	XMVECTOR	vec1;
	XMVECTOR	vec2;
	float		d1, d2;

	{	// �|���S���̊O�ς��Ƃ��Ė@�������߂�(���̏����͌Œ蕨�Ȃ�\��Init()�ōs���Ă����Ɨǂ�)
		vec1 = p1 - p0;
		vec2 = p2 - p0;
		crossProduct(&nor, &vec2, &vec1);
		nor = XMVector3Normalize(nor);		// �v�Z���₷���悤�ɖ@�����m�[�}���C�Y���Ă���(���̃x�N�g���̒������P�ɂ��Ă���)
		XMStoreFloat3(normal, nor);			// ���߂��@�������Ă���
	}

	// �|���S�����ʂƐ����̓��ςƂ��ďՓ˂��Ă���\���𒲂ׂ�i�s�p�Ȃ�{�A�݊p�Ȃ�[�A���p�Ȃ�O�j
	vec1 = pos0 - p0;
	vec2 = pos1 - p0;
	{	// ���߂��|���S���̖@���ƂQ�̃x�N�g���i�����̗��[�ƃ|���S����̔C�ӂ̓_�j�̓��ςƂ��ďՓ˂��Ă���\���𒲂ׂ�
		d1 = dotProduct(&vec1, &nor);
		d2 = dotProduct(&vec2, &nor);
		if (((d1 * d2) > 0.0f) || (d1 == 0 && d2 == 0))
		{
			// �������Ă���\���͖���
			return(FALSE);
		}
	}


	{	// �|���S���Ɛ����̌�_�����߂�
		d1 = (float)fabs(d1);	// ��Βl�����߂Ă���
		d2 = (float)fabs(d2);	// ��Βl�����߂Ă���
		float a = d1 / (d1 + d2);							// ������

		XMVECTOR	vec3 = (1 - a) * vec1 + a * vec2;		// p0�����_�ւ̃x�N�g��
		XMVECTOR	p3 = p0 + vec3;							// ��_
		XMStoreFloat3(hit, p3);								// ���߂���_�����Ă���

		{	// ���߂���_���|���S���̒��ɂ��邩���ׂ�

			// �|���S���̊e�ӂ̃x�N�g��
			XMVECTOR	v1 = p1 - p0;
			XMVECTOR	v2 = p2 - p1;
			XMVECTOR	v3 = p0 - p2;

			// �e���_�ƌ�_�Ƃ̃x�N�g��
			XMVECTOR	v4 = p3 - p1;
			XMVECTOR	v5 = p3 - p2;
			XMVECTOR	v6 = p3 - p0;

			// �O�ςŊe�ӂ̖@�������߂āA�|���S���̖@���Ƃ̓��ς��Ƃ��ĕ������`�F�b�N����
			XMVECTOR	n1, n2, n3;

			crossProduct(&n1, &v4, &v1);
			if (dotProduct(&n1, &nor) < 0.0f) return(FALSE);	// �������Ă��Ȃ�

			crossProduct(&n2, &v5, &v2);
			if (dotProduct(&n2, &nor) < 0.0f) return(FALSE);	// �������Ă��Ȃ�

			crossProduct(&n3, &v6, &v3);
			if (dotProduct(&n3, &nor) < 0.0f) return(FALSE);	// �������Ă��Ȃ�
		}
	}

	return(TRUE);	// �������Ă���I(hit�ɂ͓������Ă����_�������Ă���Bnormal�ɂ͖@���������Ă���)
}

BOOL CollisionPointSphere(XMFLOAT3 point, XMFLOAT3 center, float r)
{
	BOOL ans = FALSE;

	XMVECTOR p = XMLoadFloat3(&point);
	XMVECTOR cp = XMLoadFloat3(&center);
	XMVECTOR lv = p - cp;

	float len;
	XMStoreFloat(&len, XMVector3Length(lv));

	if (len<r)
	{
		ans = TRUE;
	}
	return ans;
}
BOOL CollisionPointBox(XMFLOAT3 point, XMMATRIX boxMatrix)
{
	return FALSE;
}

BOOL CollisionPointCapsule(XMFLOAT3 point, XMFLOAT3 pos1, XMFLOAT3 pos2,float r)
{
	BOOL ans = FALSE;

	XMVECTOR p = XMLoadFloat3(&point);

	XMVECTOR p1 = XMLoadFloat3(&pos1);
	XMVECTOR p2 = XMLoadFloat3(&pos2);

	XMVECTOR p1c = p - p1;
	XMVECTOR p2c = p - p2;
	float p1l;
	float p2l;
	XMStoreFloat(&p1l, XMVector3Length(p1c));
	XMStoreFloat(&p2l, XMVector3Length(p2c));


	//�����̗��[���܂��͌���
	if (p1l < r || p2l < r)
	{
		return TRUE;
	}

	XMVECTOR lv = XMVector3LinePointDistance(p1, p2, p);
	float length;
	XMStoreFloat(&length, lv);
	if (length < r)
	{
		return TRUE;
	}

	return ans;
}

BOOL CollisionPointBox(XMFLOAT3 point, XMFLOAT3 center, XMFLOAT3 size)
{
	// �{�b�N�X�̊e�ӂ̍ŏ�����эő���W���v�Z
	XMFLOAT3 min = XMFLOAT3(center.x - size.x / 2.0f, center.y - size.y / 2.0f, center.z - size.z / 2.0f);
	XMFLOAT3 max = XMFLOAT3(center.x + size.x / 2.0f, center.y + size.y / 2.0f, center.z + size.z / 2.0f);

	// �_���{�b�N�X���ɂ��邩�ǂ������`�F�b�N
	if (point.x >= min.x && point.x <= max.x &&
		point.y >= min.y && point.y <= max.y &&
		point.z >= min.z && point.z <= max.z)
	{
		return TRUE; // �_���{�b�N�X���ɂ���ꍇ
	}
	return FALSE; // �_���{�b�N�X���ɂȂ��ꍇ
}

BOOL CollisionPointTerrain(XMFLOAT3 point,TerrainColliderComponent* terrain )
{

	XMFLOAT2 length;
	length.x = point.x - terrain->GetCenter().x;
	length.y = point.z - terrain->GetCenter().z;

	XMFLOAT2 terrainSize = terrain->GetSize();

	//�͈͓��ɂ��邩�H
	if (length.x > (terrainSize.x * 0.5) ||
		length.x < -(terrainSize.x * 0.5) ||
		length.y >(terrainSize.y * 0.5) ||
		length.y < -(terrainSize.y * 0.5))
	{

		return FALSE;

	}

	float height = terrain->GetHeight(point);

	if (height > point.y)
	{
		return TRUE;
	}

	return FALSE;

}






//�����Ƌ��̓����蔻��
BOOL CollisionLineSphere(XMFLOAT3 pos1, XMFLOAT3 pos2, XMFLOAT3 center ,float r)
{
	BOOL ans = FALSE;
	XMVECTOR p1 = XMLoadFloat3(&pos1);
	XMVECTOR p2 = XMLoadFloat3(&pos2);
	XMVECTOR cp = XMLoadFloat3(&center);

	XMVECTOR p1c = cp - p1;
	XMVECTOR p2c = cp - p2;
	float p1l;
	float p2l;
	XMStoreFloat(&p1l, XMVector3Length(p1c));
	XMStoreFloat(&p2l, XMVector3Length(p2c));


	//�����̗��[���܂��͌���
	if (p1l < r || p2l < r)
	{
		return TRUE;
	}

	XMVECTOR lv = XMVector3LinePointDistance(p1,p2,cp);
	float length;
	XMStoreFloat(&length, lv);
	if (length<r)
	{
		return TRUE;
	}

	return ans;

}

BOOL CollisionLineCapsule(XMFLOAT3 lp1, XMFLOAT3 lp2, XMFLOAT3 cp1, XMFLOAT3 cp2, float r)
{
	XMVECTOR lp1vec = XMLoadFloat3(&lp1);
	XMVECTOR lp2vec = XMLoadFloat3(&lp2);

	XMVECTOR cp1vec = XMLoadFloat3(&cp1);
	XMVECTOR cp2vec = XMLoadFloat3(&cp2);

	// �����̕����x�N�g��
	XMVECTOR lineDir = XMVectorSubtract(lp2vec, lp1vec);
	XMVECTOR capsuleDir = XMVectorSubtract(cp2vec, cp1vec);

	// �����ƃJ�v�Z���̍ŋߐړ_�����߂�
	float t1, t2;
	XMVECTOR closestLinePoint, closestCapsulePoint;
	ClosestPtSegmentSegment(lp1vec, lineDir, cp1vec, capsuleDir, t1, t2, closestLinePoint, closestCapsulePoint);

	// �ŋߐړ_�Ԃ̋������v�Z
	XMVECTOR distVec = XMVectorSubtract(closestLinePoint, closestCapsulePoint);
	float distSq = XMVectorGetX(XMVector3LengthSq(distVec));

	// �J�v�Z���̔��a���l�����ďՓ˔���
	return distSq <= (r * r);
}

BOOL CollisionLineBox(XMFLOAT3 lp1, XMFLOAT3 lp2, XMFLOAT3 center, XMFLOAT3 size)
{
	XMFLOAT3 boxMin(center.x - size.x / 2, center.y - size.y / 2, center.z - size.z / 2);
	XMFLOAT3 boxMax(center.x + size.x / 2, center.y + size.y / 2, center.z + size.z / 2);

	XMFLOAT3 direction(lp2.x - lp1.x, lp2.y - lp1.y, lp2.z - lp1.z);
	XMFLOAT3 invDirection(1.0f / direction.x, 1.0f / direction.y, 1.0f / direction.z);

	float t1 = (boxMin.x - lp1.x) * invDirection.x;
	float t2 = (boxMax.x - lp1.x) * invDirection.x;
	float t3 = (boxMin.y - lp1.y) * invDirection.y;
	float t4 = (boxMax.y - lp1.y) * invDirection.y;
	float t5 = (boxMin.z - lp1.z) * invDirection.z;
	float t6 = (boxMax.z - lp1.z) * invDirection.z;

	float tmin = max(max(min(t1, t2), min(t3, t4)), min(t5, t6));
	float tmax = min(min(max(t1, t2), max(t3, t4)), max(t5, t6));

	if (tmax < 0 || tmin > tmax)
		return FALSE;

	return TRUE;
}

BOOL CollisionLineTerrain(XMFLOAT3 lp1, XMFLOAT3 lp2, XMFLOAT3 center, XMFLOAT2 hw)
{
	// �n�`�͈̔͂��`
	XMFLOAT3 minPoint(center.x - hw.x / 2, center.y, center.z - hw.y / 2);
	XMFLOAT3 maxPoint(center.x + hw.x / 2, center.y, center.z + hw.y / 2);

	// �����̊e�_���͈͓����`�F�b�N
	auto isPointInRange = [&](const XMFLOAT3& p)
	{
		return (p.x >= minPoint.x && p.x <= maxPoint.x &&
			p.y >= minPoint.y && p.y <= maxPoint.y &&
			p.z >= minPoint.z && p.z <= maxPoint.z);
	};

	// �����̓_���͈͓��ɂ��邩���m�F
	if (isPointInRange(lp1) || isPointInRange(lp2))
	{
		return TRUE;
	}

	return FALSE;
}




BOOL CollisionSphereSphere(XMFLOAT3 center1, float r1, XMFLOAT3 center2, float r2)
{
	BOOL ans = FALSE;
	XMVECTOR p1 = XMLoadFloat3(&center1);
	XMVECTOR p2 = XMLoadFloat3(&center2);

	XMVECTOR dist = p1 - p2;

	float len;

	XMStoreFloat(&len, XMVector3Length(dist));

	if (len<r1+r2)
	{
		ans = TRUE;
	}

	return ans;
}

BOOL CollisionSphereCapsule(XMFLOAT3 center1, float r1, XMFLOAT3 cp1, XMFLOAT3 cp2, float r2)
{
	BOOL ans = FALSE;

	XMVECTOR p = XMLoadFloat3(&center1);

	XMVECTOR p1 = XMLoadFloat3(&cp1);
	XMVECTOR p2 = XMLoadFloat3(&cp2);

	XMVECTOR p1c = p - p1;
	XMVECTOR p2c = p - p2;
	float p1l;
	float p2l;
	XMStoreFloat(&p1l, XMVector3Length(p1c));
	XMStoreFloat(&p2l, XMVector3Length(p2c));


	//�����̗��[���܂��͌���
	if (p1l < r1+r2 || p2l < r1+r2)
	{
		return TRUE;
	}

	XMVECTOR lv = XMVector3LinePointDistance(p1, p2, p);
	float length;
	XMStoreFloat(&length, lv);
	if (length < r1+r2)
	{
		return TRUE;
	}

	return ans;
}

BOOL CollisionSphereBox(XMFLOAT3 center1, float r1, XMFLOAT3 center, XMFLOAT3 size)
{
	// �{�b�N�X�͈̔͂��`
	XMFLOAT3 boxMin(center.x - size.x / 2, center.y - size.y / 2, center.z - size.z / 2);
	XMFLOAT3 boxMax(center.x + size.x / 2, center.y + size.y / 2, center.z + size.z / 2);

	// �{�b�N�X���ŋ��̒��S�ɍł��߂��_��������
	XMFLOAT3 closestPoint(
		max(boxMin.x, min(center1.x, boxMax.x)),
		max(boxMin.y, min(center1.y, boxMax.y)),
		max(boxMin.z, min(center1.z, boxMax.z))
	);

	// ���̒��S�ƃ{�b�N�X���ōł��߂��_�̋������v�Z
	XMFLOAT3 direction(center1.x - closestPoint.x, center1.y - closestPoint.y, center1.z - closestPoint.z);
	float distanceSq = direction.x * direction.x + direction.y * direction.y + direction.z * direction.z;

	// ���������̔��a�ȉ��ł���΁A�Փ˂��Ă���
	return distanceSq <= r1 * r1 ? TRUE : FALSE;
}

BOOL CollisionSphereTerrain(XMFLOAT3 center1, float r1, XMFLOAT3 center, XMFLOAT2 hw)
{
	// �n�`�͈̔͂��`
	XMFLOAT3 minPoint(center.x - hw.x / 2, center.y, center.z - hw.y / 2);
	XMFLOAT3 maxPoint(center.x + hw.x / 2, center.y, center.z + hw.y / 2);

	// �n�`�̊e�ʂɂ��ċ��̒��S�ɍł��߂��_��������
	XMFLOAT3 closestPoint(
		max(minPoint.x, min(center1.x, maxPoint.x)),
		center.y, // �����͕ς��Ȃ��̂�center.y���g�p
		max(minPoint.z, min(center1.z, maxPoint.z))
	);

	// ���̒��S�ƒn�`���ōł��߂��_�̋������v�Z
	XMFLOAT3 direction(center1.x - closestPoint.x, center1.y - closestPoint.y, center1.z - closestPoint.z);
	float distanceSq = direction.x * direction.x + direction.y * direction.y + direction.z * direction.z;

	// ���������̔��a�ȉ��ł���΁A�͈͓��ɂ���
	return distanceSq <= r1 * r1 ? TRUE : FALSE;
}

BOOL CollisionCapsuleCapsule(XMFLOAT3 cp1_1, XMFLOAT3 cp1_2, float r1, XMFLOAT3 cp2_1, XMFLOAT3 cp2_2, float r2)
{
	XMVECTOR p1_1 = XMLoadFloat3(&cp1_1);
	XMVECTOR p1_2 = XMLoadFloat3(&cp1_2);
	XMVECTOR p2_1 = XMLoadFloat3(&cp2_1);
	XMVECTOR p2_2 = XMLoadFloat3(&cp2_2);

	XMVECTOR d1 = XMVectorSubtract(p1_2, p1_1);
	XMVECTOR d2 = XMVectorSubtract(p2_2, p2_1);

	float t1, t2;
	XMVECTOR c1, c2;

	// �ŋߐړ_�����߂�
	ClosestPtSegmentSegment(p1_1, d1, p2_1, d2, t1, t2, c1, c2);

	// �J�v�Z���̔��a���l�����ďՓ˔���
	XMVECTOR distVec = XMVectorSubtract(c1, c2);
	float distSq = XMVectorGetX(XMVector3LengthSq(distVec));
	float radiusSum = r1 + r2;

	return distSq <= (radiusSum * radiusSum);
}

BOOL CollisionCapsuleBox(XMFLOAT3 cp1_1, XMFLOAT3 cp1_2, float r1, XMFLOAT3 center, XMFLOAT3 size)
{
	XMFLOAT3 boxMin(center.x - size.x / 2, center.y - size.y / 2, center.z - size.z / 2);
	XMFLOAT3 boxMax(center.x + size.x / 2, center.y + size.y / 2, center.z + size.z / 2);

	auto squaredDistancePointAABB = [](const XMFLOAT3& p, const XMFLOAT3& bMin, const XMFLOAT3& bMax)
	{
		float sqDist = 0.0f;
		if (p.x < bMin.x) sqDist += (bMin.x - p.x) * (bMin.x - p.x);
		if (p.x > bMax.x) sqDist += (p.x - bMax.x) * (p.x - bMax.x);
		if (p.y < bMin.y) sqDist += (bMin.y - p.y) * (bMin.y - p.y);
		if (p.y > bMax.y) sqDist += (p.y - bMax.y) * (p.y - bMax.y);
		if (p.z < bMin.z) sqDist += (bMin.z - p.z) * (bMin.z - p.z);
		if (p.z > bMax.z) sqDist += (p.z - bMax.z) * (p.z - bMax.z);
		return sqDist;
	};

	if (squaredDistancePointAABB(cp1_1, boxMin, boxMax) <= r1 * r1 ||
		squaredDistancePointAABB(cp1_2, boxMin, boxMax) <= r1 * r1)
		return TRUE;

	XMFLOAT3 d(cp1_2.x - cp1_1.x, cp1_2.y - cp1_1.y, cp1_2.z - cp1_1.z);
	float lengthSq = d.x * d.x + d.y * d.y + d.z * d.z;
	XMFLOAT3 closestPt = cp1_1;

	auto segmentClosestPtToPoint = [&](const XMFLOAT3& p, XMFLOAT3& closest)
	{
		XMFLOAT3 pToCp1(p.x - cp1_1.x, p.y - cp1_1.y, p.z - cp1_1.z);
		float t = (pToCp1.x * d.x + pToCp1.y * d.y + pToCp1.z * d.z) / lengthSq;
		t = max(0.0f, min(1.0f, t));
		closest.x = cp1_1.x + t * d.x;
		closest.y = cp1_1.y + t * d.y;
		closest.z = cp1_1.z + t * d.z;
	};

	segmentClosestPtToPoint(center, closestPt);

	if (squaredDistancePointAABB(closestPt, boxMin, boxMax) <= r1 * r1)
		return TRUE;

	return FALSE;
}

BOOL CollisionCapsuleTerrain(XMFLOAT3 cp1_1, XMFLOAT3 cp1_2, float r1, XMFLOAT3 center, XMFLOAT2 hw)
{
	// �n�`�͈̔͂��` (xz���ʂ̂�)
	XMFLOAT2 minPoint(center.x - hw.x / 2, center.z - hw.y / 2);
	XMFLOAT2 maxPoint(center.x + hw.x / 2, center.z + hw.y / 2);

	auto squaredDistancePointAABB2D = [](const XMFLOAT2& p, const XMFLOAT2& bMin, const XMFLOAT2& bMax)
	{
		float sqDist = 0.0f;
		if (p.x < bMin.x) sqDist += (bMin.x - p.x) * (bMin.x - p.x);
		if (p.x > bMax.x) sqDist += (p.x - bMax.x) * (p.x - bMax.x);
		if (p.y < bMin.y) sqDist += (bMin.y - p.y) * (bMin.y - p.y);
		if (p.y > bMax.y) sqDist += (p.y - bMax.y) * (p.y - bMax.y);
		return sqDist;
	};

	// �J�v�Z���̗��[���n�`�͈͓̔����`�F�b�N
	XMFLOAT2 cp1_1_2D(cp1_1.x, cp1_1.z);
	XMFLOAT2 cp1_2_2D(cp1_2.x, cp1_2.z);
	if (squaredDistancePointAABB2D(cp1_1_2D, minPoint, maxPoint) <= r1 * r1 ||
		squaredDistancePointAABB2D(cp1_2_2D, minPoint, maxPoint) <= r1 * r1)
	{
		return TRUE;
	}

	// �J�v�Z���̐����̊e�_���n�`�͈͓̔����`�F�b�N
	XMFLOAT2 d(cp1_2_2D.x - cp1_1_2D.x, cp1_2_2D.y - cp1_1_2D.y);
	float lengthSq = d.x * d.x + d.y * d.y;
	XMFLOAT2 closestPt = cp1_1_2D;

	auto segmentClosestPtToPoint2D = [&](const XMFLOAT2& p, XMFLOAT2& closest)
	{
		XMFLOAT2 pToCp1(p.x - cp1_1_2D.x, p.y - cp1_1_2D.y);
		float t = (pToCp1.x * d.x + pToCp1.y * d.y) / lengthSq;
		t = max(0.0f, min(1.0f, t));
		closest.x = cp1_1_2D.x + t * d.x;
		closest.y = cp1_1_2D.y + t * d.y;
	};

	segmentClosestPtToPoint2D(XMFLOAT2(center.x, center.z), closestPt);

	if (squaredDistancePointAABB2D(closestPt, minPoint, maxPoint) <= r1 * r1)
		return TRUE;

	return FALSE;
}

BOOL CollisionBoxBox(XMFLOAT3 center1, XMFLOAT3 size1, XMFLOAT3 center2, XMFLOAT3 size2)
{
	// �{�b�N�X1�̍ŏ�����эő���W���v�Z
	XMFLOAT3 min1 = XMFLOAT3(center1.x - size1.x / 2.0f, center1.y - size1.y / 2.0f, center1.z - size1.z / 2.0f);
	XMFLOAT3 max1 = XMFLOAT3(center1.x + size1.x / 2.0f, center1.y + size1.y / 2.0f, center1.z + size1.z / 2.0f);

	// �{�b�N�X2�̍ŏ�����эő���W���v�Z
	XMFLOAT3 min2 = XMFLOAT3(center2.x - size2.x / 2.0f, center2.y - size2.y / 2.0f, center2.z - size2.z / 2.0f);
	XMFLOAT3 max2 = XMFLOAT3(center2.x + size2.x / 2.0f, center2.y + size2.y / 2.0f, center2.z + size2.z / 2.0f);

	// �e���ɑ΂��ďd�Ȃ���`�F�b�N
	if (min1.x > max2.x || max1.x < min2.x) return FALSE;
	if (min1.y > max2.y || max1.y < min2.y) return FALSE;
	if (min1.z > max2.z || max1.z < min2.z) return FALSE;

	return TRUE; // �{�b�N�X���d�Ȃ��Ă���ꍇ
}


BOOL CollisionBoxTerrain(XMFLOAT3 center1, XMFLOAT3 size1, XMFLOAT3 center, XMFLOAT2 hw)
{
	// �n�`�͈̔͂��` (xz���ʂ̂�)
	XMFLOAT2 minPoint(center.x - hw.x / 2, center.z - hw.y / 2);
	XMFLOAT2 maxPoint(center.x + hw.x / 2, center.z + hw.y / 2);

	// �{�b�N�X�͈̔͂��` (xz���ʂ̂�)
	XMFLOAT2 boxMin(center1.x - size1.x / 2, center1.z - size1.z / 2);
	XMFLOAT2 boxMax(center1.x + size1.x / 2, center1.z + size1.z / 2);

	// �{�b�N�X�ƒn�`�͈̔͂��������邩���`�F�b�N
	if (boxMin.x <= maxPoint.x && boxMax.x >= minPoint.x &&
		boxMin.y <= maxPoint.y && boxMax.y >= minPoint.y)
	{
		return TRUE;
	}

	return FALSE;
}

void ClosestPtSegmentSegment(XMVECTOR p1, XMVECTOR d1, XMVECTOR p2, XMVECTOR d2, float& t1, float& t2, XMVECTOR& c1, XMVECTOR& c2)
{
	XMVECTOR r = XMVectorSubtract(p1, p2);
	float a = XMVectorGetX(XMVector3Dot(d1, d1));
	float e = XMVectorGetX(XMVector3Dot(d2, d2));
	float f = XMVectorGetX(XMVector3Dot(d2, r));

	// �ǂ��炩�̐������_�̏ꍇ
	if (a <= FLT_EPSILON && e <= FLT_EPSILON)
	{
		t1 = t2 = 0.0f;
		c1 = p1;
		c2 = p2;
		return;
	}
	if (a <= FLT_EPSILON)
	{
		t1 = 0.0f;
		t2 = f / e;
		t2 = std::clamp(t2, 0.0f, 1.0f);
	}
	else
	{
		float c = XMVectorGetX(XMVector3Dot(d1, r));
		if (e <= FLT_EPSILON)
		{
			t2 = 0.0f;
			t1 = std::clamp(-c / a, 0.0f, 1.0f);
		}
		else
		{
			float b = XMVectorGetX(XMVector3Dot(d1, d2));
			float denom = a * e - b * b;

			if (denom != 0.0f)
			{
				t1 = std::clamp((b * f - c * e) / denom, 0.0f, 1.0f);
			}
			else
			{
				t1 = 0.0f;
			}

			t2 = (b * t1 + f) / e;

			if (t2 < 0.0f)
			{
				t2 = 0.0f;
				t1 = std::clamp(-c / a, 0.0f, 1.0f);
			}
			else if (t2 > 1.0f)
			{
				t2 = 1.0f;
				t1 = std::clamp((b - c) / a, 0.0f, 1.0f);
			}
		}
	}

	c1 = XMVectorAdd(p1, XMVectorScale(d1, t1));
	c2 = XMVectorAdd(p2, XMVectorScale(d2, t2));
}




