//======================================================================================
//
//ƒ{ƒX‚Ìˆ—[Enemy.cpp]
//Author;¬Š}Œ´@•V
//
//======================================================================================
#include "collision.h"

//========================================================================
// ‰~‚Ì“–‚½‚è”»’è
//========================================================================
bool CollisionCircle(D3DXVECTOR3 *pPos1, D3DXVECTOR3 *pPos2, float fLength1, float fLength2)
{
	float fLength;
	bool bUse = false;

	//“G‚ÆƒvƒŒƒCƒ„[ŠÔ‚Ì‘ÎŠpü‚Ì’·‚³‚ðŽZo‚·‚é
	fLength = sqrtf((pPos1->x - pPos2->x) * (pPos1->x - pPos2->x) +
					(pPos1->y - pPos2->y) * (pPos1->y - pPos2->y));
	
	if (fLength <= (fLength1 / 2) + (fLength1 / 2))
	{
		bUse = true;			//Žg—p‚·‚é
	}

	return bUse;
}

//========================================================================
// ‘ål‚Ì•Çˆ—
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
