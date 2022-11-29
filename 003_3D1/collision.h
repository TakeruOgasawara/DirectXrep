//======================================================================================
//
// 当たり判定処理[collision.h]
// Author;小笠原　彪
//
//======================================================================================
#ifndef _COLLISION_H_
#define _COLLISION_H_

#include "main.h"

//プロトタイプ宣言
bool CollisionCircle(D3DXVECTOR3 *pPos1, D3DXVECTOR3 *pPos2, float fLength1, float fLength2);
bool CollisionAdultWall(D3DXVECTOR3 *pPos, float fWidth);

#endif
