//====================================================================
//
// �|���S���̏���[polygon.h]
// Author: ���}���V
//
//====================================================================
#ifndef _WALL_H_
#define _WALL_H_

#include "main.h"

//�Ǎ\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;					//�ʒu
	D3DXVECTOR3 rot;					//����
	D3DXMATRIX mtxWorldWall;			//���[���h�}�g���b�N�X
	bool bUse;							//�g���Ă��邩
} Wall;

//�v���g�^�C�v�錾
void InitWall(void);
void UninitWall(void);
void UpdateWall(void);
void DrawWall(void);
void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

#endif