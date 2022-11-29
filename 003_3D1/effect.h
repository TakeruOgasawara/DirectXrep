//======================================================================================
//
//�G�t�F�N�g�̏���[Player.h]
//Author;���}���@�V
//
//======================================================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "main.h"

//�G�t�F�N�g�\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;				//�ʒu
	D3DXVECTOR3 move;
	D3DXVECTOR3 size;
	D3DXMATRIX mtxWorldBullet;	//���[���h�}�g���b�N�X
	D3DXCOLOR col;					//�F
	float fRadius;					//���a(�傫��)
	int nLife;						//����
	bool bUse;						//�g�p���Ă��邩�ǂ���
}Effect;


//�v���g�^�C�v�錾
void InitEffect(void);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);
void SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float fRadius, int nLife);
Effect *GetEffect(void);

#endif