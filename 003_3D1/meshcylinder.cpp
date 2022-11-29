//======================================================================================
//
// ���b�V���V�����_�[�̏���[meshcylindwe.h]
// Author;���}���@�V
//
//======================================================================================
#include "meshcylinder.h"

//�}�N����`
#define BG_TEX_FULE		"data\\TEXTURE\\mountain000.png"			//���w�i�̉摜��ǂݍ���
#define MESH_LENGTH		(3000.0f)			//�V�����_�[�̔��a�̒���
#define MESH_HEIGHT		(400.0f)			//�V�����_�[�̍���

//�O���[�o����`
LPDIRECT3DTEXTURE9 g_pTextureMeshCylinder = NULL;				//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshCylinder = NULL;			//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshCylinder = NULL;			//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
MeshCylinder g_meshCylinder;			//�t�B�[���h���

//====================================================================
//�|���S���̏���������
//====================================================================
void InitMeshCylinder(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, BG_TEX_FULE, &g_pTextureMeshCylinder);

	//�ϐ��̏�����
	g_meshCylinder.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_meshCylinder.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 20,
		D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED,
		&g_pVtxBuffMeshCylinder, 
		NULL);
	
	//���_���ւ̃|�C���^
	VERTEX_3D *pVtx;
	
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffMeshCylinder->Lock(0, 0, (void**)&pVtx, 0);
	
	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(cosf(D3DX_PI * 0.0f) * MESH_LENGTH, MESH_HEIGHT, sinf(D3DX_PI * 0.0f) * MESH_LENGTH);
	pVtx[1].pos = D3DXVECTOR3(cosf(D3DX_PI * 0.25f) * MESH_LENGTH, MESH_HEIGHT, sinf(D3DX_PI * 0.25f) * MESH_LENGTH);
	pVtx[2].pos = D3DXVECTOR3(cosf(D3DX_PI * 0.5f) * MESH_LENGTH, MESH_HEIGHT, sinf(D3DX_PI * 0.5f) * MESH_LENGTH);
	pVtx[3].pos = D3DXVECTOR3(cosf(D3DX_PI * 0.75f) * MESH_LENGTH, MESH_HEIGHT, sinf(D3DX_PI * 0.75f) * MESH_LENGTH);
	pVtx[4].pos = D3DXVECTOR3(cosf(D3DX_PI * 1.0f) * MESH_LENGTH, MESH_HEIGHT, sinf(D3DX_PI * 1.0f) * MESH_LENGTH);
	pVtx[5].pos = D3DXVECTOR3(cosf(-D3DX_PI * 0.75f) * MESH_LENGTH, MESH_HEIGHT, sinf(-D3DX_PI * 0.75f) * MESH_LENGTH);
	pVtx[6].pos = D3DXVECTOR3(cosf(-D3DX_PI * 0.5f) * MESH_LENGTH, MESH_HEIGHT, sinf(-D3DX_PI * 0.5f) * MESH_LENGTH);
	pVtx[7].pos = D3DXVECTOR3(cosf(-D3DX_PI * 0.25f) * MESH_LENGTH, MESH_HEIGHT, sinf(-D3DX_PI * 0.25f) * MESH_LENGTH);
	////�d�Ȃ��Ă��鏊(�㑤)
	pVtx[8].pos = D3DXVECTOR3(cosf(D3DX_PI * 0.0f) * MESH_LENGTH, MESH_HEIGHT, sinf(D3DX_PI * 0.0f) * MESH_LENGTH);
	//����
	pVtx[9].pos = D3DXVECTOR3(cosf(D3DX_PI * 0.0f) * MESH_LENGTH, 0.0f, sinf(D3DX_PI * 0.0f) * MESH_LENGTH);
	pVtx[10].pos = D3DXVECTOR3(cosf(D3DX_PI * 0.25f) * MESH_LENGTH, 0.0f, sinf(D3DX_PI * 0.25f) * MESH_LENGTH);
	pVtx[11].pos = D3DXVECTOR3(cosf(D3DX_PI * 0.5f) * MESH_LENGTH, 0.0f, sinf(D3DX_PI * 0.5f) * MESH_LENGTH);
	pVtx[12].pos = D3DXVECTOR3(cosf(D3DX_PI * 0.75f) * MESH_LENGTH, 0.0f, sinf(D3DX_PI * 0.75f) * MESH_LENGTH);
	pVtx[13].pos = D3DXVECTOR3(cosf(D3DX_PI * 1.0f) * MESH_LENGTH, 0.0f, sinf(D3DX_PI * 1.0f) * MESH_LENGTH);
	pVtx[14].pos = D3DXVECTOR3(cosf(-D3DX_PI * 0.75f) * MESH_LENGTH, 0.0f, sinf(-D3DX_PI * 0.75f) * MESH_LENGTH);
	pVtx[15].pos = D3DXVECTOR3(cosf(-D3DX_PI * 0.5f) * MESH_LENGTH, 0.0f, sinf(-D3DX_PI * 0.5f) * MESH_LENGTH);
	pVtx[16].pos = D3DXVECTOR3(cosf(-D3DX_PI * 0.25f) * MESH_LENGTH, 0.0f, sinf(-D3DX_PI * 0.25f) * MESH_LENGTH);
	//�d�Ȃ��Ă��鏊(����)
	pVtx[17].pos = D3DXVECTOR3(cosf(D3DX_PI * 0.0f) * MESH_LENGTH, 0.0f, sinf(D3DX_PI * 0.0f) * MESH_LENGTH);

	for (int nCnt = 0; nCnt < 18; nCnt++)
	{
		//�@���x�N�g���̐ݒ�
		pVtx[nCnt].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//���_�J���[(0.0f�`1.0f���Őݒ�)
		pVtx[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}

	//�e�N�X�`���̍��W�ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.125f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.25f, 0.0f);
	pVtx[3].tex = D3DXVECTOR2(0.375f, 0.0f);
	pVtx[4].tex = D3DXVECTOR2(0.5f, 0.0f);
	pVtx[5].tex = D3DXVECTOR2(0.625f, 0.0f);
	pVtx[6].tex = D3DXVECTOR2(0.75f, 0.0f);
	pVtx[7].tex = D3DXVECTOR2(0.875f, 0.0f);
	pVtx[8].tex = D3DXVECTOR2(1.0f, 0.0f);
	//����
	pVtx[9].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[10].tex = D3DXVECTOR2(0.125f, 1.0f);
	pVtx[11].tex = D3DXVECTOR2(0.25f, 1.0f);
	pVtx[12].tex = D3DXVECTOR2(0.375f, 1.0f);
	pVtx[13].tex = D3DXVECTOR2(0.5f, 1.0f);
	pVtx[14].tex = D3DXVECTOR2(0.625f, 1.0f);
	pVtx[15].tex = D3DXVECTOR2(0.75f, 1.0f);
	pVtx[16].tex = D3DXVECTOR2(0.875f, 1.0f);
	pVtx[17].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffMeshCylinder->Unlock();

	//�C���f�b�N�X�o�b�t�@�̐���(�ԍ����o���邽�߂̃�����)
	pDevice->CreateIndexBuffer(sizeof(WORD) * 20,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshCylinder, NULL);

	WORD *pIdx;			//�C���f�b�N�X���ւ̃|�C���^

	//�C���f�b�N�X�o�b�t�@�����b�N���A���_�ԍ��f�[�^�ւ̃|�C���^���擾
	g_pIdxBuffMeshCylinder->Lock(0, 0, (void**)&pIdx, 0);

	//���_�ԍ��f�[�^�̐ݒ�
	pIdx[0] = 0;
	pIdx[1] = 9;
	pIdx[2] = 1;
	pIdx[3] = 10;

	pIdx[4] = 2;
	pIdx[5] = 11;
	pIdx[6] = 3;
	pIdx[7] = 12;

	pIdx[8] = 4;
	pIdx[9] = 13;
	pIdx[10] = 5;
	pIdx[11] = 14;

	pIdx[12] = 6;
	pIdx[13] = 15;
	pIdx[14] = 7;
	pIdx[15] = 16;

	pIdx[16] = 8;
	pIdx[17] = 17;

	//�C���f�b�N�X�o�b�t�@���A�����b�N����
	g_pIdxBuffMeshCylinder->Unlock();
}

//====================================================================
//�|���S���̏I������
//====================================================================
void UninitMeshCylinder(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureMeshCylinder != NULL)
	{
		g_pTextureMeshCylinder->Release();
		g_pTextureMeshCylinder = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffMeshCylinder != NULL)
	{
		g_pVtxBuffMeshCylinder->Release();
		g_pVtxBuffMeshCylinder = NULL;
	}
	//�C���f�b�N�X�o�b�t�@�̔j��
	if (g_pIdxBuffMeshCylinder != NULL)
	{
		g_pIdxBuffMeshCylinder->Release();
		g_pIdxBuffMeshCylinder = NULL;
	}
}

//====================================================================
//�|���S���̍X�V����
//====================================================================
void UpdateMeshCylinder(void)
{

}

//====================================================================
//�|���S���̕`�揈��
//====================================================================
void DrawMeshCylinder(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X
	
	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_meshCylinder.mtxWorldField);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_meshCylinder.rot.y, g_meshCylinder.rot.x, g_meshCylinder.rot.z);
	D3DXMatrixMultiply(&g_meshCylinder.mtxWorldField, &g_meshCylinder.mtxWorldField, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_meshCylinder.pos.x, g_meshCylinder.pos.y, g_meshCylinder.pos.z);
	D3DXMatrixMultiply(&g_meshCylinder.mtxWorldField, &g_meshCylinder.mtxWorldField, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_meshCylinder.mtxWorldField);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffMeshCylinder, 0,
		sizeof(VERTEX_3D));			//���_���\���̂̃T�C�Y

	//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(g_pIdxBuffMeshCylinder);

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureMeshCylinder);

	//�|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0,
		9,			//�p�ӂ������_�̐�
		0,
		20);		//�`�悷��v���~�e�B�u�̐�
}