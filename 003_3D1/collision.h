//======================================================================================
//
// �����蔻�菈��[collision.h]
// Author;���}���@�V
//
//======================================================================================
#ifndef _COLLISION_H_
#define _COLLISION_H_

#include "main.h"

//�v���g�^�C�v�錾
bool CollisionCircle(D3DXVECTOR3 *pPos1, D3DXVECTOR3 *pPos2, float fLength1, float fLength2);
bool CollisionAdultWall(D3DXVECTOR3 *pPos, float fWidth);

#endif
