//======================================================================================
//
// ���f���̏���[model.cpp]
// Author;���}���@�V
//
//======================================================================================
#include "model.h"
#include "input.h"
#include "shadow.h"
#include "camera.h"

#define MODEL_SPEED			(0.4f)			//���f���̈ړ����x
#define MODEL_ATT			(0.5f)			//���f���̌���

//�O���[�o���錾
LPDIRECT3DTEXTURE9 g_pTextureModel[8] = {};
LPD3DXMESH g_pMeshModel = NULL;
LPD3DXBUFFER g_pBuffMatModel = NULL;
DWORD g_dwNumMatModel = 0;
D3DXVECTOR3 g_posModel;
D3DXVECTOR3 g_rotModel;
D3DXVECTOR3 g_moveModel;
D3DXMATRIX g_mtxWorldModel;

//int g_nIdxShadow = -1;			//�Ώۂ̉e�̃C���f�b�N�X(�ԍ�)

//====================================================================
// ���f���̏���������
//====================================================================
void InitModel(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�O���[�o���錾�̏�����
	g_posModel = D3DXVECTOR3(0.0f, 50.0f, 0.0f);
	g_rotModel = D3DXVECTOR3(0.0f, 1.5f, 0.0f);
	g_moveModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX("data\\MODEL\\model000.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatModel,
		NULL,
		&g_dwNumMatModel,
		&g_pMeshModel);

	D3DXMATERIAL *pMat;			//�}�e���A���ւ̃|�C���^

	//�}�e���A���ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)g_pBuffMatModel->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_dwNumMatModel; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{//�t�@�C������e�N�X�`����ǂݍ���
		
			D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\wood000.png", &g_pTextureModel[2]);
			D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\sumi.jpg", &g_pTextureModel[3]);
		}
	}

	//�e�̈ʒu��ݒ�
	//g_nIdxShadow = SetShadow();
}

//====================================================================
// ���f���̏I������
//====================================================================
void UninitModel(void)
{
	//���b�V���̔j��
	if (g_pMeshModel != NULL)
	{
		g_pMeshModel->Release();
		g_pMeshModel = NULL;
	}
	//�}�e���A���̔j��
	if (g_pBuffMatModel != NULL)
	{
		g_pBuffMatModel->Release();
		g_pBuffMatModel = NULL;
	}
}

//====================================================================
// ���f���̍X�V����
//====================================================================
void UpdateModel(void)
{
	Camera camera = GetCamera();

	//�L�[���͂ňړ����鏈��
	if (GetKeyboardPress(DIK_LEFT) == true)
	{//A�L�[�������ꂽ
		if (GetKeyboardPress(DIK_UP) == true)
		{
			//����ړ�
			g_moveModel.x += sinf(-D3DX_PI * 0.75f) * MODEL_SPEED;
			g_moveModel.z -= cosf(-D3DX_PI * 0.75f) * MODEL_SPEED;


		}
		else if (GetKeyboardPress(DIK_DOWN) == true)
		{
			//����ړ�
			g_moveModel.x += sinf(-D3DX_PI * 0.25f) * MODEL_SPEED;
			g_moveModel.z -= cosf(-D3DX_PI * 0.25f) * MODEL_SPEED;
		}
		else
		{
			g_moveModel.x -= MODEL_SPEED;
		}
	}
	else if (GetKeyboardPress(DIK_RIGHT) == true)
	{//D�L�[�������ꂽ
		if (GetKeyboardPress(DIK_UP) == true)
		{
			//�E��ړ�
			g_moveModel.x += sinf(D3DX_PI * 0.75f) * MODEL_SPEED;
			g_moveModel.z -= cosf(D3DX_PI * 0.75f) * MODEL_SPEED;
		}
		else if (GetKeyboardPress(DIK_DOWN) == true)
		{
			//�E���ړ�
			g_moveModel.x += sinf(D3DX_PI * 0.25f) * MODEL_SPEED;
			g_moveModel.z -= cosf(D3DX_PI * 0.25f) * MODEL_SPEED;
		}
		else
		{
			g_moveModel.x += MODEL_SPEED;
		}
	}
	else if (GetKeyboardPress(DIK_UP) == true)
	{//W�L�[�������ꂽ
		g_moveModel.z += MODEL_SPEED;
	}
	else if (GetKeyboardPress(DIK_DOWN) == true)
	{//S�L�[�������ꂽ
		g_moveModel.z -= MODEL_SPEED;
	}

	//�J�����ʒu���̍X�V
	g_posModel.x += g_moveModel.x;			//���_X
	g_posModel.y += g_moveModel.y;			//���_Y
	g_posModel.z += g_moveModel.z;			//���_Y
	
	g_posModel.x += g_moveModel.x;			//�����_X
	g_posModel.y += g_moveModel.y;			//�����_Y
	g_posModel.z += g_moveModel.z;			//�����_Z

	//�ړ��ʂ��X�V(����������)
	g_moveModel.x += (0.0f - g_moveModel.x) * MODEL_ATT;
	g_moveModel.y += (0.0f - g_moveModel.y) * MODEL_ATT;
	g_moveModel.z += (0.0f - g_moveModel.z) * MODEL_ATT;

	//���f���ʒu���̍X�V
	g_posModel += g_moveModel;

	g_posModel = D3DXVECTOR3(g_posModel.x, g_posModel.y, g_posModel.z);

	//�e�̈ʒu��ݒ�
	//SetPositionShadow(g_nIdxShadow, g_posModel);
}

//====================================================================
// ���f���̕`�揈��
//====================================================================
void DrawModel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;						//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;							//�}�e���A���f�[�^�ւ̃|�C���^

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldModel);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotModel.y, g_rotModel.x, g_rotModel.z);

	D3DXMatrixMultiply(&g_mtxWorldModel, &g_mtxWorldModel, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_posModel.x, g_posModel.y, g_posModel.z);

	D3DXMatrixMultiply(&g_mtxWorldModel, &g_mtxWorldModel, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldModel);

	//���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	//�}�e���A���ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*) g_pBuffMatModel->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_dwNumMatModel; nCntMat++)
	{
		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureModel[nCntMat]);

		//���f��(�p�[�c)�̕`��
		g_pMeshModel->DrawSubset(nCntMat);
	}

	//�ۑ�����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

//====================================================================
// ���f�����̎擾
//====================================================================
D3DXVECTOR3 GetModel(void)
{
	return g_posModel;
}