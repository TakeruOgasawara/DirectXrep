//====================================================================
//
// ���b�V���V�����_�[�̏���[meshcylindwe.h]
// Author: ���}���V
//
//====================================================================
#ifndef _MESHCYLINDER_H_
#define _MESHCYLINDER_H_

#include "main.h"

//�t�B�[���h�\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;					//�ʒu
	D3DXVECTOR3 rot;					//����
	D3DXMATRIX mtxWorldField;			//���[���h�}�g���b�N�X
	bool bUse;							//�g���Ă��邩
} MeshCylinder;

//�v���g�^�C�v�錾
void InitMeshCylinder(void);
void UninitMeshCylinder(void);
void UpdateMeshCylinder(void);
void DrawMeshCylinder(void);

#endif