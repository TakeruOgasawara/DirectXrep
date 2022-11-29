//====================================================================
//
// ���b�V���E�H�[���̏���[field.h]
// Author: ���}���V
//
//====================================================================
#ifndef _MESHWALL_H_
#define _MESHWALL_H_

#include "main.h"

//�t�B�[���h�\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;					//�ʒu
	D3DXVECTOR3 rot;					//����
	D3DXMATRIX mtxWorldField;			//���[���h�}�g���b�N�X
	bool bUse;							//�g���Ă��邩
} MeshWall;

//�v���g�^�C�v�錾
void InitMeshWall(void);
void UninitMeshWall(void);
void UpdateMeshWall(void);
void DrawMeshWall(void);
void SetMeshWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
MeshWall *GetMeshWall(void);

#endif