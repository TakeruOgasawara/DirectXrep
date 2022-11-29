//======================================================================================
//
//�e�̏���[Player.cpp]
//Author;���}���@�V
//
//======================================================================================
#include "explosion.h"

//�}�N����`
#define MAX_EXPLOSION			(128)			//�����̍ő吔

#define EXPLOSION_TEX_FILE		"data\\TEXTURE\\explosion.png"		//�摜��ǂݍ���
#define EXPLO_SIZE			(20.0f)					//�����̒��_���W
//�A�j���[�V�����̏���
#define TEX_ANIM			(0.1f)					//�������A�j��1�R�}�̉���(0.0�`1.0)
#define TEX_PA				(9)

//�e�̍\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;				//�ʒu
	D3DXMATRIX mtxWorldBullet;	//���[���h�}�g���b�N�X
	int nCounterAnim;				//�A�j���[�V�����̃J�E���^�[
	int nPatternAnim;				//�A�j���[�V�����p�^�[��No.
	bool bUse;						//�g�p���Ă��邩�ǂ���
} Explosion;

//�O���[�o���錾
LPDIRECT3DTEXTURE9 g_pTextureExplosion = NULL;					//�e�N�X�`���[�ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffExplosion = NULL;				//���_�o�b�t�@�ւ̃|�C���^
Explosion g_aExplosion[MAX_EXPLOSION];							//���j�̏��
int g_nCntExplosion;

//========================================================================
//���j�̏���������
//========================================================================
void InitExplosion(void)
{
	//�ϐ��錾
	int nCntExplosion;

	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`����ǂݍ���
	D3DXCreateTextureFromFile(pDevice, EXPLOSION_TEX_FILE, &g_pTextureExplosion);

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		//�\���̂̏�����
		g_aExplosion[nCntExplosion].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aExplosion[nCntExplosion].nCounterAnim = 0;
		g_aExplosion[nCntExplosion].nPatternAnim = 0;
		g_aExplosion[nCntExplosion].bUse = false;						//�g�p���Ă��Ȃ���Ԃɂ���
	}

	//�����J�E���g�̏�����
	g_nCntExplosion = 0;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_EXPLOSION, //���d�v
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffExplosion,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-EXPLO_SIZE, EXPLO_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(EXPLO_SIZE, EXPLO_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-EXPLO_SIZE, -EXPLO_SIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(EXPLO_SIZE, -EXPLO_SIZE, 0.0f);
		//�@���x�N�g���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		//���_�J���[(0.0f�`1.0f���Őݒ�)
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//�e�N�X�`���̍��W�ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.125f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.125f, 1.0f);

		pVtx += 4;			//���_�f�[�^�̃|�C���^��4���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffExplosion->Unlock();
}
//========================================================================
//�I������
//========================================================================
void UninitExplosion(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureExplosion != NULL)
	{
		g_pTextureExplosion->Release();
		g_pTextureExplosion = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffExplosion != NULL)
	{
		g_pVtxBuffExplosion->Release();
		g_pVtxBuffExplosion = NULL;
	}

}
//========================================================================
//�����̍X�V����
//========================================================================
void UpdateExplosion(void)
{
	//���_���ւ̃|�C���^
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

 	for (int nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == true)
		{//�������g�p����Ă���
			//�J�E���^��i�߂āA�p�^�[��No.���X�V����
			g_aExplosion[nCntExplosion].nCounterAnim++;

			if ((g_aExplosion[nCntExplosion].nCounterAnim % TEX_PA) == 0)
			{
				g_aExplosion[nCntExplosion].nPatternAnim++;

				//�e�N�X�`�����W�̍X�V
				pVtx[0].tex = D3DXVECTOR2(g_aExplosion[nCntExplosion].nPatternAnim  * TEX_ANIM, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(g_aExplosion[nCntExplosion].nPatternAnim * TEX_ANIM + TEX_ANIM, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(g_aExplosion[nCntExplosion].nPatternAnim * TEX_ANIM, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(g_aExplosion[nCntExplosion].nPatternAnim * TEX_ANIM + TEX_ANIM, 1.0f);
			}
		}

		if (g_aExplosion[nCntExplosion].nPatternAnim >= TEX_PA)
		{
			g_aExplosion[nCntExplosion].bUse = false;
		}
		pVtx += 4;			//���_�f�[�^�̃|�C���^��4���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffExplosion->Unlock();
}
//========================================================================
//�����̕`�揈��
//========================================================================
void DrawExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾
	D3DXMATRIX mtxTrans;						//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxView;							//�r���[�}�g���b�N�X�̎擾�p

	//�A���t�@�e�X�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);			//�A���t�@�e�X�g�̗L��/�����̐ݒ�
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);		//��r���@
	pDevice->SetRenderState(D3DRS_ALPHAREF, 10);					//��l

	//z�e�X�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);		//��r���@
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);			//z�o�b�t�@�X�V�̗L�������ݒ�

	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);			//�A���t�@�e�X�g�̗L��/�����̐ݒ�

	for (int nCntExp = 0; nCntExp < MAX_EXPLOSION; nCntExp++)
	{
		if (g_aExplosion[nCntExp].bUse == true)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aExplosion[nCntExp].mtxWorldBullet);

			//�r���[�}�g���b�N�X���擾
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//�|���S�����J�����ɑ΂��Đ��ʂɌ�����
			D3DXMatrixInverse(&g_aExplosion[nCntExp].mtxWorldBullet, NULL, &mtxView);

			g_aExplosion[nCntExp].mtxWorldBullet._41 = 0.0f;
			g_aExplosion[nCntExp].mtxWorldBullet._42 = 0.0f;
			g_aExplosion[nCntExp].mtxWorldBullet._43 = 0.0f;

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aExplosion[nCntExp].pos.x, g_aExplosion[nCntExp].pos.y, g_aExplosion[nCntExp].pos.z);
			D3DXMatrixMultiply(&g_aExplosion[nCntExp].mtxWorldBullet, &g_aExplosion[nCntExp].mtxWorldBullet, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aExplosion[nCntExp].mtxWorldBullet);

			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffExplosion,
				0, sizeof(VERTEX_3D));			//���_���\���̂̃T�C�Y

												//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureExplosion);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,				//�v���~�e�B�u�̎��
				nCntExp * 4,						//�`�悷��ŏ��̃C���f�b�N�X
				2);						//�v���~�e�B�u(�|���S��)��
		}
	}

	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);			//�A���t�@�e�X�g�̗L��/�����̐ݒ�

	//z�o�b�t�@��L���ɂ���
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);			//z�o�b�t�@�X�V�̗L�������ݒ�

	//�A���t�@�e�X�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);			//�A���t�@�e�X�g�̗L��/�����̐ݒ�
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);		//��r���@
	pDevice->SetRenderState(D3DRS_ALPHAREF, 10);					//��l
}
//========================================================================
//�����̒��_���̐ݒ�
//========================================================================
void SetExplosion(D3DXVECTOR3 pos)
{
	//�ϐ��錾
	int nCntExplosion;

	//���_���ւ̃|�C���^
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == false)
		{//�������g�p����Ă��Ȃ�
			g_aExplosion[nCntExplosion].pos = pos;
			g_aExplosion[nCntExplosion].nCounterAnim = 0;
			g_aExplosion[nCntExplosion].nPatternAnim = 0;

			//�e�N�X�`�����W�̍X�V
			pVtx[0].tex = D3DXVECTOR2(g_aExplosion[nCntExplosion].nPatternAnim * TEX_ANIM, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(g_aExplosion[nCntExplosion].nPatternAnim * TEX_ANIM + TEX_ANIM, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(g_aExplosion[nCntExplosion].nPatternAnim * TEX_ANIM, 0.0f);
			pVtx[3].tex = D3DXVECTOR2(g_aExplosion[nCntExplosion].nPatternAnim * TEX_ANIM + TEX_ANIM, 0.0f);

			g_aExplosion[nCntExplosion].bUse = true;				//�g�p���Ă����Ԃɂ���

			break;
		}
		pVtx += 4;			//���_�f�[�^�̃|�C���^��4���i�߂�
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffExplosion->Unlock();
}

//========================================================================
//�������̎擾
//========================================================================
int ExplosionCnt(void)
{
	return g_nCntExplosion;
}
