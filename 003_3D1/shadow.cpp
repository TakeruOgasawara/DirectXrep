//======================================================================================
//
// �|���S���̏���[polygon.cpp]
// Author;���}���@�V
//
//======================================================================================
#include "shadow.h"

//�}�N����`
#define TEX_FILENAME		"data\\TEXTURE\\shadow000.jpg"
#define MAX_SHADOW		(128)			//�e�̍ő吔

//�O���[�o����`
LPDIRECT3DTEXTURE9 g_pTextureShadow = NULL;				//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffShadow = NULL;		//���_�o�b�t�@�ւ̃|�C���^

Shadow g_shadow[MAX_SHADOW];

//====================================================================
// �e�̏���������
//====================================================================
void InitShadow(void)
{
	//�ϐ��錾
	int nCntShadow;

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TEX_FILENAME, &g_pTextureShadow);

	//�ϐ��̏�����
	for (nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		g_shadow[nCntShadow].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//�ړ���
		g_shadow[nCntShadow].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//����
		g_shadow[nCntShadow].bUse = false;									//�g���Ă��邩
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_SHADOW,
		D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED,
		&g_pVtxBuffShadow,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-10.0f, 0.0f, 10.0f);
		pVtx[1].pos = D3DXVECTOR3(10.0f, 0.0f, 10.0f);
		pVtx[2].pos = D3DXVECTOR3(-10.0f, 0.0f, -10.0f);
		pVtx[3].pos = D3DXVECTOR3(10.0f, 0.0f, -10.0f);
		//�@���x�N�g���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		//���_�J���[(0.0f�`1.0f���Őݒ�)
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//�e�N�X�`���̍��W�ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffShadow->Unlock();
}

//====================================================================
// �e�̏I������
//====================================================================
void UninitShadow(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureShadow != NULL)
	{
		g_pTextureShadow->Release();
		g_pTextureShadow = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffShadow != NULL)
	{
		g_pVtxBuffShadow->Release();
		g_pVtxBuffShadow = NULL;
	}
}

//====================================================================
// �e�̍X�V����
//====================================================================
void UpdateShadow(void)
{

}

//====================================================================
// �e�̕`�揈��
//====================================================================
void DrawShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X

	//���Z�����̐ݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		if (g_shadow[nCntShadow].bUse == true)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_shadow[nCntShadow].mtxWorld);

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_shadow[nCntShadow].rot.y, g_shadow[nCntShadow].rot.x, g_shadow[nCntShadow].rot.z);
			D3DXMatrixMultiply(&g_shadow[nCntShadow].mtxWorld, &g_shadow[nCntShadow].mtxWorld, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_shadow[nCntShadow].pos.x, g_shadow[nCntShadow].pos.y, g_shadow[nCntShadow].pos.z);
			D3DXMatrixMultiply(&g_shadow[nCntShadow].mtxWorld, &g_shadow[nCntShadow].mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_shadow[nCntShadow].mtxWorld);

			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffShadow, 0,
				sizeof(VERTEX_3D));			//���_���\���̂̃T�C�Y

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureShadow);

			//�|���S���̕`��
  			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,				//�v���~�e�B�u�̎��
				nCntShadow * 4,						//�`�悷��ŏ��̃C���f�b�N�X
				2);
		}
	}

	//�ʏ�̍����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//====================================================================
// �e�̐ݒ菈��
//====================================================================
int SetShadow(float size)
{
	int nCntShadow = -1;

	//���_���ւ̃|�C���^
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_SHADOW; nCnt++)
	{
		if (g_shadow[nCnt].bUse == false)
		{
			nCntShadow = nCnt;

			g_shadow[nCnt].bUse = true;

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(-size, 0.0f, size);
			pVtx[1].pos = D3DXVECTOR3(size, 0.0f, size);
			pVtx[2].pos = D3DXVECTOR3(-size, 0.0f, -size);
			pVtx[3].pos = D3DXVECTOR3(size, 0.0f, -size);

			break;
		}
		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffShadow->Unlock();

	return nCntShadow;
}

//====================================================================
// �e�̈ʒu���ݒ菈��
//====================================================================
void SetPositionShadow(int nIdxShadow, D3DXVECTOR3 pos)
{
	//�w�肵���e�̈ʒu��ݒ�
	g_shadow[nIdxShadow].pos.x = pos.x;
	g_shadow[nIdxShadow].pos.z = pos.z;
}

//====================================================================
// �e������
//====================================================================
void FalseShadow(int nFalseShadow)
{
	if (nFalseShadow > -1)
	{
		g_shadow[nFalseShadow].bUse = false;
	}
}