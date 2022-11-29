//======================================================================================
//
// ポリゴンの処理[polygon.cpp]
// Author;小笠原　彪
//
//======================================================================================
#include "shadow.h"

//マクロ定義
#define TEX_FILENAME		"data\\TEXTURE\\shadow000.jpg"
#define MAX_SHADOW		(128)			//影の最大数

//グローバル定義
LPDIRECT3DTEXTURE9 g_pTextureShadow = NULL;				//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffShadow = NULL;		//頂点バッファへのポインタ

Shadow g_shadow[MAX_SHADOW];

//====================================================================
// 影の初期化処理
//====================================================================
void InitShadow(void)
{
	//変数宣言
	int nCntShadow;

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, TEX_FILENAME, &g_pTextureShadow);

	//変数の初期化
	for (nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		g_shadow[nCntShadow].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//移動量
		g_shadow[nCntShadow].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//向き
		g_shadow[nCntShadow].bUse = false;									//使っているか
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_SHADOW,
		D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED,
		&g_pVtxBuffShadow,
		NULL);

	//頂点情報へのポインタ
	VERTEX_3D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-10.0f, 0.0f, 10.0f);
		pVtx[1].pos = D3DXVECTOR3(10.0f, 0.0f, 10.0f);
		pVtx[2].pos = D3DXVECTOR3(-10.0f, 0.0f, -10.0f);
		pVtx[3].pos = D3DXVECTOR3(10.0f, 0.0f, -10.0f);
		//法線ベクトルの設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
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
	g_pVtxBuffShadow->Unlock();
}

//====================================================================
// 影の終了処理
//====================================================================
void UninitShadow(void)
{
	//テクスチャの破棄
	if (g_pTextureShadow != NULL)
	{
		g_pTextureShadow->Release();
		g_pTextureShadow = NULL;
	}
	//頂点バッファの破棄
	if (g_pVtxBuffShadow != NULL)
	{
		g_pVtxBuffShadow->Release();
		g_pVtxBuffShadow = NULL;
	}
}

//====================================================================
// 影の更新処理
//====================================================================
void UpdateShadow(void)
{

}

//====================================================================
// 影の描画処理
//====================================================================
void DrawShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;				//計算用マトリックス

	//減算合成の設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		if (g_shadow[nCntShadow].bUse == true)
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_shadow[nCntShadow].mtxWorld);

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_shadow[nCntShadow].rot.y, g_shadow[nCntShadow].rot.x, g_shadow[nCntShadow].rot.z);
			D3DXMatrixMultiply(&g_shadow[nCntShadow].mtxWorld, &g_shadow[nCntShadow].mtxWorld, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_shadow[nCntShadow].pos.x, g_shadow[nCntShadow].pos.y, g_shadow[nCntShadow].pos.z);
			D3DXMatrixMultiply(&g_shadow[nCntShadow].mtxWorld, &g_shadow[nCntShadow].mtxWorld, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_shadow[nCntShadow].mtxWorld);

			//頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffShadow, 0,
				sizeof(VERTEX_3D));			//頂点情報構造体のサイズ

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureShadow);

			//ポリゴンの描画
  			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,				//プリミティブの種類
				nCntShadow * 4,						//描画する最初のインデックス
				2);
		}
	}

	//通常の合成に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//====================================================================
// 影の設定処理
//====================================================================
int SetShadow(float size)
{
	int nCntShadow = -1;

	//頂点情報へのポインタ
	VERTEX_3D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_SHADOW; nCnt++)
	{
		if (g_shadow[nCnt].bUse == false)
		{
			nCntShadow = nCnt;

			g_shadow[nCnt].bUse = true;

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(-size, 0.0f, size);
			pVtx[1].pos = D3DXVECTOR3(size, 0.0f, size);
			pVtx[2].pos = D3DXVECTOR3(-size, 0.0f, -size);
			pVtx[3].pos = D3DXVECTOR3(size, 0.0f, -size);

			break;
		}
		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffShadow->Unlock();

	return nCntShadow;
}

//====================================================================
// 影の位置情報設定処理
//====================================================================
void SetPositionShadow(int nIdxShadow, D3DXVECTOR3 pos)
{
	//指定した影の位置を設定
	g_shadow[nIdxShadow].pos.x = pos.x;
	g_shadow[nIdxShadow].pos.z = pos.z;
}

//====================================================================
// 影を消す
//====================================================================
void FalseShadow(int nFalseShadow)
{
	if (nFalseShadow > -1)
	{
		g_shadow[nFalseShadow].bUse = false;
	}
}