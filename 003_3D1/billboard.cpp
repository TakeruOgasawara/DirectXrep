//======================================================================================
//
// ビルボードの処理[billboard.cpp]
// Author;小笠原　彪
//
//======================================================================================
#include "billboard.h"

#define BG_TEX_FULE		"data\\TEXTURE\\tree000.png"

//グローバル定義
LPDIRECT3DTEXTURE9 g_pTextureBillboard = NULL;				//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBillboard = NULL;			//頂点バッファへのポインタ
D3DXVECTOR3 g_posBillboard;			//位置

D3DXMATRIX g_mtxWorldBillboard;			//ワールドマトリックス

//====================================================================
// ビルボードの初期化処理
//====================================================================
void InitBillboard(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, BG_TEX_FULE, &g_pTextureBillboard);

	//グローバル宣言の初期化
	g_posBillboard = D3DXVECTOR3(100.0f, 0.0f, 35.0f);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED,
		&g_pVtxBuffBillboard, 
		NULL);

	//頂点情報へのポインタ
	VERTEX_3D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBillboard->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(-20.0f, 100.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(20.0f, 100.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-20.0f, 0.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(20.0f, 0.0f, 0.0f);
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

	//頂点バッファをアンロックする
	g_pVtxBuffBillboard->Unlock();
}

//====================================================================
// ビルボードの終了処理
//====================================================================
void UninitBillboard(void)
{
	//テクスチャの破棄
	if (g_pTextureBillboard != NULL)
	{
		g_pTextureBillboard->Release();
		g_pTextureBillboard = NULL;
	}
	//頂点バッファの破棄
	if (g_pVtxBuffBillboard != NULL)
	{
		g_pVtxBuffBillboard->Release();
		g_pVtxBuffBillboard = NULL;
	}
}

//====================================================================
// ビルボードの更新処理
//====================================================================
void UpdateBillboard(void)
{

}

//====================================================================
// ビルボードの描画処理
//====================================================================
void DrawBillboard(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得
	D3DXMATRIX mtxTrans;						//計算用マトリックス
	D3DXMATRIX mtxView;							//ビューマトリックスの取得用

	//zテストを無効にする
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);		//比較方法
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);			//zバッファ更新の有効無効設定

	//アルファテストを無効にする
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);			//アルファテストの有効/無効の設定
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);		//比較方法
	pDevice->SetRenderState(D3DRS_ALPHAREF, 10);					//基準値

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxWorldBillboard);

	//ビューマトリックスを取得
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	//ポリゴンをカメラに対して正面に向ける
	D3DXMatrixInverse(&g_mtxWorldBillboard, NULL, &mtxView);

	g_mtxWorldBillboard._41 = 0.0f;
	g_mtxWorldBillboard._42 = 0.0f;
	g_mtxWorldBillboard._43 = 0.0f;

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_posBillboard.x, g_posBillboard.y, g_posBillboard.z);

	D3DXMatrixMultiply(&g_mtxWorldBillboard, &g_mtxWorldBillboard, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldBillboard);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffBillboard, 0,
		sizeof(VERTEX_3D));			//頂点情報構造体のサイズ

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureBillboard);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,				//プリミティブの種類
		0,						//描画する最初のインデックス
		2);

	//zバッファを有効にする
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);			//zバッファ更新の有効無効設定

	//アルファテストを無効にする
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);			//アルファテストの有効/無効の設定
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);		//比較方法
	pDevice->SetRenderState(D3DRS_ALPHAREF, 10);					//基準値
}