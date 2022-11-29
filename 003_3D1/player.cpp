//======================================================================================
//
// �v���C���[�̏���[model.cpp]
// Author;���}���@�V
//
//======================================================================================
#include <stdio.h>
#include "player.h"
#include "input.h"
#include "shadow.h"
#include "camera.h"
#include "bullet.h"
#include "wall.h"
#include "collision.h"
#include "object.h"

//�}�N����`
#define MODEL_SPEED			(1.7f)			//���f���̈ړ����x
#define MODEL_ATT			(0.2f)			//���f���̌���

//�v���g�^�C�v�錾
void PlayerOps(void);
void ColliObj(void);

//�O���[�o���錾
LPDIRECT3DTEXTURE9 g_pTexturePlayer[8] = {};
LPD3DXMESH g_pMeshPlayer = NULL;
LPD3DXBUFFER g_pBuffMatPlayer = NULL;
DWORD g_dwNumMatPlayer = 0;
Player g_player;

int g_nIdxShadow = -1;			//�Ώۂ̉e�̃C���f�b�N�X(�ԍ�)

//====================================================================
// ���f���̏���������
//====================================================================
void InitPlayer(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�O���[�o���錾�̏�����
	g_player.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX("data\\MODEL\\model000.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatPlayer,
		NULL,
		&g_dwNumMatPlayer,
		&g_pMeshPlayer);

	D3DXMATERIAL *pMat;			//�}�e���A���ւ̃|�C���^

	//�}�e���A���ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)g_pBuffMatPlayer->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_dwNumMatPlayer; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{//�t�@�C������e�N�X�`����ǂݍ���
			D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\wood000.png", &g_pTexturePlayer[2]);
			D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\sumi.jpg", &g_pTexturePlayer[3]);
		}
	}

	//�e�̈ʒu��ݒ�
	g_nIdxShadow = SetShadow(10.0f);
}

//====================================================================
// ���f���̏I������
//====================================================================
void UninitPlayer(void)
{
	//���b�V���̔j��
	if (g_pMeshPlayer != NULL)
	{
		g_pMeshPlayer->Release();
		g_pMeshPlayer = NULL;
	}
	//�}�e���A���̔j��
	if (g_pBuffMatPlayer != NULL)
	{
		g_pBuffMatPlayer->Release();
		g_pBuffMatPlayer = NULL;
	}
}

//====================================================================
// ���f���̍X�V����
//====================================================================
void UpdatePlayer(void)
{
	PlayerOps();

	ColliObj();

	//�ړ��ʂ��X�V(����������)
	g_player.move.x += (0.0f - g_player.move.x) * MODEL_ATT;
	g_player.move.y += (0.0f - g_player.move.y) * MODEL_ATT;
	g_player.move.z += (0.0f - g_player.move.z) * MODEL_ATT;

	//�v���C���[�ʒu�̍X�V
	g_player.pos += g_player.move;

	//��l�̕ǂƂ̓����蔻��
	CollisionAdultWall(&g_player.pos, 10.0f);
	
	//�e�̈ʒu��ݒ�
	SetPositionShadow(g_nIdxShadow, g_player.pos);
}

void ColliObj(void)
{
	Object *pObject = GetObj();

	for (int nCnt = 0; nCnt < 1; nCnt++, pObject++)
	{
		//�I�u�W�F�N�g�Ƃ̓����蔻��
		if (pObject->vtxMaxObj.x >= g_player.pos.x && pObject->vtxMinObj.x <= g_player.pos.x &&
			pObject->vtxMaxObj.z >= g_player.pos.z && pObject->vtxMinObj.z <= g_player.pos.z)
		{
			g_player.pos.x = 100.0f;
		}
	}
}

//====================================================================
// �v���C���[�̑���
//====================================================================
void PlayerOps(void)
{
	//�ϐ��錾
	float fRotDest = g_player.rot.y;			//�ڕW�̊p�x
	float fRotDiff = 0.0f;					//�ڕW�ƌ��݂̍���

	Camera camera = GetCamera();

	//�L�[���͂ňړ����鏈��
	if (GetKeyboardPress(DIK_A) == true)
	{//A�L�[�������ꂽ
		if (GetKeyboardPress(DIK_W) == true)
		{
			fRotDest = camera.rot.y + D3DX_PI * 0.75f;

			//����ړ�
			g_player.move.x += sinf(camera.rot.y + -D3DX_PI * 0.25f) * MODEL_SPEED;
			g_player.move.z += cosf(camera.rot.y + -D3DX_PI * 0.25f) * MODEL_SPEED;
		}
		else if (GetKeyboardPress(DIK_S) == true)
		{
			fRotDest = camera.rot.y + D3DX_PI * 0.25f;

			//�����ړ�
			g_player.move.x += sinf(camera.rot.y + -D3DX_PI * 0.75f) * MODEL_SPEED;
			g_player.move.z += cosf(camera.rot.y + -D3DX_PI * 0.75f) * MODEL_SPEED;
		}
		else
		{
			fRotDest = camera.rot.y + D3DX_PI * 0.5f;

			g_player.move.x += sinf(camera.rot.y + -D3DX_PI * 0.5f) * MODEL_SPEED;
			g_player.move.z += cosf(camera.rot.y + -D3DX_PI * 0.5f) * MODEL_SPEED;
		}
	}
	else if (GetKeyboardPress(DIK_D) == true)
	{//D�L�[�������ꂽ
		if (GetKeyboardPress(DIK_W) == true)
		{
			fRotDest = camera.rot.y + -D3DX_PI * 0.75f;

			//�E��ړ�
			g_player.move.x += sinf(camera.rot.y + D3DX_PI * 0.25f) * MODEL_SPEED;
			g_player.move.z += cosf(camera.rot.y + D3DX_PI * 0.25f) * MODEL_SPEED;
		}
		else if (GetKeyboardPress(DIK_S) == true)
		{
			fRotDest = camera.rot.y + -D3DX_PI * 0.25f;

			//�E���ړ�
			g_player.move.x += sinf(camera.rot.y + D3DX_PI * 0.75f) * MODEL_SPEED;
			g_player.move.z += cosf(camera.rot.y + D3DX_PI * 0.75f) * MODEL_SPEED;
		}
		else
		{
			fRotDest = camera.rot.y + -D3DX_PI * 0.5f;

			g_player.move.x += sinf(camera.rot.y + D3DX_PI * 0.5f) * MODEL_SPEED;
			g_player.move.z += cosf(camera.rot.y + D3DX_PI * 0.5f) * MODEL_SPEED;
		}
	}
	else if (GetKeyboardPress(DIK_W) == true)
	{//W�L�[�������ꂽ
		fRotDest = camera.rot.y + -D3DX_PI;

		g_player.move.x += sinf(camera.rot.y + 0.0f) * MODEL_SPEED;
		g_player.move.z += cosf(camera.rot.y + 0.0f) * MODEL_SPEED;
	}
	else if (GetKeyboardPress(DIK_S) == true)
	{//S�L�[�������ꂽ
		fRotDest = camera.rot.y;

		g_player.move.x += sinf(camera.rot.y + D3DX_PI) * MODEL_SPEED;
		g_player.move.z += cosf(camera.rot.y + D3DX_PI) * MODEL_SPEED;
	}

	if (GetKeyboardPress(DIK_LSHIFT) == true)
	{//S�L�[�������ꂽ
		g_player.rot.y += 0.3f;

		g_player.pos.z = g_player.pos.z + (sinf(g_player.rot.y) * sinf(g_player.rot.x));
		g_player.pos.x = g_player.pos.x + (sinf(g_player.rot.y) * cosf(g_player.rot.x));
	}
	if (GetKeyboardPress(DIK_RSHIFT) == true)
	{//S�L�[�������ꂽ
		g_player.rot.y -= 0.3f;

		g_player.pos.z = g_player.pos.z + (sinf(g_player.rot.y) * sinf(g_player.rot.x));
		g_player.pos.x = g_player.pos.x + (sinf(g_player.rot.y) * cosf(g_player.rot.x));
	}

	if (GetKeyboardTrigger(DIK_SPACE) == true)
	{//�e������
		SetBullet(D3DXVECTOR3(g_player.pos.x, g_player.pos.y + 2.0f, g_player.pos.z - 5.0f), D3DXVECTOR3(-sinf(g_player.rot.y), 0.0f, -cosf(g_player.rot.y)), 1000, BULLETTYPE_PLAYER);
	}

	fRotDiff = fRotDest - g_player.rot.y;			//�ڕW�̊p�x�܂ł̍��������߂�

	if (fRotDiff > D3DX_PI)
	{
		fRotDiff -= 6.28f;
	}
	if (fRotDiff < -D3DX_PI)
	{
		fRotDiff += 6.28f;
	}

	g_player.rot.y += fRotDiff * 0.1f;			//�␳����

												//������3.14�ȏ�-3.14�ȉ��ɍs���Ȃ��悤�ɂ���
	if (g_player.rot.y > D3DX_PI)
	{
		g_player.rot.y = -D3DX_PI;
	}
	if (g_player.rot.y < -D3DX_PI)
	{
		g_player.rot.y = D3DX_PI;
	}
}

//====================================================================
// ���f���̕`�揈��
//====================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;						//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;							//�}�e���A���f�[�^�ւ̃|�C���^

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_player.mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_player.rot.y, g_player.rot.x, g_player.rot.z);

	D3DXMatrixMultiply(&g_player.mtxWorld, &g_player.mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_player.pos.x, g_player.pos.y, g_player.pos.z);

	D3DXMatrixMultiply(&g_player.mtxWorld, &g_player.mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_player.mtxWorld);

	//���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	//�}�e���A���ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*) g_pBuffMatPlayer->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_dwNumMatPlayer; nCntMat++)
	{
		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTexturePlayer[nCntMat]);

		//���f��(�p�[�c)�̕`��
		g_pMeshPlayer->DrawSubset(nCntMat);
	}

	//�ۑ�����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

//===================================================
// ���f���ʒu�̕\��
//===================================================
void DrawModelPos(void)
{
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	char aStr[256];

	Player *pPlayer = GetPlayer();
	LPD3DXFONT pFont = GetFont();

	//���������
	sprintf(&aStr[0], "���f���ʒu�F[%0.2f, %0.2f, %0.2f]\n���f���̈ړ��ʁF[%0.4f, %0.4f, %0.4f]", pPlayer->pos.x, pPlayer->pos.y, pPlayer->pos.z, pPlayer->move.x, pPlayer->move.y, pPlayer->move.z);

	//�e�L�X�g�`��
	pFont->DrawTextA(NULL, &aStr[0], -1, &rect, DT_RIGHT, D3DCOLOR_RGBA(255, 255, 255, 255));
}


//====================================================================
// �v���C���[���̎擾
//====================================================================
Player *GetPlayer(void)
{
	return &g_player;
}