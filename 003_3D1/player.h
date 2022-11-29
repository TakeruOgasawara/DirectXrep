//====================================================================
//
// ���f���̏���[model.h]
// Author: ���}���V
//
//====================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"

//�v���C���[�\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;			//�ʒu
	D3DXVECTOR3 rot;			//����
	D3DXMATRIX mtxWorld;		//���[���h�}�g���b�N�X
	D3DXVECTOR3 move;			//�ړ���
	int nIdxShadow;			//�Ώۂ̉e�̃C���f�b�N�X(�ԍ�)
	bool bUse;					//�g���Ă��邩
} Player;

//�v���g�^�C�v�錾
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);

void DrawModelPos(void);

Player *GetPlayer(void);

#endif