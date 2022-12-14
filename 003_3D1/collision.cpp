//======================================================================================
//
//ボスの処理[Enemy.cpp]
//Author;小笠原　彪
//
//======================================================================================
#include "collision.h"

//========================================================================
// 円の当たり判定
//========================================================================
bool CollisionCircle(D3DXVECTOR3 *pPos1, D3DXVECTOR3 *pPos2, float fLength1, float fLength2)
{
	float fLength;
	bool bUse = false;

	//敵とプレイヤー間の対角線の長さを算出する
	fLength = sqrtf((pPos1->x - pPos2->x) * (pPos1->x - pPos2->x) +
					(pPos1->y - pPos2->y) * (pPos1->y - pPos2->y));
	
	if (fLength <= (fLength1 / 2) + (fLength1 / 2))
	{
		bUse = true;			//使用する
	}

	return bUse;
}

//========================================================================
// 大人の壁処理
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
