//======================================================================================
//
// オブジェクトの処理[object.cpp]
// Author;小笠原　彪
//
//======================================================================================
#include "object.h"
#include "input.h"
#include "shadow.h"
#include "camera.h"
#include "bullet.h"

//マクロ定義
#define NUM_OBJ				(3)				//モデルの数

//モデルファイル名
const char *c_apModelnameObject[] =
{
	"data\\MODEL\\campfire.x",
	"data\\MODEL\\benchi.x",
};

//オブジェクトの列挙型定義
typedef enum
{
	OBJTYPE_CAMPFIRE = 0,
	OBJTYPE_COIN,
	OBJTYPE_MAX
} OBJECT;

//グローバル宣言
LPD3DXMESH g_pMeshObject[NUM_OBJ] = {};
LPD3DXBUFFER g_pBuffMatObject[NUM_OBJ] = {};
DWORD g_dwNumMatObject[NUM_OBJ] = {};
Object g_object[NUM_OBJ];				//オブジェクト情報
Obj g_obj[NUM_OBJ];

//====================================================================
// オブジェクトの初期化処理
//====================================================================
void InitObject(void)
{
	//変数宣言
	int nCntObj;			//forカウント用
	int nNumVtx;			//頂点数
	DWORD dwSizeFVF;		//頂点フォーマットのサイズ
	BYTE *pVtxBuff;			//頂点バッファへのポインタ

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (nCntObj = 0; nCntObj < NUM_OBJ; nCntObj++)
	{//変数の初期化
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
		//Xファイルの読み込み
		D3DXLoadMeshFromX(c_apModelnameObject[nCntObj],
			D3DXMESH_SYSTEMMEM, pDevice,
			NULL, &g_pBuffMatObject[nCntObj],
			NULL, &g_dwNumMatObject[nCntObj],
			&g_pMeshObject[nCntObj]);
	}

	for (nCntObj = 0; nCntObj < OBJTYPE_MAX; nCntObj++)
	{
		//頂点数を取得
		nNumVtx = g_pMeshObject[nCntObj]->GetNumVertices();

		//頂点フォーマットのサイズを取得
		dwSizeFVF = D3DXGetFVFVertexSize(g_pMeshObject[nCntObj]->GetFVF());

		//頂点バッファをロック
		g_pMeshObject[nCntObj]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;			//頂点座標の代入

			if (g_object[nCntObj].vtxMaxObj.x < vtx.x)
			{//xが大きかったら
				g_object[nCntObj].vtxMaxObj.x = vtx.x;
			}
			if (g_object[nCntObj].vtxMaxObj.z < vtx.z)
			{//zの値が大きかったら
				g_object[nCntObj].vtxMaxObj.z = vtx.z;
			}

			if (g_object[nCntObj].vtxMinObj.x > vtx.x)
			{//xが小さかったら
				g_object[nCntObj].vtxMinObj.x = vtx.x;
			}
			if (g_object[nCntObj].vtxMinObj.z > vtx.z)
			{//zの値が大きかったら
				g_object[nCntObj].vtxMinObj.z = vtx.z;
			}

			pVtxBuff += dwSizeFVF;			//頂点フォーマットのサイズ分ポインタを進める
		}
	}

	D3DXMATERIAL *pMat;			//マテリアルへのポインタ

	for (nCntObj = 0; nCntObj < OBJTYPE_MAX; nCntObj++)
	{
		//マテリアルへのポインタを取得
		pMat = (D3DXMATERIAL*)g_pBuffMatObject[nCntObj]->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_dwNumMatObject[nCntObj]; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{//ファイルからテクスチャを読み込む
				D3DXCreateTextureFromFile(pDevice, pMat[nCntMat].pTextureFilename, &g_obj[nCntObj].pTexture[nCntMat]);
			}
		}

		//影の位置を設定
		//g_object[nCntObj].nIdxShadow = SetShadow(50.0f);
	}

	SetObject(D3DXVECTOR3(-100.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), OBJTYPE_CAMPFIRE);
	SetObject(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), OBJTYPE_COIN);
	SetObject(D3DXVECTOR3(100.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), OBJTYPE_COIN);
}

//====================================================================
// オブジェクトの終了処理
//====================================================================
void UninitObject(void)
{
	//変数宣言
	int nCntObj;			//forカウント用

	for (nCntObj = 0; nCntObj < OBJTYPE_MAX; nCntObj++)
	{
		for (int nCntMat = 0; nCntMat < MAX_OBJTEX; nCntMat++)
		{
			//テクスチャーの破棄
			if (g_obj[nCntObj].pTexture[nCntMat] != NULL)
			{
				g_obj[nCntObj].pTexture[nCntMat]->Release();
				g_obj[nCntObj].pTexture[nCntMat] = NULL;
			}
		}
	}
	for (nCntObj = 0; nCntObj < OBJTYPE_MAX; nCntObj++)
	{
		//メッシュの破棄
		if (g_pMeshObject[nCntObj] != NULL)
		{
			g_pMeshObject[nCntObj]->Release();
			g_pMeshObject[nCntObj] = NULL;
		}
		//マテリアルの破棄
		if (g_pBuffMatObject[nCntObj] != NULL)
		{
			g_pBuffMatObject[nCntObj]->Release();
			g_pBuffMatObject[nCntObj] = NULL;
		}
	}
}

//====================================================================
// オブジェクトの更新処理
//====================================================================
void UpdateObject(void)
{
	//影の位置を設定
	//SetPositionShadow(g_object[nCntObj].nIdxShadow, g_object[nCntObj].pos);
}

//====================================================================
// オブジェクトの描画処理
//====================================================================
void DrawObject(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;				//計算用マトリックス
	D3DMATERIAL9 matDef;						//現在のマテリアル保存用
	D3DXMATERIAL *pMat;							//マテリアルデータへのポインタ

	for (int nCntObj = 0; nCntObj < NUM_OBJ; nCntObj++)
	{
		if (g_object[nCntObj].bUse == true)
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_object[nCntObj].mtxWorld);

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_object[nCntObj].rot.y, g_object[nCntObj].rot.x, g_object[nCntObj].rot.z);

			D3DXMatrixMultiply(&g_object[nCntObj].mtxWorld, &g_object[nCntObj].mtxWorld, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_object[nCntObj].pos.x, g_object[nCntObj].pos.y, g_object[nCntObj].pos.z);

			D3DXMatrixMultiply(&g_object[nCntObj].mtxWorld, &g_object[nCntObj].mtxWorld, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_object[nCntObj].mtxWorld);

			//現在のマテリアルを取得
			pDevice->GetMaterial(&matDef);

			//マテリアルへのポインタを取得
			pMat = (D3DXMATERIAL*)g_pBuffMatObject[g_object[nCntObj].nType]->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_dwNumMatObject[g_object[nCntObj].nType]; nCntMat++)
			{
				//マテリアルの設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				//テクスチャの設定
				pDevice->SetTexture(0, g_obj[g_object[nCntObj].nType].pTexture[nCntMat]);

				//オブジェクト(パーツ)の描画
				g_pMeshObject[g_object[nCntObj].nType]->DrawSubset(nCntMat);
			}

			//保存されていたマテリアルを戻す
			pDevice->SetMaterial(&matDef);
		}
	}
}

//====================================================================
// モデル設置処理
//====================================================================
void SetObject(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType)
{
	for (int nCntObj = 0; nCntObj < NUM_OBJ; nCntObj++)
	{
		if (g_object[nCntObj].bUse == false)
		{
			//引数からの情報を代入
			g_object[nCntObj].pos = pos;
			g_object[nCntObj].rot = rot;
			g_object[nCntObj].nType = nType;
			g_object[nCntObj].bUse = true;

			break;
		}
	}
}

//====================================================================
// モデル情報の取得
//====================================================================
Object *GetObj(void)
{
	return &g_object[0];
}