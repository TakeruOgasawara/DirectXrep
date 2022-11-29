//====================================================================
//
// �J�����̏���[camera.h]
// Author: ���}���V
//
//====================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"

//�J�����\���̂̒�`
typedef struct
{
	D3DXVECTOR3 posV;			//���_
	D3DXVECTOR3 posR;			//�����_
	D3DXVECTOR3 posVDest;		//�ړI�̎��_
	D3DXVECTOR3 posRDest;		//�ړI�̒����_
	D3DXVECTOR3 vecU;			//������x�N�g��
	D3DXMATRIX mtxProjection;	//�v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX mtxView;			//�r���[�}�g���b�N�X
	D3DXVECTOR3 move;			//�ړ���
	D3DXVECTOR3 rot;			//����
	float fLengthCamera;		//����
} Camera;

//�v���g�^�C�v�錾
void InitCamera(void);
void UninitCamera(void);
void UpdateCamera(void);

void SetCamera(void);
void CameraAuto(void);			//�J������w�ʂ֊������鏈��

void DrawCameraOps(void);		//�J�����̑������
void DrawCameraPos(void);		//�J�������_�ʒu�̕\��

Camera GetCamera(void);


#endif
