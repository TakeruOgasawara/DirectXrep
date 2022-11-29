//====================================================================
//
// �|���S���̏���[polygon.h]
// Author: ���}���V
//
//====================================================================
#ifndef _SHADOW_H_
#define _SHADOW_H_

#include "main.h"

//�e�\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;					//�ʒu
	D3DXVECTOR3 rot;					//����
	D3DXMATRIX mtxWorld;				//���[���h�}�g���b�N�X
	bool bUse;							//�g���Ă��邩
} Shadow;


//�v���g�^�C�v�錾
void InitShadow(void);
void UninitShadow(void);
void UpdateShadow(void);
void DrawShadow(void);

int SetShadow(float  size);
void SetPositionShadow(int nIdxShadow, D3DXVECTOR3 pos);
void FalseShadow(int nFalseShadow);

#endif