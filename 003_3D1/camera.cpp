//======================================================================================
//
// �J�����̏���[camera.cpp]
// Author;���}���@�V
//
//======================================================================================
#include <stdio.h>
#include "camera.h"
#include "input.h"
#include "player.h"

//�}�N����`
#define CAMERA_SPEED		(0.9f)			//�J�����̑��x
#define CAMERA_DISTANCE		(200.0f)		//���_�ƒ����_�̋���
#define CAMELA_AUTO			(0.0001f)		//�J���������ɉ�鎞�̊���

//�v���g�^�C�v�錾
void CameraOps(void);			//�J��������̏���
void CameraV(void);				//���_����̏���
void CameraR(void);				//�����_����̏���
void Camerafollow(void);		//�J�����Ǐ]�̏���

//�O���[�o���錾
Camera g_camera;			//�J�������

//====================================================================
// �J�����̏���������
//====================================================================
void InitCamera(void)
{
	//�ϐ��̏�����
	g_camera.posV = D3DXVECTOR3(0.0f, 200.0f, -50.0f);			//���_
	g_camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//�����_
	g_camera.vecU = D3DXVECTOR3(0.0, 1.0f, 0.0f);				//������x�N�g��

	g_camera.posVDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//�ړI�̎��_
	g_camera.posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//�ړI�̒����_

	g_camera.rot = D3DXVECTOR3(0.0f, 0.0f, -0.55f);				//����

	g_camera.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//�ړ���

	g_camera.fLengthCamera = 230.0f;			//�����_���王�_�Ԃ̋���
}

//====================================================================
//�J�����̏I����������
//====================================================================
void UninitCamera(void)
{

}

//====================================================================
//�J�����̍X�V����
//====================================================================
void UpdateCamera(void)
{
	//�J�����̑��삪�����Ă�֐�
	CameraOps();
}

//====================================================================
//�J�����̑���
//====================================================================
void CameraOps(void)
{
	Player *pPlayer = GetPlayer();

	//�������ړ�
	//if (GetKeyboardPress(DIK_A) == true)
	//{//A�L�[�������ꂽ
	//	if (GetKeyboardPress(DIK_W) == true)
	//	{//����ړ�
	//		g_camera.posV.x += sinf(g_camera.rot.y + -D3DX_PI * 0.25f) * CAMERA_SPEED;
	//		g_camera.posR.x += sinf(g_camera.rot.y + -D3DX_PI * 0.25f) * CAMERA_SPEED;
	//		g_camera.posV.z += cosf(g_camera.rot.y + -D3DX_PI * 0.25f) * CAMERA_SPEED;
	//		g_camera.posR.z += cosf(g_camera.rot.y + -D3DX_PI * 0.25f) * CAMERA_SPEED;
	//	}
	//	else if (GetKeyboardPress(DIK_S) == true)
	//	{//�����ړ�
	//		g_camera.posV.x += sinf(g_camera.rot.y + -D3DX_PI * 0.75f) * CAMERA_SPEED;
	//		g_camera.posR.x += sinf(g_camera.rot.y + -D3DX_PI * 0.75f) * CAMERA_SPEED;
	//		g_camera.posV.z += cosf(g_camera.rot.y + -D3DX_PI * 0.75f) * CAMERA_SPEED;
	//		g_camera.posR.z += cosf(g_camera.rot.y + -D3DX_PI * 0.75f) * CAMERA_SPEED;
	//	}
	//	else
	//	{//���ړ�
	//		//�J�����ʒu���̍X�V
	//		g_camera.posV.x += sinf(g_camera.rot.y + -D3DX_PI * 0.5f) * CAMERA_SPEED;
	//		g_camera.posR.x += sinf(g_camera.rot.y + -D3DX_PI * 0.5f) * CAMERA_SPEED;
	//		g_camera.posV.z += cosf(g_camera.rot.y + -D3DX_PI * 0.5f) * CAMERA_SPEED;
	//		g_camera.posR.z += cosf(g_camera.rot.y + -D3DX_PI * 0.5f) * CAMERA_SPEED;
	//	}
	//}
	//else if (GetKeyboardPress(DIK_D) == true)
	//{//D�L�[�������ꂽ
	//	if (GetKeyboardPress(DIK_W) == true)
	//	{//�E��ړ�
	//		g_camera.posV.x += sinf(g_camera.rot.y + D3DX_PI * 0.25f) * CAMERA_SPEED;
	//		g_camera.posR.x += sinf(g_camera.rot.y + D3DX_PI * 0.25f) * CAMERA_SPEED;
	//		g_camera.posV.z += cosf(g_camera.rot.y + D3DX_PI * 0.25f) * CAMERA_SPEED;
	//		g_camera.posR.z += cosf(g_camera.rot.y + D3DX_PI * 0.25f) * CAMERA_SPEED;
	//	}
	//	else if (GetKeyboardPress(DIK_S) == true)
	//	{//�E���ړ�
	//		g_camera.posV.x += sinf(g_camera.rot.y + D3DX_PI * 0.75f) * CAMERA_SPEED;
	//		g_camera.posR.x += sinf(g_camera.rot.y + D3DX_PI * 0.75f) * CAMERA_SPEED;
	//		g_camera.posV.z += cosf(g_camera.rot.y + D3DX_PI * 0.75f) * CAMERA_SPEED;
	//		g_camera.posR.z += cosf(g_camera.rot.y + D3DX_PI * 0.75f) * CAMERA_SPEED;
	//	}
	//	else
	//	{//�E�ړ�
	//		//�J�����ʒu���̍X�V
	//		g_camera.posV.x += sinf(g_camera.rot.y + D3DX_PI * 0.5f) * CAMERA_SPEED;
	//		g_camera.posR.x += sinf(g_camera.rot.y + D3DX_PI * 0.5f) * CAMERA_SPEED;
	//		g_camera.posV.z += cosf(g_camera.rot.y + D3DX_PI * 0.5f) * CAMERA_SPEED;
	//		g_camera.posR.z += cosf(g_camera.rot.y + D3DX_PI * 0.5f) * CAMERA_SPEED;
	//	}
	//}
	//else if (GetKeyboardPress(DIK_W) == true)
	//{//W�L�[�������ꂽ
	//	//��ړ�
	//	g_camera.posV.x += sinf(g_camera.rot.y) * CAMERA_SPEED;
	//	g_camera.posR.x += sinf(g_camera.rot.y) * CAMERA_SPEED;
	//	g_camera.posV.z += cosf(g_camera.rot.y) * CAMERA_SPEED;
	//	g_camera.posR.z += cosf(g_camera.rot.y) * CAMERA_SPEED;
	//}
	//else if (GetKeyboardPress(DIK_S) == true)
	//{//S�L�[�������ꂽ
	//	//���ړ�
	//	g_camera.posV.x += sinf(g_camera.rot.y + D3DX_PI) * CAMERA_SPEED;
	//	g_camera.posR.x += sinf(g_camera.rot.y + D3DX_PI) * CAMERA_SPEED;
	//	g_camera.posV.z += cosf(g_camera.rot.y + D3DX_PI) * CAMERA_SPEED;
	//	g_camera.posR.z += cosf(g_camera.rot.y + D3DX_PI) * CAMERA_SPEED;
	//}

	//�J�����̒Ǐ]
	Camerafollow();

	//���_����
	CameraV();

	//�����_�ړ�
	CameraR();

	//if (pPlayer->move.x <= CAMELA_AUTO && pPlayer->move.y <= CAMELA_AUTO && pPlayer->move.z <= CAMELA_AUTO &&
	//	pPlayer->move.x >= -CAMELA_AUTO && pPlayer->move.y >= -CAMELA_AUTO && pPlayer->move.z >= -CAMELA_AUTO)
	//{//�J������w��ɉ񂷏���
	//	CameraAuto();
	//}
	
	//������3.14�ȏ�-3.14�ȉ��ɍs���Ȃ��悤�ɂ���
	//y
	if (g_camera.rot.y > D3DX_PI)
	{
		g_camera.rot.y = -D3DX_PI;
	}
	if (g_camera.rot.y < -D3DX_PI)
	{
		g_camera.rot.y = D3DX_PI;
	}
	//z
	if (g_camera.rot.z > D3DX_PI)
	{
		g_camera.rot.z = -D3DX_PI;
	}
	if (g_camera.rot.z < -D3DX_PI)
	{
		g_camera.rot.z = D3DX_PI;
	}
	//x
	if (g_camera.rot.x > D3DX_PI)
	{
		g_camera.rot.x = -D3DX_PI;
	}
	if (g_camera.rot.x < -D3DX_PI)
	{
		g_camera.rot.x = D3DX_PI;
	}
}

//====================================================================
// �J�������_�̈ړ�����
//====================================================================
void CameraV(void)
{
	//�|�C���^���̎擾
	Player *pPlayer = GetPlayer();

	//�c��]
	if (GetKeyboardPress(DIK_Y) == true)
	{//Y�L�[�������ꂽ
		g_camera.rot.z -= 0.05f;
	}
	else if (GetKeyboardPress(DIK_N) == true)
	{//N�L�[�������ꂽ
		g_camera.rot.z += 0.05f;
	}
	//����]
	if (GetKeyboardPress(DIK_Z) == true)
	{//Z�L�[�������ꂽ
		g_camera.rot.y += 0.05f;
	}
	else if (GetKeyboardPress(DIK_C) == true)
	{//C�L�[�������ꂽ
		g_camera.rot.y -= 0.05f;
	}

	g_camera.posVDest.x = pPlayer->pos.x + (cosf(g_camera.rot.z) * sinf(g_camera.rot.y)) * -g_camera.fLengthCamera;
	g_camera.posVDest.y = pPlayer->pos.y + sinf(g_camera.rot.z) * -g_camera.fLengthCamera;			//���_Y
	g_camera.posVDest.z = pPlayer->pos.z + (cosf(g_camera.rot.z) * cosf(g_camera.rot.y)) * -g_camera.fLengthCamera;
}

//====================================================================
// �J���������_�̈ړ�����
//====================================================================
void CameraR(void)
{
	//�c��]
	if (GetKeyboardPress(DIK_T) == true)
	{//T�L�[�������ꂽ
		g_camera.rot.z += 0.05f;
	}
	else if (GetKeyboardPress(DIK_B) == true)
	{//B�L�[�������ꂽ
		g_camera.rot.z -= 0.05f;
	}
	//����]
	if (GetKeyboardPress(DIK_Q) == true)
	{//Q�L�[�������ꂽ
		g_camera.rot.y -= 0.05f;
	}
	else if (GetKeyboardPress(DIK_E) == true)
	{//E�L�[�������ꂽ
		g_camera.rot.y += 0.05f;
	}

	g_camera.posRDest.x = g_camera.posVDest.x + (cosf(g_camera.rot.z) * sinf(g_camera.rot.y)) * g_camera.fLengthCamera;
	g_camera.posRDest.y = g_camera.posVDest.y + sinf(g_camera.rot.z) * g_camera.fLengthCamera;			//���_Y
	g_camera.posRDest.z = g_camera.posVDest.z + (cosf(g_camera.rot.z) * cosf(g_camera.rot.y)) * g_camera.fLengthCamera;
}

//====================================================================
// �J�����̒Ǐ]����
//====================================================================
void Camerafollow(void)
{
	//�|�C���^���̎擾
	Player *pPlayer = GetPlayer();

	D3DXVECTOR3 posRDiff;
	D3DXVECTOR3 posVDiff;

	//�ړI�̎��_/�����_��ݒ�(�����l)
	g_camera.posRDest = D3DXVECTOR3(pPlayer->pos.x + sinf(pPlayer->rot.y + D3DX_PI) * 20.0f, pPlayer->pos.y, pPlayer->pos.z + cosf(pPlayer->rot.y + D3DX_PI) * 20.0f);				//�����_

	g_camera.posVDest = D3DXVECTOR3(g_camera.posRDest.x + (cosf(g_camera.rot.z) * sinf(g_camera.rot.y)) * -g_camera.fLengthCamera, 
									pPlayer->pos.y + 50.0f, 
									g_camera.posRDest.z + (cosf(g_camera.rot.z) * cosf(g_camera.rot.y)) * -g_camera.fLengthCamera);		//���_

	posRDiff = g_camera.posRDest - g_camera.posR;			//�����_�̍���
	posVDiff = g_camera.posVDest - g_camera.posV;			//���_�̍���

	g_camera.posR += posRDiff * 0.2f;			//�����_��␳����
	
	g_camera.posV += posVDiff * 0.3f;			//���_��␳����
}

//====================================================================
// �J�����̈ʒu�������I�Ɍ�둤��
//====================================================================
void CameraAuto(void)
{
	//�ϐ��錾
	float fRotDiff = 0.0f;			//�����ۑ��p

	//�|�C���^���̎擾
	Player *pPlayer = GetPlayer();

	fRotDiff = (pPlayer->rot.y + D3DX_PI) - g_camera.rot.y;			//�������v�Z

	//�ڕW�̊p�x�̕␳
	if (fRotDiff > D3DX_PI)
	{
		fRotDiff -= 6.28f;
	}
	if (fRotDiff < -D3DX_PI)
	{
		fRotDiff += 6.28f;
	}

	g_camera.rot.y += fRotDiff * 0.045f;			//�␳����

	//�p�x�̕␳
	if (g_camera.rot.y > D3DX_PI)
	{
		g_camera.rot.y -= 6.28f;
	}
	if (g_camera.rot.y < -D3DX_PI)
	{
		g_camera.rot.y += 6.28f;
	}

	//�J�������X�V����
	g_camera.posVDest.x = pPlayer->pos.x + (cosf(g_camera.rot.z) * sinf(g_camera.rot.y)) * -g_camera.fLengthCamera;
	g_camera.posVDest.y = pPlayer->pos.y + sinf(g_camera.rot.z) * -g_camera.fLengthCamera;			//���_Y
	g_camera.posVDest.z = pPlayer->pos.z + (cosf(g_camera.rot.z) * cosf(g_camera.rot.y)) * -g_camera.fLengthCamera;
}

//====================================================================
//�J�����̐ݒ菈������
//====================================================================
void SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾

	//�v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_camera.mtxProjection);

	//�v���W�F�N�V�����}�g���b�N�X���쐬
	D3DXMatrixPerspectiveFovLH(&g_camera.mtxProjection,
		D3DXToRadian(45.0f),							//����p
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,		//��ʂ̃A�X�y�N�g��
		10.0f,											//z�l�̍ŏ��l
		10000.0f);										//z�l�̍ő�l

	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &g_camera.mtxProjection);

	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_camera.mtxView);

	//�r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&g_camera.mtxView,
						&g_camera.posV,				//���_
						&g_camera.posR,				//�����_
						&g_camera.vecU);			//���x�N�g��

	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &g_camera.mtxView);
}

//===================================================
// �J�����ʒu�̕\��
//===================================================
void DrawCameraPos(void)
{
	RECT rect = { 0, 60, SCREEN_WIDTH, SCREEN_HEIGHT };
	char aStr[256];

	Camera PosCamera = GetCamera();
	LPD3DXFONT pFont = GetFont();

	//���������
	sprintf(&aStr[0], "�J�������_:[%0.2f, %0.2f, %0.2f]\n�J���������_:[%0.2f, %0.2f, %0.2f]\n�J�����̌����F[%0.2f, %0.2f, %0.2f]\n���_�ƒ����_�̋���[%0.2f]",
		PosCamera.posV.x, PosCamera.posV.y, PosCamera.posV.z, PosCamera.posR.x, PosCamera.posR.y, PosCamera.posR.z, PosCamera.rot.x, PosCamera.rot.y, PosCamera.rot.z, PosCamera.fLengthCamera);

	//�e�L�X�g�`��
	pFont->DrawTextA(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}

//===================================================
// �J�����̑�������\��
//===================================================
void DrawCameraOps(void)
{
	RECT rect = { 0, 160, SCREEN_WIDTH, SCREEN_HEIGHT };
	char aStr[256];

	Camera PosCamera = GetCamera();
	LPD3DXFONT pFont = GetFont();

	//���������
	wsprintf(&aStr[0], "*�J�����ړ�*\n[W][A][S][D]\n\n*�J�������_����*\n��[Y]��[N]�E[C]��[Z]\n\n*�J���������_�ړ�*\n��[T]��[B]�E[E]��[Q]\n\n�e����");

	//�e�L�X�g�`��
	pFont->DrawTextA(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}

//====================================================================
//�J�����̏��̃|�C���^
//====================================================================
Camera GetCamera(void)
{
	return g_camera;
}