//======================================================================================
//
// モデルの処理[model.cpp]
// Author;小笠原　彪
//
//======================================================================================
#include "model.h"
#include "input.h"
#include "shadow.h"
#include "camera.h"

#define MODEL_SPEED			(0.4f)			//モデルの移動速度
#define MODEL_ATT			(0.5f)			//モデルの減衰

//グローバル宣言
LPDIRECT3DTEXTURE9 g_pTextureModel[8] = {};
LPD3DXMESH g_pMeshModel = NULL;
LPD3DXBUFFER g_pBuffMatModel = NULL;
DWORD g_dwNumMatModel = 0;
D3DXVECTOR3 g_posModel;
D3DXVECTOR3 g_rotModel;
D3DXVECTOR3 g_moveModel;
D3DXMATRIX g_mtxWorldModel;

//int g_nIdxShadow = -1;			//対象の影のインデックス(番号)

//====================================================================
// モデルの初期化処理
//====================================================================
void InitModel(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//グローバル宣言の初期化
	g_posModel = D3DXVECTOR3(0.0f, 50.0f, 0.0f);
	g_rotModel = D3DXVECTOR3(0.0f, 1.5f, 0.0f);
	g_moveModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//Xファイルの読み込み
	D3DXLoadMeshFromX("data\\MODEL\\model000.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatModel,
		NULL,
		&g_dwNumMatModel,
		&g_pMeshModel);

	D3DXMATERIAL *pMat;			//マテリアルへのポインタ

	//マテリアルへのポインタを取得
	pMat = (D3DXMATERIAL*)g_pBuffMatModel->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_dwNumMatModel; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{//ファイルからテクスチャを読み込む
		
			D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\wood000.png", &g_pTextureModel[2]);
			D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\sumi.jpg", &g_pTextureModel[3]);
		}
	}

	//影の位置を設定
	//g_nIdxShadow = SetShadow();
}

//====================================================================
// モデルの終了処理
//====================================================================
void UninitModel(void)
{
	//メッシュの破棄
	if (g_pMeshModel != NULL)
	{
		g_pMeshModel->Release();
		g_pMeshModel = NULL;
	}
	//マテリアルの破棄
	if (g_pBuffMatModel != NULL)
	{
		g_pBuffMatModel->Release();
		g_pBuffMatModel = NULL;
	}
}

//====================================================================
// モデルの更新処理
//====================================================================
void UpdateModel(void)
{
	Camera camera = GetCamera();

	//キー入力で移動する処理
	if (GetKeyboardPress(DIK_LEFT) == true)
	{//Aキーが押された
		if (GetKeyboardPress(DIK_UP) == true)
		{
			//左上移動
			g_moveModel.x += sinf(-D3DX_PI * 0.75f) * MODEL_SPEED;
			g_moveModel.z -= cosf(-D3DX_PI * 0.75f) * MODEL_SPEED;


		}
		else if (GetKeyboardPress(DIK_DOWN) == true)
		{
			//左上移動
			g_moveModel.x += sinf(-D3DX_PI * 0.25f) * MODEL_SPEED;
			g_moveModel.z -= cosf(-D3DX_PI * 0.25f) * MODEL_SPEED;
		}
		else
		{
			g_moveModel.x -= MODEL_SPEED;
		}
	}
	else if (GetKeyboardPress(DIK_RIGHT) == true)
	{//Dキーが押された
		if (GetKeyboardPress(DIK_UP) == true)
		{
			//右上移動
			g_moveModel.x += sinf(D3DX_PI * 0.75f) * MODEL_SPEED;
			g_moveModel.z -= cosf(D3DX_PI * 0.75f) * MODEL_SPEED;
		}
		else if (GetKeyboardPress(DIK_DOWN) == true)
		{
			//右下移動
			g_moveModel.x += sinf(D3DX_PI * 0.25f) * MODEL_SPEED;
			g_moveModel.z -= cosf(D3DX_PI * 0.25f) * MODEL_SPEED;
		}
		else
		{
			g_moveModel.x += MODEL_SPEED;
		}
	}
	else if (GetKeyboardPress(DIK_UP) == true)
	{//Wキーが押された
		g_moveModel.z += MODEL_SPEED;
	}
	else if (GetKeyboardPress(DIK_DOWN) == true)
	{//Sキーが押された
		g_moveModel.z -= MODEL_SPEED;
	}

	//カメラ位置情報の更新
	g_posModel.x += g_moveModel.x;			//視点X
	g_posModel.y += g_moveModel.y;			//視点Y
	g_posModel.z += g_moveModel.z;			//視点Y
	
	g_posModel.x += g_moveModel.x;			//注視点X
	g_posModel.y += g_moveModel.y;			//注視点Y
	g_posModel.z += g_moveModel.z;			//注視点Z

	//移動量を更新(減衰させる)
	g_moveModel.x += (0.0f - g_moveModel.x) * MODEL_ATT;
	g_moveModel.y += (0.0f - g_moveModel.y) * MODEL_ATT;
	g_moveModel.z += (0.0f - g_moveModel.z) * MODEL_ATT;

	//モデル位置情報の更新
	g_posModel += g_moveModel;

	g_posModel = D3DXVECTOR3(g_posModel.x, g_posModel.y, g_posModel.z);

	//影の位置を設定
	//SetPositionShadow(g_nIdxShadow, g_posModel);
}

//====================================================================
// モデルの描画処理
//====================================================================
void DrawModel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;				//計算用マトリックス
	D3DMATERIAL9 matDef;						//現在のマテリアル保存用
	D3DXMATERIAL *pMat;							//マテリアルデータへのポインタ

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxWorldModel);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotModel.y, g_rotModel.x, g_rotModel.z);

	D3DXMatrixMultiply(&g_mtxWorldModel, &g_mtxWorldModel, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_posModel.x, g_posModel.y, g_posModel.z);

	D3DXMatrixMultiply(&g_mtxWorldModel, &g_mtxWorldModel, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldModel);

	//現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	//マテリアルへのポインタを取得
	pMat = (D3DXMATERIAL*) g_pBuffMatModel->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_dwNumMatModel; nCntMat++)
	{
		//マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureModel[nCntMat]);

		//モデル(パーツ)の描画
		g_pMeshModel->DrawSubset(nCntMat);
	}

	//保存されていたマテリアルを戻す
	pDevice->SetMaterial(&matDef);
}

//====================================================================
// モデル情報の取得
//====================================================================
D3DXVECTOR3 GetModel(void)
{
	return g_posModel;
}