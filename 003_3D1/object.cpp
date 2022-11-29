//======================================================================================
//
// �I�u�W�F�N�g�̏���[object.cpp]
// Author;���}���@�V
//
//======================================================================================
#include "object.h"
#include "input.h"
#include "shadow.h"
#include "camera.h"
#include "bullet.h"

//�}�N����`
#define NUM_OBJ				(3)				//���f���̐�

//���f���t�@�C����
const char *c_apModelnameObject[] =
{
	"data\\MODEL\\campfire.x",
	"data\\MODEL\\benchi.x",
};

//�I�u�W�F�N�g�̗񋓌^��`
typedef enum
{
	OBJTYPE_CAMPFIRE = 0,
	OBJTYPE_COIN,
	OBJTYPE_MAX
} OBJECT;

//�O���[�o���錾
LPD3DXMESH g_pMeshObject[NUM_OBJ] = {};
LPD3DXBUFFER g_pBuffMatObject[NUM_OBJ] = {};
DWORD g_dwNumMatObject[NUM_OBJ] = {};
Object g_object[NUM_OBJ];				//�I�u�W�F�N�g���
Obj g_obj[NUM_OBJ];

//====================================================================
// �I�u�W�F�N�g�̏���������
//====================================================================
void InitObject(void)
{
	//�ϐ��錾
	int nCntObj;			//for�J�E���g�p
	int nNumVtx;			//���_��
	DWORD dwSizeFVF;		//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff;			//���_�o�b�t�@�ւ̃|�C���^

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (nCntObj = 0; nCntObj < NUM_OBJ; nCntObj++)
	{//�ϐ��̏�����
		g_object[nCntObj].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_object[nCntObj].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_object[nCntObj].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_object[nCntObj].vtxMinObj = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_object[nCntObj].vtxMaxObj = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_object[nCntObj].nIdxShadow = -1;
		g_object[nCntObj].nType = 0;
		g_object[nCntObj].bUse = false;

		g_obj[nCntObj].pTexture[10];
	}

	for (nCntObj = 0; nCntObj < OBJTYPE_MAX; nCntObj++)
	{
		//X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX(c_apModelnameObject[nCntObj],
			D3DXMESH_SYSTEMMEM, pDevice,
			NULL, &g_pBuffMatObject[nCntObj],
			NULL, &g_dwNumMatObject[nCntObj],
			&g_pMeshObject[nCntObj]);
	}

	for (nCntObj = 0; nCntObj < OBJTYPE_MAX; nCntObj++)
	{
		//���_�����擾
		nNumVtx = g_pMeshObject[nCntObj]->GetNumVertices();

		//���_�t�H�[�}�b�g�̃T�C�Y���擾
		dwSizeFVF = D3DXGetFVFVertexSize(g_pMeshObject[nCntObj]->GetFVF());

		//���_�o�b�t�@�����b�N
		g_pMeshObject[nCntObj]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;			//���_���W�̑��

			if (g_object[nCntObj].vtxMaxObj.x < vtx.x)
			{//x���傫��������
				g_object[nCntObj].vtxMaxObj.x = vtx.x;
			}
			if (g_object[nCntObj].vtxMaxObj.z < vtx.z)
			{//z�̒l���傫��������
				g_object[nCntObj].vtxMaxObj.z = vtx.z;
			}

			if (g_object[nCntObj].vtxMinObj.x > vtx.x)
			{//x��������������
				g_object[nCntObj].vtxMinObj.x = vtx.x;
			}
			if (g_object[nCntObj].vtxMinObj.z > vtx.z)
			{//z�̒l���傫��������
				g_object[nCntObj].vtxMinObj.z = vtx.z;
			}

			pVtxBuff += dwSizeFVF;			//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
		}
	}

	D3DXMATERIAL *pMat;			//�}�e���A���ւ̃|�C���^

	for (nCntObj = 0; nCntObj < OBJTYPE_MAX; nCntObj++)
	{
		//�}�e���A���ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)g_pBuffMatObject[nCntObj]->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_dwNumMatObject[nCntObj]; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{//�t�@�C������e�N�X�`����ǂݍ���
				D3DXCreateTextureFromFile(pDevice, pMat[nCntMat].pTextureFilename, &g_obj[nCntObj].pTexture[nCntMat]);
			}
		}

		//�e�̈ʒu��ݒ�
		//g_object[nCntObj].nIdxShadow = SetShadow(50.0f);
	}

	SetObject(D3DXVECTOR3(-100.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), OBJTYPE_CAMPFIRE);
	SetObject(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), OBJTYPE_COIN);
	SetObject(D3DXVECTOR3(100.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), OBJTYPE_COIN);
}

//====================================================================
// �I�u�W�F�N�g�̏I������
//====================================================================
void UninitObject(void)
{
	//�ϐ��錾
	int nCntObj;			//for�J�E���g�p

	for (nCntObj = 0; nCntObj < OBJTYPE_MAX; nCntObj++)
	{
		for (int nCntMat = 0; nCntMat < MAX_OBJTEX; nCntMat++)
		{
			//�e�N�X�`���[�̔j��
			if (g_obj[nCntObj].pTexture[nCntMat] != NULL)
			{
				g_obj[nCntObj].pTexture[nCntMat]->Release();
				g_obj[nCntObj].pTexture[nCntMat] = NULL;
			}
		}
	}
	for (nCntObj = 0; nCntObj < OBJTYPE_MAX; nCntObj++)
	{
		//���b�V���̔j��
		if (g_pMeshObject[nCntObj] != NULL)
		{
			g_pMeshObject[nCntObj]->Release();
			g_pMeshObject[nCntObj] = NULL;
		}
		//�}�e���A���̔j��
		if (g_pBuffMatObject[nCntObj] != NULL)
		{
			g_pBuffMatObject[nCntObj]->Release();
			g_pBuffMatObject[nCntObj] = NULL;
		}
	}
}

//====================================================================
// �I�u�W�F�N�g�̍X�V����
//====================================================================
void UpdateObject(void)
{
	//�e�̈ʒu��ݒ�
	//SetPositionShadow(g_object[nCntObj].nIdxShadow, g_object[nCntObj].pos);
}

//====================================================================
// �I�u�W�F�N�g�̕`�揈��
//====================================================================
void DrawObject(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;						//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;							//�}�e���A���f�[�^�ւ̃|�C���^

	for (int nCntObj = 0; nCntObj < NUM_OBJ; nCntObj++)
	{
		if (g_object[nCntObj].bUse == true)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_object[nCntObj].mtxWorld);

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_object[nCntObj].rot.y, g_object[nCntObj].rot.x, g_object[nCntObj].rot.z);

			D3DXMatrixMultiply(&g_object[nCntObj].mtxWorld, &g_object[nCntObj].mtxWorld, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_object[nCntObj].pos.x, g_object[nCntObj].pos.y, g_object[nCntObj].pos.z);

			D3DXMatrixMultiply(&g_object[nCntObj].mtxWorld, &g_object[nCntObj].mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_object[nCntObj].mtxWorld);

			//���݂̃}�e���A�����擾
			pDevice->GetMaterial(&matDef);

			//�}�e���A���ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)g_pBuffMatObject[g_object[nCntObj].nType]->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_dwNumMatObject[g_object[nCntObj].nType]; nCntMat++)
			{
				//�}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_obj[g_object[nCntObj].nType].pTexture[nCntMat]);

				//�I�u�W�F�N�g(�p�[�c)�̕`��
				g_pMeshObject[g_object[nCntObj].nType]->DrawSubset(nCntMat);
			}

			//�ۑ�����Ă����}�e���A����߂�
			pDevice->SetMaterial(&matDef);
		}
	}
}

//====================================================================
// ���f���ݒu����
//====================================================================
void SetObject(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType)
{
	for (int nCntObj = 0; nCntObj < NUM_OBJ; nCntObj++)
	{
		if (g_object[nCntObj].bUse == false)
		{
			//��������̏�����
			g_object[nCntObj].pos = pos;
			g_object[nCntObj].rot = rot;
			g_object[nCntObj].nType = nType;
			g_object[nCntObj].bUse = true;

			break;
		}
	}
}

//====================================================================
// ���f�����̎擾
//====================================================================
Object *GetObj(void)
{
	return &g_object[0];
}