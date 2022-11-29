//======================================================================================
//
// 壁の処理[wall.cpp]
// Author;小笠原　彪
//
//======================================================================================
#include "wall.h"

//マクロ定義
#define TEX_NAME			"data\\TEXTURE\\wall000.jpg"
#define MAX_WALL			(128)			//壁の最大数

//グローバル定義
LPDIRECT3DTEXTURE9 g_pTextureWall = NULL;				//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffWall = NULL;			//頂点バッファへのポインタ
Wall g_wall[MAX_WALL];			//壁の情報

//====================================================================
// 壁の初期化処理
//====================================================================
void InitWall(void)
{
	//変数宣言
	int nCntWall;			//forカウント用

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, TEX_NAME, &g_pTextureWall);

	//変数の初期化
	for (nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		g_wall[nCntWall].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_wall[nCntWall].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_wall[nCntWall].bUse = false;
	}


	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_WALL,
		D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED,
		&g_pVtxBuffWall, 
		NULL);

	//頂点情報へのポインタ
	VERTEX_3D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-50.0f, 50.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(50.0f, 50.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-50.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(50.0f, 0.0f, 0.0f);
		//法線ベクトルの設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		//頂点カラー(0.0f～1.0f内で設定)
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//テクスチャの座標設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffWall->Unlock();

	SetWall(D3DXVECTOR3(0.0f, 0.0f, 150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetWall(D3DXVECTOR3(100.0f, 0.0f, 150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetWall(D3DXVECTOR3(-100.0f, 0.0f, 150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetWall(D3DXVECTOR3(0.0f, 0.0f, -50.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));
	SetWall(D3DXVECTOR3(100.0f, 0.0f, -50.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));
	SetWall(D3DXVECTOR3(-100.0f, 0.0f, -50.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));

	SetWall(D3DXVECTOR3(150.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f));
	SetWall(D3DXVECTOR3(150.0f, 0.0f, 100.0f), D3DXVECTOR3(0.0f, D3DX_PI* 0.5f, 0.0f));
	SetWall(D3DXVECTOR3(-150.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -D3DX_PI* 0.5f, 0.0f));
	SetWall(D3DXVECTOR3(-150.0f, 0.0f, 100.0f), D3DXVECTOR3(0.0f, -D3DX_PI* 0.5f, 0.0f));
}

//====================================================================
// 壁の終了処理
//====================================================================
void UninitWall(void)
{
	//テクスチャの破棄
	if (g_pTextureWall != NULL)
	{
		g_pTextureWall->Release();
		g_pTextureWall = NULL;
	}
	//頂点バッファの破棄
	if (g_pVtxBuffWall != NULL)
	{
		g_pVtxBuffWall->Release();
		g_pVtxBuffWall = NULL;
	}
}

//====================================================================
// 壁の更新処理
//====================================================================
void UpdateWall(void)
{

}

//====================================================================
// 壁の描画処理
//====================================================================
void DrawWall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;				//計算用マトリックス

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		if (g_wall[nCntWall].bUse == true)
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_wall[nCntWall].mtxWorldWall);

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_wall[nCntWall].rot.y, g_wall[nCntWall].rot.x, g_wall[nCntWall].rot.z);
			D3DXMatrixMultiply(&g_wall[nCntWall].mtxWorldWall, &g_wall[nCntWall].mtxWorldWall, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_wall[nCntWall].pos.x, g_wall[nCntWall].pos.y, g_wall[nCntWall].pos.z);
			D3DXMatrixMultiply(&g_wall[nCntWall].mtxWorldWall, &g_wall[nCntWall].mtxWorldWall, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_wall[nCntWall].mtxWorldWall);

			//頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffWall, 0,
				sizeof(VERTEX_3D));			//頂点情報構造体のサイズ

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureWall);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,				//プリミティブの種類
				nCntWall * 4,						//描画する最初のインデックス
				2);
		}
	}
}

//====================================================================
// 壁の設定処理
//====================================================================
void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	//頂点情報へのポインタ
	VERTEX_3D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		if (g_wall[nCntWall].bUse == false)
		{
			g_wall[nCntWall].pos = pos;
			g_wall[nCntWall].rot = rot;

			g_wall[nCntWall].bUse = true;

			break;			//for分を抜ける
		}

		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffWall->Unlock();
}
