//======================================================================================
//
// メッシュシリンダーの処理[meshcylindwe.h]
// Author;小笠原　彪
//
//======================================================================================
#include "meshcylinder.h"

//マクロ定義
#define BG_TEX_FULE		"data\\TEXTURE\\mountain000.png"			//奥背景の画像を読み込む
#define MESH_LENGTH		(3000.0f)			//シリンダーの半径の長さ
#define MESH_HEIGHT		(400.0f)			//シリンダーの高さ

//グローバル定義
LPDIRECT3DTEXTURE9 g_pTextureMeshCylinder = NULL;				//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshCylinder = NULL;			//頂点バッファへのポインタ
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshCylinder = NULL;			//インデックスバッファへのポインタ
MeshCylinder g_meshCylinder;			//フィールド情報

//====================================================================
//ポリゴンの初期化処理
//====================================================================
void InitMeshCylinder(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, BG_TEX_FULE, &g_pTextureMeshCylinder);

	//変数の初期化
	g_meshCylinder.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_meshCylinder.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 20,
		D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED,
		&g_pVtxBuffMeshCylinder, 
		NULL);
	
	//頂点情報へのポインタ
	VERTEX_3D *pVtx;
	
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffMeshCylinder->Lock(0, 0, (void**)&pVtx, 0);
	
	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(cosf(D3DX_PI * 0.0f) * MESH_LENGTH, MESH_HEIGHT, sinf(D3DX_PI * 0.0f) * MESH_LENGTH);
	pVtx[1].pos = D3DXVECTOR3(cosf(D3DX_PI * 0.25f) * MESH_LENGTH, MESH_HEIGHT, sinf(D3DX_PI * 0.25f) * MESH_LENGTH);
	pVtx[2].pos = D3DXVECTOR3(cosf(D3DX_PI * 0.5f) * MESH_LENGTH, MESH_HEIGHT, sinf(D3DX_PI * 0.5f) * MESH_LENGTH);
	pVtx[3].pos = D3DXVECTOR3(cosf(D3DX_PI * 0.75f) * MESH_LENGTH, MESH_HEIGHT, sinf(D3DX_PI * 0.75f) * MESH_LENGTH);
	pVtx[4].pos = D3DXVECTOR3(cosf(D3DX_PI * 1.0f) * MESH_LENGTH, MESH_HEIGHT, sinf(D3DX_PI * 1.0f) * MESH_LENGTH);
	pVtx[5].pos = D3DXVECTOR3(cosf(-D3DX_PI * 0.75f) * MESH_LENGTH, MESH_HEIGHT, sinf(-D3DX_PI * 0.75f) * MESH_LENGTH);
	pVtx[6].pos = D3DXVECTOR3(cosf(-D3DX_PI * 0.5f) * MESH_LENGTH, MESH_HEIGHT, sinf(-D3DX_PI * 0.5f) * MESH_LENGTH);
	pVtx[7].pos = D3DXVECTOR3(cosf(-D3DX_PI * 0.25f) * MESH_LENGTH, MESH_HEIGHT, sinf(-D3DX_PI * 0.25f) * MESH_LENGTH);
	////重なっている所(上側)
	pVtx[8].pos = D3DXVECTOR3(cosf(D3DX_PI * 0.0f) * MESH_LENGTH, MESH_HEIGHT, sinf(D3DX_PI * 0.0f) * MESH_LENGTH);
	//下側
	pVtx[9].pos = D3DXVECTOR3(cosf(D3DX_PI * 0.0f) * MESH_LENGTH, 0.0f, sinf(D3DX_PI * 0.0f) * MESH_LENGTH);
	pVtx[10].pos = D3DXVECTOR3(cosf(D3DX_PI * 0.25f) * MESH_LENGTH, 0.0f, sinf(D3DX_PI * 0.25f) * MESH_LENGTH);
	pVtx[11].pos = D3DXVECTOR3(cosf(D3DX_PI * 0.5f) * MESH_LENGTH, 0.0f, sinf(D3DX_PI * 0.5f) * MESH_LENGTH);
	pVtx[12].pos = D3DXVECTOR3(cosf(D3DX_PI * 0.75f) * MESH_LENGTH, 0.0f, sinf(D3DX_PI * 0.75f) * MESH_LENGTH);
	pVtx[13].pos = D3DXVECTOR3(cosf(D3DX_PI * 1.0f) * MESH_LENGTH, 0.0f, sinf(D3DX_PI * 1.0f) * MESH_LENGTH);
	pVtx[14].pos = D3DXVECTOR3(cosf(-D3DX_PI * 0.75f) * MESH_LENGTH, 0.0f, sinf(-D3DX_PI * 0.75f) * MESH_LENGTH);
	pVtx[15].pos = D3DXVECTOR3(cosf(-D3DX_PI * 0.5f) * MESH_LENGTH, 0.0f, sinf(-D3DX_PI * 0.5f) * MESH_LENGTH);
	pVtx[16].pos = D3DXVECTOR3(cosf(-D3DX_PI * 0.25f) * MESH_LENGTH, 0.0f, sinf(-D3DX_PI * 0.25f) * MESH_LENGTH);
	//重なっている所(下側)
	pVtx[17].pos = D3DXVECTOR3(cosf(D3DX_PI * 0.0f) * MESH_LENGTH, 0.0f, sinf(D3DX_PI * 0.0f) * MESH_LENGTH);

	for (int nCnt = 0; nCnt < 18; nCnt++)
	{
		//法線ベクトルの設定
		pVtx[nCnt].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//頂点カラー(0.0f～1.0f内で設定)
		pVtx[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}

	//テクスチャの座標設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.125f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.25f, 0.0f);
	pVtx[3].tex = D3DXVECTOR2(0.375f, 0.0f);
	pVtx[4].tex = D3DXVECTOR2(0.5f, 0.0f);
	pVtx[5].tex = D3DXVECTOR2(0.625f, 0.0f);
	pVtx[6].tex = D3DXVECTOR2(0.75f, 0.0f);
	pVtx[7].tex = D3DXVECTOR2(0.875f, 0.0f);
	pVtx[8].tex = D3DXVECTOR2(1.0f, 0.0f);
	//下側
	pVtx[9].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[10].tex = D3DXVECTOR2(0.125f, 1.0f);
	pVtx[11].tex = D3DXVECTOR2(0.25f, 1.0f);
	pVtx[12].tex = D3DXVECTOR2(0.375f, 1.0f);
	pVtx[13].tex = D3DXVECTOR2(0.5f, 1.0f);
	pVtx[14].tex = D3DXVECTOR2(0.625f, 1.0f);
	pVtx[15].tex = D3DXVECTOR2(0.75f, 1.0f);
	pVtx[16].tex = D3DXVECTOR2(0.875f, 1.0f);
	pVtx[17].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffMeshCylinder->Unlock();

	//インデックスバッファの生成(番号を覚えるためのメモリ)
	pDevice->CreateIndexBuffer(sizeof(WORD) * 20,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshCylinder, NULL);

	WORD *pIdx;			//インデックス情報へのポインタ

	//インデックスバッファをロックし、頂点番号データへのポインタを取得
	g_pIdxBuffMeshCylinder->Lock(0, 0, (void**)&pIdx, 0);

	//頂点番号データの設定
	pIdx[0] = 0;
	pIdx[1] = 9;
	pIdx[2] = 1;
	pIdx[3] = 10;

	pIdx[4] = 2;
	pIdx[5] = 11;
	pIdx[6] = 3;
	pIdx[7] = 12;

	pIdx[8] = 4;
	pIdx[9] = 13;
	pIdx[10] = 5;
	pIdx[11] = 14;

	pIdx[12] = 6;
	pIdx[13] = 15;
	pIdx[14] = 7;
	pIdx[15] = 16;

	pIdx[16] = 8;
	pIdx[17] = 17;

	//インデックスバッファをアンロックする
	g_pIdxBuffMeshCylinder->Unlock();
}

//====================================================================
//ポリゴンの終了処理
//====================================================================
void UninitMeshCylinder(void)
{
	//テクスチャの破棄
	if (g_pTextureMeshCylinder != NULL)
	{
		g_pTextureMeshCylinder->Release();
		g_pTextureMeshCylinder = NULL;
	}
	//頂点バッファの破棄
	if (g_pVtxBuffMeshCylinder != NULL)
	{
		g_pVtxBuffMeshCylinder->Release();
		g_pVtxBuffMeshCylinder = NULL;
	}
	//インデックスバッファの破棄
	if (g_pIdxBuffMeshCylinder != NULL)
	{
		g_pIdxBuffMeshCylinder->Release();
		g_pIdxBuffMeshCylinder = NULL;
	}
}

//====================================================================
//ポリゴンの更新処理
//====================================================================
void UpdateMeshCylinder(void)
{

}

//====================================================================
//ポリゴンの描画処理
//====================================================================
void DrawMeshCylinder(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;				//計算用マトリックス
	
	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_meshCylinder.mtxWorldField);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_meshCylinder.rot.y, g_meshCylinder.rot.x, g_meshCylinder.rot.z);
	D3DXMatrixMultiply(&g_meshCylinder.mtxWorldField, &g_meshCylinder.mtxWorldField, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_meshCylinder.pos.x, g_meshCylinder.pos.y, g_meshCylinder.pos.z);
	D3DXMatrixMultiply(&g_meshCylinder.mtxWorldField, &g_meshCylinder.mtxWorldField, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_meshCylinder.mtxWorldField);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffMeshCylinder, 0,
		sizeof(VERTEX_3D));			//頂点情報構造体のサイズ

	//インデックスバッファをデータストリームに設定
	pDevice->SetIndices(g_pIdxBuffMeshCylinder);

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureMeshCylinder);

	//ポリゴンの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0,
		9,			//用意した頂点の数
		0,
		20);		//描画するプリミティブの数
}