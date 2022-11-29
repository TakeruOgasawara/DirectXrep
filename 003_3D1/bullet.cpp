//======================================================================================
//
//�e�̏���[Player.cpp]
//Author;���}���@�V
//
//======================================================================================
#include "bullet.h"
#include "effect.h"
#include "shadow.h"
#include "explosion.h"
#include "collision.h"
#include "meshwall.h"
#include "object.h"

//�}�N����`
#define MAX_BULLET			(128)			//�e�̍ő吔
#define NUM_BULLET			(1)				//�e�̎�ސ�
//�摜�̃t�@�C����
#define BULLET_TEX_FILE		"data\\TEXTURE\\bullet000.png"

#define BULLET_SIZE			(2.0f)			//�T�C�Y
#define BULLET_LIFE			(30000)			//�e�̗̑�
#define BULLET_SPEED		(3.5f)			//�e�̃X�s�[�h

//�O���[�o���錾
LPDIRECT3DTEXTURE9 g_pTextureBullet[NUM_BULLET] = {};					//�e�N�X�`���\�ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;			//���_�o�b�t�@�ւ̃|�C���^
Bullet g_aBullet[MAX_BULLET];								//�e�̏��
int g_nBulletCnt;				//�e�̕\������Ă��鐔���J�E���g
float g_fLengthBullet;			// �e�̑Ίp���̒���
float g_fAngleBullet;			// �e�̑Ίp���̊p�x
D3DXVECTOR3 g_vecToPos;
D3DXVECTOR3 g_vecLine;

//========================================================================
//�e�̏���������
//========================================================================
void InitBullet(void)
{//�ϐ��錾
	int nCntBullet;

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�e���̎擾
	Bullet *pBullet = GetBullet();

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++, pBullet++)
	{
		//�\���̂̏�����
		pBullet->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pBullet->move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pBullet->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pBullet->nLife = BULLET_LIFE;
		pBullet->nIdxShadow = -1;
		pBullet->bUse = false;				//�g�p���Ă��Ȃ���Ԃɂ���
	}
	g_vecToPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_vecLine = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, BULLET_TEX_FILE, &g_pTextureBullet[0]);

	//�Ίp���̒������Z�o����
	g_fLengthBullet = sqrtf(BULLET_SIZEX * BULLET_SIZEX + BULLET_SIZEY * BULLET_SIZEY) * 0.5f;

	//�Ίp���̊p�x���Z�o����
	g_fAngleBullet = atan2f(BULLET_SIZEX, BULLET_SIZEY);

	//�e�J�E���g��������
	g_nBulletCnt = 0;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_BULLET,
		D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL);

		//���_���ւ̃|�C���^
		VERTEX_3D *pVtx;

		//���_�o�b�t�@�����b�N
		g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

		for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
		{
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(-BULLET_SIZE, BULLET_SIZE, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(BULLET_SIZE, BULLET_SIZE, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-BULLET_SIZE, -BULLET_SIZE, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(BULLET_SIZE, -BULLET_SIZE, 0.0f);
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
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			pVtx += 4;			//���_�f�[�^�̃|�C���^��4���i�߂�
		}
		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffBullet->Unlock();
}

//========================================================================
//�e�̏I������
//========================================================================
void UninitBullet(void)
{
	//�ϐ��錾
	int nCntTex;			//�e�N�X�`���\�̃J�E���g

	for (nCntTex = 0; nCntTex < NUM_BULLET; nCntTex++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureBullet[nCntTex] != NULL)
		{
			g_pTextureBullet[nCntTex]->Release();
			g_pTextureBullet[nCntTex] = NULL;
		}
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}
}

//========================================================================
//�e�̍X�V����
//========================================================================
void UpdateBullet(void)
{
	//���_���ւ̃|�C���^
	VERTEX_3D *pVtx;

	//�ϐ��錾
	int nCntBullet;
	float vec;

	//�|�C���^���̎擾
	Bullet *pBullet = GetBullet();
	MeshWall *pMeshWall = GetMeshWall();
	Object *pObject = GetObj();

	//���_�o�b�t�@�����b�N
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	//�S�Ă̒e���`�F�b�N
	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++, pBullet++)
	{
		if (pBullet->bUse == true)
		{//�e���g�p����Ă���
			//�e�̈ʒu�̍X�V
			pBullet->pos += pBullet->move;
			//�G�t�F�N�g�̐ݒ�
			SetEffect(pBullet->pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 5.0f, 100);

			//�����̃J�E���g�_�E��
 			pBullet->nLife--;

			if (pBullet->nLife <= 0)
			{//�������I�������
				//�g�p���Ă��Ȃ���Ԃɂ���
				pBullet->bUse = false;
				FalseShadow(pBullet->nIdxShadow);			//�e������
				SetExplosion(pBullet->pos);
			}

			//��l�̕ǂƒe�̓����蔻��
			if (CollisionAdultWall(&pBullet->pos, 0.0f) == true)
			{
				pBullet->bUse = false;
				FalseShadow(pBullet->nIdxShadow);			//�e������
				SetExplosion(pBullet->pos);
			}

			//�I�u�W�F�N�g�Ƃ̓����蔻��
			if (pObject->vtxMaxObj.x >= pBullet->pos.x && pObject->vtxMinObj.x <= pBullet->pos.x &&
				pObject->vtxMaxObj.z >= pBullet->pos.z && pObject->vtxMinObj.z <= pBullet->pos.z)
			{
				pBullet->bUse = false;
				FalseShadow(pBullet->nIdxShadow);			//�e���g���Ă��Ȃ���Ԃ�
				SetExplosion(pBullet->pos);					//�������g�p����
			}

			//�O�ς̓����蔻��//
			g_vecLine = (pMeshWall->pos + D3DXVECTOR3(200.0f, 0.0f, 0.0f) - (pMeshWall->pos + D3DXVECTOR3(-200.0f, 0.0f, 0.0f)));

			g_vecToPos = pBullet->pos - pMeshWall->pos;
			
			vec = (g_vecLine.z * g_vecToPos.x) - (g_vecLine.x * g_vecToPos.z);

			if (vec < 0)
			{
				pBullet->bUse = false;						//�g���Ă��Ȃ���Ԃ�
				FalseShadow(pBullet->nIdxShadow);			//�e���g���Ă��Ȃ���Ԃ�
				SetExplosion(pBullet->pos);					//�������g�p����
			}

			//�e�̈ʒu��ݒ�
			SetPositionShadow(pBullet->nIdxShadow, pBullet->pos);
		}
		pVtx += 4;			//���_�f�[�^�̃|�C���^��4���i�߂�
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBullet->Unlock();
}

//========================================================================
//�e�̕`�揈��
//========================================================================
void DrawBullet(void)
{
	//�e���̎擾
	Bullet *pBullet = GetBullet();
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾
	D3DXMATRIX mtxTrans;						//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxView;							//�r���[�}�g���b�N�X�̎擾�p

	//�e�̐���������
	g_nBulletCnt = 0;

	//�A���t�@�e�X�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);			//�A���t�@�e�X�g�̗L��/�����̐ݒ�
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);		//��r���@
	pDevice->SetRenderState(D3DRS_ALPHAREF, 10);					//��l

	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);			//���C�e�B���O�̗L��/�����̐ݒ�

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++, pBullet++)
	{
		if (pBullet->bUse == true)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&pBullet->mtxWorldBullet);

			//�r���[�}�g���b�N�X���擾
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//�|���S�����J�����ɑ΂��Đ��ʂɌ�����
			D3DXMatrixInverse(&pBullet->mtxWorldBullet, NULL, &mtxView);

			pBullet->mtxWorldBullet._41 = 0.0f;
			pBullet->mtxWorldBullet._42 = 0.0f;
			pBullet->mtxWorldBullet._43 = 0.0f;

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, pBullet->pos.x, pBullet->pos.y, pBullet->pos.z);
			D3DXMatrixMultiply(&pBullet->mtxWorldBullet, &pBullet->mtxWorldBullet, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &pBullet->mtxWorldBullet);

			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffBullet,
				0, sizeof(VERTEX_3D));			//���_���\���̂̃T�C�Y

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureBullet[0]);

			//�|���S���̕`��
 			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,				//�v���~�e�B�u�̎��
				nCntBullet * 4,						//�`�悷��ŏ��̃C���f�b�N�X
				2);						//�v���~�e�B�u(�|���S��)��

			//�e���̃J�E���g
			g_nBulletCnt++;
		}
	}

	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);			//���C�e�B���O�̗L��/�����̐ݒ�

	//�A���t�@�e�X�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);			//�A���t�@�e�X�g�̗L��/�����̐ݒ�
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);		//��r���@
	pDevice->SetRenderState(D3DRS_ALPHAREF, 10);					//��l
}

//========================================================================
//�e�̐ݒ菈��
//========================================================================
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife, BULLETTYPE type)
{
	//�ϐ��錾
	int nCntBullet;

	//�e���̎擾
	Bullet *pBullet = GetBullet();

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++, pBullet++)
	{
		if (pBullet->bUse == false)
		{//�e���g�p����Ă��Ȃ�
			//���ꂼ��̎擾
			pBullet->pos = pos;						//�ʒu
			pBullet->type = type;					//���
			pBullet->nLife = nLife;					//����
			pBullet->move = move * BULLET_SPEED;	//�ړ���

			//�g�p���Ă����Ԃɂ���
			pBullet->bUse = true;

			//�e�̈ʒu��ݒ�
			pBullet->nIdxShadow = SetShadow(BULLET_SIZE);

			break;
		}
	}
}

//===================================================
// �f�o�b�O�\�L
//===================================================
void DrawDebug(void)
{
	RECT rect = { 0, 680, SCREEN_WIDTH, SCREEN_HEIGHT };
	char aStr[256];

	int  nCntBullet = BulletCnt();
	LPD3DXFONT pFont = GetFont();

	//���������
	wsprintf(&aStr[0], "%d", nCntBullet);

	//�e�L�X�g�`��
	pFont->DrawTextA(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}

//==================================================================================================
//�|�C���^�擾
//==================================================================================================
Bullet *GetBullet(void)
{
	return &g_aBullet[0];
}

//========================================================================
//�e�����擾
//========================================================================
int BulletCnt(void)
{
	return g_nBulletCnt;
}

