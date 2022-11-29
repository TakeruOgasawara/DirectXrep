//======================================================================================
//
//弾の処理[Player.cpp]
//Author;小笠原　彪
//
//======================================================================================
#include "explosion.h"

//マクロ定義
#define MAX_EXPLOSION			(128)			//爆発の最大数

#define EXPLOSION_TEX_FILE		"data\\TEXTURE\\explosion.png"		//画像を読み込む
#define EXPLO_SIZE			(20.0f)					//爆発の頂点座標
//アニメーションの処理
#define TEX_ANIM			(0.1f)					//動かすアニメ1コマの横幅(0.0～1.0)
#define TEX_PA				(9)

//弾の構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;				//位置
	D3DXMATRIX mtxWorldBullet;	//ワールドマトリックス
	int nCounterAnim;				//アニメーションのカウンター
	int nPatternAnim;				//アニメーションパターンNo.
	bool bUse;						//使用しているかどうか
} Explosion;

//グローバル宣言
LPDIRECT3DTEXTURE9 g_pTextureExplosion = NULL;					//テクスチャーへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffExplosion = NULL;				//頂点バッファへのポインタ
Explosion g_aExplosion[MAX_EXPLOSION];							//爆破の情報
int g_nCntExplosion;

//========================================================================
//爆破の初期化処理
//========================================================================
void InitExplosion(void)
{
	//変数宣言
	int nCntExplosion;

	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャを読み込む
	D3DXCreateTextureFromFile(pDevice, EXPLOSION_TEX_FILE, &g_pTextureExplosion);

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		//構造体の初期化
		g_aExplosion[nCntExplosion].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aExplosion[nCntExplosion].nCounterAnim = 0;
		g_aExplosion[nCntExplosion].nPatternAnim = 0;
		g_aExplosion[nCntExplosion].bUse = false;						//使用していない状態にする
	}

	//爆発カウントの初期化
	g_nCntExplosion = 0;

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_EXPLOSION, //←重要
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffExplosion,
		NULL);

	//頂点情報へのポインタ
	VERTEX_3D *pVtx;

	//頂点バッファをロック
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-EXPLO_SIZE, EXPLO_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(EXPLO_SIZE, EXPLO_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-EXPLO_SIZE, -EXPLO_SIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(EXPLO_SIZE, -EXPLO_SIZE, 0.0f);
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
		pVtx[1].tex = D3DXVECTOR2(0.125f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.125f, 1.0f);

		pVtx += 4;			//頂点データのポインタを4つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffExplosion->Unlock();
}
//========================================================================
//終了処理
//========================================================================
void UninitExplosion(void)
{
	//テクスチャの破棄
	if (g_pTextureExplosion != NULL)
	{
		g_pTextureExplosion->Release();
		g_pTextureExplosion = NULL;
	}
	//頂点バッファの破棄
	if (g_pVtxBuffExplosion != NULL)
	{
		g_pVtxBuffExplosion->Release();
		g_pVtxBuffExplosion = NULL;
	}

}
//========================================================================
//爆発の更新処理
//========================================================================
void UpdateExplosion(void)
{
	//頂点情報へのポインタ
	VERTEX_3D *pVtx;

	//頂点バッファをロック
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

 	for (int nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == true)
		{//爆発が使用されている
			//カウンタを進めて、パターンNo.を更新する
			g_aExplosion[nCntExplosion].nCounterAnim++;

			if ((g_aExplosion[nCntExplosion].nCounterAnim % TEX_PA) == 0)
			{
				g_aExplosion[nCntExplosion].nPatternAnim++;

				//テクスチャ座標の更新
				pVtx[0].tex = D3DXVECTOR2(g_aExplosion[nCntExplosion].nPatternAnim  * TEX_ANIM, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(g_aExplosion[nCntExplosion].nPatternAnim * TEX_ANIM + TEX_ANIM, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(g_aExplosion[nCntExplosion].nPatternAnim * TEX_ANIM, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(g_aExplosion[nCntExplosion].nPatternAnim * TEX_ANIM + TEX_ANIM, 1.0f);
			}
		}

		if (g_aExplosion[nCntExplosion].nPatternAnim >= TEX_PA)
		{
			g_aExplosion[nCntExplosion].bUse = false;
		}
		pVtx += 4;			//頂点データのポインタを4つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffExplosion->Unlock();
}
//========================================================================
//爆発の描画処理
//========================================================================
void DrawExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得
	D3DXMATRIX mtxTrans;						//計算用マトリックス
	D3DXMATRIX mtxView;							//ビューマトリックスの取得用

	//アルファテストを無効にする
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);			//アルファテストの有効/無効の設定
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);		//比較方法
	pDevice->SetRenderState(D3DRS_ALPHAREF, 10);					//基準値

	//zテストを無効にする
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);		//比較方法
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);			//zバッファ更新の有効無効設定

	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);			//アルファテストの有効/無効の設定

	for (int nCntExp = 0; nCntExp < MAX_EXPLOSION; nCntExp++)
	{
		if (g_aExplosion[nCntExp].bUse == true)
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aExplosion[nCntExp].mtxWorldBullet);

			//ビューマトリックスを取得
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//ポリゴンをカメラに対して正面に向ける
			D3DXMatrixInverse(&g_aExplosion[nCntExp].mtxWorldBullet, NULL, &mtxView);

			g_aExplosion[nCntExp].mtxWorldBullet._41 = 0.0f;
			g_aExplosion[nCntExp].mtxWorldBullet._42 = 0.0f;
			g_aExplosion[nCntExp].mtxWorldBullet._43 = 0.0f;

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aExplosion[nCntExp].pos.x, g_aExplosion[nCntExp].pos.y, g_aExplosion[nCntExp].pos.z);
			D3DXMatrixMultiply(&g_aExplosion[nCntExp].mtxWorldBullet, &g_aExplosion[nCntExp].mtxWorldBullet, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aExplosion[nCntExp].mtxWorldBullet);

			//頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffExplosion,
				0, sizeof(VERTEX_3D));			//頂点情報構造体のサイズ

												//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureExplosion);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,				//プリミティブの種類
				nCntExp * 4,						//描画する最初のインデックス
				2);						//プリミティブ(ポリゴン)数
		}
	}

	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);			//アルファテストの有効/無効の設定

	//zバッファを有効にする
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);			//zバッファ更新の有効無効設定

	//アルファテストを無効にする
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);			//アルファテストの有効/無効の設定
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);		//比較方法
	pDevice->SetRenderState(D3DRS_ALPHAREF, 10);					//基準値
}
//========================================================================
//爆発の頂点情報の設定
//========================================================================
void SetExplosion(D3DXVECTOR3 pos)
{
	//変数宣言
	int nCntExplosion;

	//頂点情報へのポインタ
	VERTEX_3D *pVtx;

	//頂点バッファをロック
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == false)
		{//爆発が使用されていない
			g_aExplosion[nCntExplosion].pos = pos;
			g_aExplosion[nCntExplosion].nCounterAnim = 0;
			g_aExplosion[nCntExplosion].nPatternAnim = 0;

			//テクスチャ座標の更新
			pVtx[0].tex = D3DXVECTOR2(g_aExplosion[nCntExplosion].nPatternAnim * TEX_ANIM, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(g_aExplosion[nCntExplosion].nPatternAnim * TEX_ANIM + TEX_ANIM, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(g_aExplosion[nCntExplosion].nPatternAnim * TEX_ANIM, 0.0f);
			pVtx[3].tex = D3DXVECTOR2(g_aExplosion[nCntExplosion].nPatternAnim * TEX_ANIM + TEX_ANIM, 0.0f);

			g_aExplosion[nCntExplosion].bUse = true;				//使用している状態にする

			break;
		}
		pVtx += 4;			//頂点データのポインタを4つ分進める
	}
	//頂点バッファをアンロックする
	g_pVtxBuffExplosion->Unlock();
}

//========================================================================
//爆発情報の取得
//========================================================================
int ExplosionCnt(void)
{
	return g_nCntExplosion;
}
