//======================================================================================
//
// メッシュフィールドの処理[polygon.cpp]
// Author;小笠原　彪
//
//======================================================================================
#include "meshwall.h"

//マクロ定義
#define BG_TEX_FULE		"data\\TEXTURE\\wall000.jpg"			//奥背景の画像を読み込む
#define MAX_MESHWALL		(128)			//メッシュウォールの最大数
#define MESHWALL_WIDTH		(1000.0f)		//幅
#define MESHWALL_HEIGHT		(100.0f)			//高さ

//グローバル定義
LPDIRECT3DTEXTURE9 g_pTextureMeshWall = NULL;				//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshWall = NULL;			//頂点バッファへのポインタ
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshWall = NULL;			//インデックスバッファへのポインタ
MeshWall g_meshWall[MAX_MESHWALL];							//フィールド情報

//====================================================================
// メッシュウォールの初期化処理
//====================================================================
void InitMeshWall(void)
{
	//変数宣言
	int nCnt;

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, BG_TEX_FULE, &g_pTextureMeshWall);

	//変数の初期化
	for (nCnt = 0; nCnt < MAX_MESHWALL; nCnt++)
	{
		g_meshWall[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_meshWall[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_meshWall[nCnt].bUse = false;
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 14 * MAX_MESHWALL,
		D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED,
		&g_pVtxBuffMeshWall, 
		NULL);

	//頂点情報へのポインタ
	VERTEX_3D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffMeshWall->Lock(0, 0, (void**)&pVtx, 0);

	for (nCnt = 0; nCnt < MAX_MESHWALL; nCnt++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-MESHWALL_WIDTH, MESHWALL_HEIGHT, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, MESHWALL_HEIGHT, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(MESHWALL_WIDTH, MESHWALL_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(-MESHWALL_WIDTH, MESHWALL_HEIGHT * 0.5f, 0.0f);
		pVtx[4].pos = D3DXVECTOR3(0.0f, MESHWALL_HEIGHT * 0.5f, 0.0f);
		pVtx[5].pos = D3DXVECTOR3(MESHWALL_WIDTH, MESHWALL_HEIGHT * 0.5f, 0.0f);
		pVtx[6].pos = D3DXVECTOR3(-MESHWALL_WIDTH, 0.0f, 0.0f);
		pVtx[7].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[8].pos = D3DXVECTOR3(MESHWALL_WIDTH, 0.0f, 0.0f);
		//法線ベクトルの設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[4].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[5].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[6].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[7].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[8].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		//頂点カラー(0.0f～1.0f内で設定)
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[5].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[6].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[7].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[8].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//テクスチャの座標設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.5f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[3].tex = D3DXVECTOR2(0.0f, 0.5f);
		pVtx[4].tex = D3DXVECTOR2(0.5f, 0.5f);
		pVtx[5].tex = D3DXVECTOR2(1.0f, 0.5f);
		pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[7].tex = D3DXVECTOR2(0.5f, 1.0f);
		pVtx[8].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 9;			//頂点情報を9個分ずらす
	}

	//頂点バッファをアンロックする
	g_pVtxBuffMeshWall->Unlock();

	//インデックスバッファの生成(番号を覚えるためのメモリ)
	pDevice->CreateIndexBuffer(sizeof(WORD) * 14 * MAX_MESHWALL,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshWall, NULL);

	WORD *pIdx;			//インデックス情報へのポインタ

	//インデックスバッファをロックし、頂点番号データへのポインタを取得
	g_pIdxBuffMeshWall->Lock(0, 0, (void**)&pIdx, 0);

	for (nCnt = 0; nCnt < MAX_MESHWALL; nCnt++)
	{
		//頂点番号データの設定
		pIdx[0] = 3;
		pIdx[1] = 0;
		pIdx[2] = 4;
		pIdx[3] = 1;
		pIdx[4] = 5;
		pIdx[5] = 2;
		pIdx[6] = 2;
		pIdx[7] = 6;
		pIdx[8] = 6;
		pIdx[9] = 3;
		pIdx[10] = 7;
		pIdx[11] = 4;
		pIdx[12] = 8;
		pIdx[13] = 5;

		pIdx += 14;			//インデックスバッファをデータ分ずらす
	}

	//インデックスバッファをアンロックする
	g_pIdxBuffMeshWall->Unlock();

	SetMeshWall(D3DXVECTOR3(0.0f, 0.0f, 1000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetMeshWall(D3DXVECTOR3(0.0f, 0.0f, -1000.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));

	SetMeshWall(D3DXVECTOR3(-1000.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -D3DX_PI * 0.5f, 0.0f));
	SetMeshWall(D3DXVECTOR3(1000.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f));
}

//====================================================================
// メッシュウォールの終了処理
//====================================================================
void UninitMeshWall(void)
{
	//テクスチャの破棄
	if (g_pTextureMeshWall != NULL)
	{
		g_pTextureMeshWall->Release();
		g_pTextureMeshWall = NULL;
	}
	//頂点バッファの破棄
	if (g_pVtxBuffMeshWall != NULL)
	{
		g_pVtxBuffMeshWall->Release();
		g_pVtxBuffMeshWall = NULL;
	}
	//インデックスバッファの破棄
	if (g_pIdxBuffMeshWall != NULL)
	{
		g_pIdxBuffMeshWall->Release();
		g_pIdxBuffMeshWall = NULL;
	}
}

//====================================================================
// メッシュウォールの更新処理
//====================================================================
void UpdateMeshWall(void)
{

}

//====================================================================
// メッシュウォールの描画処理
//====================================================================
void DrawMeshWall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;				//計算用マトリックス
	
	for (int nCnt = 0; nCnt < MAX_MESHWALL; nCnt++)
	{
		if (g_meshWall[nCnt].bUse == true)
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_meshWall[nCnt].mtxWorldField);

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_meshWall[nCnt].rot.y, g_meshWall[nCnt].rot.x, g_meshWall[nCnt].rot.z);
			D3DXMatrixMultiply(&g_meshWall[nCnt].mtxWorldField, &g_meshWall[nCnt].mtxWorldField, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_meshWall[nCnt].pos.x, g_meshWall[nCnt].pos.y, g_meshWall[nCnt].pos.z);
			D3DXMatrixMultiply(&g_meshWall[nCnt].mtxWorldField, &g_meshWall[nCnt].mtxWorldField, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_meshWall[nCnt].mtxWorldField);

			//頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffMeshWall, 0,
				sizeof(VERTEX_3D));			//頂点情報構造体のサイズ

			//インデックスバッファをデータストリームに設定
			pDevice->SetIndices(g_pIdxBuffMeshWall);

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureMeshWall);

			//ポリゴンの描画
			pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0,
				9 * nCnt,			//用意した頂点の数
				0,
				12);		//描画するプリミティブの数
		}
	}
}

//====================================================================
// メッシュウォールの設定処理
//====================================================================
void SetMeshWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	for (int nCnt = 0; nCnt < MAX_MESHWALL; nCnt++)
	{
		if (g_meshWall[nCnt].bUse == false)
		{
			g_meshWall[nCnt].pos = pos;
			g_meshWall[nCnt].rot = rot;
			g_meshWall[nCnt].bUse = true;

			break;
		}
	}
}

//====================================================================
// メッシュウォールの情報取得
//====================================================================
MeshWall *GetMeshWall(void)
{
	return &g_meshWall[0];
}