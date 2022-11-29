//======================================================================================
//
// ���b�V���t�B�[���h�̏���[polygon.cpp]
// Author;���}���@�V
//
//======================================================================================
#include "meshwall.h"

//�}�N����`
#define BG_TEX_FULE		"data\\TEXTURE\\wall000.jpg"			//���w�i�̉摜��ǂݍ���
#define MAX_MESHWALL		(128)			//���b�V���E�H�[���̍ő吔
#define MESHWALL_WIDTH		(1000.0f)		//��
#define MESHWALL_HEIGHT		(100.0f)			//����

//�O���[�o����`
LPDIRECT3DTEXTURE9 g_pTextureMeshWall = NULL;				//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshWall = NULL;			//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshWall = NULL;			//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
MeshWall g_meshWall[MAX_MESHWALL];							//�t�B�[���h���

//====================================================================
// ���b�V���E�H�[���̏���������
//====================================================================
void InitMeshWall(void)
{
	//�ϐ��錾
	int nCnt;

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, BG_TEX_FULE, &g_pTextureMeshWall);

	//�ϐ��̏�����
	for (nCnt = 0; nCnt < MAX_MESHWALL; nCnt++)
	{
		g_meshWall[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_meshWall[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_meshWall[nCnt].bUse = false;
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 14 * MAX_MESHWALL,
		D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED,
		&g_pVtxBuffMeshWall, 
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffMeshWall->Lock(0, 0, (void**)&pVtx, 0);

	for (nCnt = 0; nCnt < MAX_MESHWALL; nCnt++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-MESHWALL_WIDTH, MESHWALL_HEIGHT, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, MESHWALL_HEIGHT, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(MESHWALL_WIDTH, MESHWALL_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(-MESHWALL_WIDTH, MESHWALL_HEIGHT * 0.5f, 0.0f);
		pVtx[4].pos = D3DXVECTOR3(0.0f, MESHWALL_HEIGHT * 0.5f, 0.0f);
		pVtx[5].pos = D3DXVECTOR3(MESHWALL_WIDTH, MESHWALL_HEIGHT * 0.5f, 0.0f);
		pVtx[6].pos = D3DXVECTOR3(-MESHWALL_WIDTH, 0.0f, 0.0f);
		pVtx[7].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[8].pos = D3DXVECTOR3(MESHWALL_WIDTH, 0.0f, 0.0f);
		//�@���x�N�g���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[4].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[5].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[6].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[7].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[8].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		//���_�J���[(0.0f�`1.0f���Őݒ�)
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[5].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[6].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[7].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[8].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//�e�N�X�`���̍��W�ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.5f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[3].tex = D3DXVECTOR2(0.0f, 0.5f);
		pVtx[4].tex = D3DXVECTOR2(0.5f, 0.5f);
		pVtx[5].tex = D3DXVECTOR2(1.0f, 0.5f);
		pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[7].tex = D3DXVECTOR2(0.5f, 1.0f);
		pVtx[8].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 9;			//���_����9�����炷
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffMeshWall->Unlock();

	//�C���f�b�N�X�o�b�t�@�̐���(�ԍ����o���邽�߂̃�����)
	pDevice->CreateIndexBuffer(sizeof(WORD) * 14 * MAX_MESHWALL,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshWall, NULL);

	WORD *pIdx;			//�C���f�b�N�X���ւ̃|�C���^

	//�C���f�b�N�X�o�b�t�@�����b�N���A���_�ԍ��f�[�^�ւ̃|�C���^���擾
	g_pIdxBuffMeshWall->Lock(0, 0, (void**)&pIdx, 0);

	for (nCnt = 0; nCnt < MAX_MESHWALL; nCnt++)
	{
		//���_�ԍ��f�[�^�̐ݒ�
		pIdx[0] = 3;
		pIdx[1] = 0;
		pIdx[2] = 4;
		pIdx[3] = 1;
		pIdx[4] = 5;
		pIdx[5] = 2;
		pIdx[6] = 2;
		pIdx[7] = 6;
		pIdx[8] = 6;
		pIdx[9] = 3;
		pIdx[10] = 7;
		pIdx[11] = 4;
		pIdx[12] = 8;
		pIdx[13] = 5;

		pIdx += 14;			//�C���f�b�N�X�o�b�t�@���f�[�^�����炷
	}

	//�C���f�b�N�X�o�b�t�@���A�����b�N����
	g_pIdxBuffMeshWall->Unlock();

	SetMeshWall(D3DXVECTOR3(0.0f, 0.0f, 1000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetMeshWall(D3DXVECTOR3(0.0f, 0.0f, -1000.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));

	SetMeshWall(D3DXVECTOR3(-1000.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -D3DX_PI * 0.5f, 0.0f));
	SetMeshWall(D3DXVECTOR3(1000.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f));
}

//====================================================================
// ���b�V���E�H�[���̏I������
//====================================================================
void UninitMeshWall(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureMeshWall != NULL)
	{
		g_pTextureMeshWall->Release();
		g_pTextureMeshWall = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffMeshWall != NULL)
	{
		g_pVtxBuffMeshWall->Release();
		g_pVtxBuffMeshWall = NULL;
	}
	//�C���f�b�N�X�o�b�t�@�̔j��
	if (g_pIdxBuffMeshWall != NULL)
	{
		g_pIdxBuffMeshWall->Release();
		g_pIdxBuffMeshWall = NULL;
	}
}

//====================================================================
// ���b�V���E�H�[���̍X�V����
//====================================================================
void UpdateMeshWall(void)
{

}

//====================================================================
// ���b�V���E�H�[���̕`�揈��
//====================================================================
void DrawMeshWall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X
	
	for (int nCnt = 0; nCnt < MAX_MESHWALL; nCnt++)
	{
		if (g_meshWall[nCnt].bUse == true)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_meshWall[nCnt].mtxWorldField);

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_meshWall[nCnt].rot.y, g_meshWall[nCnt].rot.x, g_meshWall[nCnt].rot.z);
			D3DXMatrixMultiply(&g_meshWall[nCnt].mtxWorldField, &g_meshWall[nCnt].mtxWorldField, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_meshWall[nCnt].pos.x, g_meshWall[nCnt].pos.y, g_meshWall[nCnt].pos.z);
			D3DXMatrixMultiply(&g_meshWall[nCnt].mtxWorldField, &g_meshWall[nCnt].mtxWorldField, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_meshWall[nCnt].mtxWorldField);

			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffMeshWall, 0,
				sizeof(VERTEX_3D));			//���_���\���̂̃T�C�Y

			//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetIndices(g_pIdxBuffMeshWall);

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureMeshWall);

			//�|���S���̕`��
			pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0,
				9 * nCnt,			//�p�ӂ������_�̐�
				0,
				12);		//�`�悷��v���~�e�B�u�̐�
		}
	}
}

//====================================================================
// ���b�V���E�H�[���̐ݒ菈��
//====================================================================
void SetMeshWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	for (int nCnt = 0; nCnt < MAX_MESHWALL; nCnt++)
	{
		if (g_meshWall[nCnt].bUse == false)
		{
			g_meshWall[nCnt].pos = pos;
			g_meshWall[nCnt].rot = rot;
			g_meshWall[nCnt].bUse = true;

			break;
		}
	}
}

//====================================================================
// ���b�V���E�H�[���̏��擾
//====================================================================
MeshWall *GetMeshWall(void)
{
	return &g_meshWall[0];
}