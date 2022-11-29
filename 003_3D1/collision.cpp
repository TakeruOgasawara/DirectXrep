//======================================================================================
//
//�{�X�̏���[Enemy.cpp]
//Author;���}���@�V
//
//======================================================================================
#include "collision.h"

//========================================================================
// �~�̓����蔻��
//========================================================================
bool CollisionCircle(D3DXVECTOR3 *pPos1, D3DXVECTOR3 *pPos2, float fLength1, float fLength2)
{
	float fLength;
	bool bUse = false;

	//�G�ƃv���C���[�Ԃ̑Ίp���̒������Z�o����
	fLength = sqrtf((pPos1->x - pPos2->x) * (pPos1->x - pPos2->x) +
					(pPos1->y - pPos2->y) * (pPos1->y - pPos2->y));
	
	if (fLength <= (fLength1 / 2) + (fLength1 / 2))
	{
		bUse = true;			//�g�p����
	}

	return bUse;
}

//========================================================================
// ��l�̕Ǐ���
//========================================================================
bool CollisionAdultWall(D3DXVECTOR3 *pPos, float fWidth)
{
	bool bW = false;

	if (pPos->x <= -1000.0f + fWidth)
	{
		pPos->x = -1000.0f + fWidth;
		bW = true;
	}
	if (pPos->x >= 1000.0f - fWidth)
	{
		pPos->x = 1000.0f - fWidth;
		bW = true;
	}
	if (pPos->z <= -1000.0f + fWidth)
	{
		pPos->z = -1000.0f + fWidth;
		bW = true;
	}
	if (pPos->z >= 1000.0f - fWidth)
	{
		pPos->z = 1000.0f - fWidth;
		bW = true;
	}

	return bW;
}
