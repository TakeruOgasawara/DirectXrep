//====================================================================
//
// �t�B�[���h�̏���[field.h]
// Author: ���}���V
//
//====================================================================
#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_

#include "main.h"

//�t�B�[���h�\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;					//�ʒu
	D3DXVECTOR3 rot;					//����
	D3DXMATRIX mtxWorldField;			//���[���h�}�g���b�N�X
	bool bUse;							//�g���Ă��邩
} MeshField;

//�v���g�^�C�v�錾
void InitMeshField(void);
void UninitMeshField(void);
void UpdateMeshField(void);
void DrawMeshField(void);


#endif