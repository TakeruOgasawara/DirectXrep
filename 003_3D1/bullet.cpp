//======================================================================================
//
//弾の処理[Player.cpp]
//Author;小笠原　彪
//
//======================================================================================
#include "bullet.h"
#include "effect.h"
#include "shadow.h"
#include "explosion.h"
#include "collision.h"
#include "meshwall.h"
#include "object.h"

//マクロ定義
#define MAX_BULLET			(128)			//弾の最大数
#define NUM_BULLET			(1)				//弾の種類数
//画像のファイル名
#define BULLET_TEX_FILE		"data\\TEXTURE\\bullet000.png"

#define BULLET_SIZE			(2.0f)			//サイズ
#define BULLET_LIFE			(30000)			//弾の体力
#define BULLET_SPEED		(3.5f)			//弾のスピード

//グローバル宣言
LPDIRECT3DTEXTURE9 g_pTextureBullet[NUM_BULLET] = {};					//テクスチャ―へのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;			//頂点バッファへのポインタ
Bullet g_aBullet[MAX_BULLET];								//弾の情報
int g_nBulletCnt;				//弾の表示されている数をカウント
float g_fLengthBullet;			// 弾の対角線の長さ
float g_fAngleBullet;			// 弾の対角線の角度
D3DXVECTOR3 g_vecToPos;
D3DXVECTOR3 g_vecLine;

//========================================================================
//弾の初期化処理
//========================================================================
void InitBullet(void)
{//変数宣言
	int nCntBullet;

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//弾情報の取得
	Bullet *pBullet = GetBullet();

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++, pBullet++)
	{
		//構造体の初期化
		pBullet->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pBullet->move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pBullet->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pBullet->nLife = BULLET_LIFE;
		pBullet->nIdxShadow = -1;
		pBullet->bUse = false;				//使用していない状態にする
	}
	g_vecToPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_vecLine = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, BULLET_TEX_FILE, &g_pTextureBullet[0]);

	//対角線の長さを算出する
	g_fLengthBullet = sqrtf(BULLET_SIZEX * BULLET_SIZEX + BULLET_SIZEY * BULLET_SIZEY) * 0.5f;

	//対角線の角度を算出する
	g_fAngleBullet = atan2f(BULLET_SIZEX, BULLET_SIZEY);

	//弾カウントを初期化
	g_nBulletCnt = 0;

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_BULLET,
		D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL);

		//頂点情報へのポインタ
		VERTEX_3D *pVtx;

		//頂点バッファをロック
		g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

		for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
		{
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(-BULLET_SIZE, BULLET_SIZE, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(BULLET_SIZE, BULLET_SIZE, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-BULLET_SIZE, -BULLET_SIZE, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(BULLET_SIZE, -BULLET_SIZE, 0.0f);
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

			pVtx += 4;			//頂点データのポインタを4つ分進める
		}
		//頂点バッファをアンロックする
		g_pVtxBuffBullet->Unlock();
}

//========================================================================
//弾の終了処理
//========================================================================
void UninitBullet(void)
{
	//変数宣言
	int nCntTex;			//テクスチャ―のカウント

	for (nCntTex = 0; nCntTex < NUM_BULLET; nCntTex++)
	{
		//テクスチャの破棄
		if (g_pTextureBullet[nCntTex] != NULL)
		{
			g_pTextureBullet[nCntTex]->Release();
			g_pTextureBullet[nCntTex] = NULL;
		}
	}
	//頂点バッファの破棄
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}
}

//========================================================================
//弾の更新処理
//========================================================================
void UpdateBullet(void)
{
	//頂点情報へのポインタ
	VERTEX_3D *pVtx;

	//変数宣言
	int nCntBullet;
	float vec;

	//ポインタ情報の取得
	Bullet *pBullet = GetBullet();
	MeshWall *pMeshWall = GetMeshWall();
	Object *pObject = GetObj();

	//頂点バッファをロック
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	//全ての弾をチェック
	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++, pBullet++)
	{
		if (pBullet->bUse == true)
		{//弾が使用されている
			//弾の位置の更新
			pBullet->pos += pBullet->move;
			//エフェクトの設定
			SetEffect(pBullet->pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 5.0f, 100);

			//寿命のカウントダウン
 			pBullet->nLife--;

			if (pBullet->nLife <= 0)
			{//寿命が終わったら
				//使用していない状態にする
				pBullet->bUse = false;
				FalseShadow(pBullet->nIdxShadow);			//影を消す
				SetExplosion(pBullet->pos);
			}

			//大人の壁と弾の当たり判定
			if (CollisionAdultWall(&pBullet->pos, 0.0f) == true)
			{
				pBullet->bUse = false;
				FalseShadow(pBullet->nIdxShadow);			//影を消す
				SetExplosion(pBullet->pos);
			}

			//オブジェクトとの当たり判定
			if (pObject->vtxMaxObj.x >= pBullet->pos.x && pObject->vtxMinObj.x <= pBullet->pos.x &&
				pObject->vtxMaxObj.z >= pBullet->pos.z && pObject->vtxMinObj.z <= pBullet->pos.z)
			{
				pBullet->bUse = false;
				FalseShadow(pBullet->nIdxShadow);			//影を使っていない状態へ
				SetExplosion(pBullet->pos);					//爆発を使用する
			}

			//外積の当たり判定//
			g_vecLine = (pMeshWall->pos + D3DXVECTOR3(200.0f, 0.0f, 0.0f) - (pMeshWall->pos + D3DXVECTOR3(-200.0f, 0.0f, 0.0f)));

			g_vecToPos = pBullet->pos - pMeshWall->pos;
			
			vec = (g_vecLine.z * g_vecToPos.x) - (g_vecLine.x * g_vecToPos.z);

			if (vec < 0)
			{
				pBullet->bUse = false;						//使っていない状態へ
				FalseShadow(pBullet->nIdxShadow);			//影を使っていない状態へ
				SetExplosion(pBullet->pos);					//爆発を使用する
			}

			//影の位置を設定
			SetPositionShadow(pBullet->nIdxShadow, pBullet->pos);
		}
		pVtx += 4;			//頂点データのポインタを4つ分進める
	}
	//頂点バッファをアンロックする
	g_pVtxBuffBullet->Unlock();
}

//========================================================================
//弾の描画処理
//========================================================================
void DrawBullet(void)
{
	//弾情報の取得
	Bullet *pBullet = GetBullet();
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得
	D3DXMATRIX mtxTrans;						//計算用マトリックス
	D3DXMATRIX mtxView;							//ビューマトリックスの取得用

	//弾の数を初期化
	g_nBulletCnt = 0;

	//アルファテストを無効にする
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);			//アルファテストの有効/無効の設定
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);		//比較方法
	pDevice->SetRenderState(D3DRS_ALPHAREF, 10);					//基準値

	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);			//ライティングの有効/無効の設定

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++, pBullet++)
	{
		if (pBullet->bUse == true)
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&pBullet->mtxWorldBullet);

			//ビューマトリックスを取得
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//ポリゴンをカメラに対して正面に向ける
			D3DXMatrixInverse(&pBullet->mtxWorldBullet, NULL, &mtxView);

			pBullet->mtxWorldBullet._41 = 0.0f;
			pBullet->mtxWorldBullet._42 = 0.0f;
			pBullet->mtxWorldBullet._43 = 0.0f;

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, pBullet->pos.x, pBullet->pos.y, pBullet->pos.z);
			D3DXMatrixMultiply(&pBullet->mtxWorldBullet, &pBullet->mtxWorldBullet, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &pBullet->mtxWorldBullet);

			//頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffBullet,
				0, sizeof(VERTEX_3D));			//頂点情報構造体のサイズ

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureBullet[0]);

			//ポリゴンの描画
 			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,				//プリミティブの種類
				nCntBullet * 4,						//描画する最初のインデックス
				2);						//プリミティブ(ポリゴン)数

			//弾数のカウント
			g_nBulletCnt++;
		}
	}

	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);			//ライティングの有効/無効の設定

	//アルファテストを無効にする
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);			//アルファテストの有効/無効の設定
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);		//比較方法
	pDevice->SetRenderState(D3DRS_ALPHAREF, 10);					//基準値
}

//========================================================================
//弾の設定処理
//========================================================================
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife, BULLETTYPE type)
{
	//変数宣言
	int nCntBullet;

	//弾情報の取得
	Bullet *pBullet = GetBullet();

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++, pBullet++)
	{
		if (pBullet->bUse == false)
		{//弾が使用されていない
			//それぞれの取得
			pBullet->pos = pos;						//位置
			pBullet->type = type;					//種類
			pBullet->nLife = nLife;					//寿命
			pBullet->move = move * BULLET_SPEED;	//移動量

			//使用している状態にする
			pBullet->bUse = true;

			//影の位置を設定
			pBullet->nIdxShadow = SetShadow(BULLET_SIZE);

			break;
		}
	}
}

//===================================================
// デバッグ表記
//===================================================
void DrawDebug(void)
{
	RECT rect = { 0, 680, SCREEN_WIDTH, SCREEN_HEIGHT };
	char aStr[256];

	int  nCntBullet = BulletCnt();
	LPD3DXFONT pFont = GetFont();

	//文字列を代入
	wsprintf(&aStr[0], "%d", nCntBullet);

	//テキスト描画
	pFont->DrawTextA(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}

//==================================================================================================
//ポインタ取得
//==================================================================================================
Bullet *GetBullet(void)
{
	return &g_aBullet[0];
}

//========================================================================
//弾数を取得
//========================================================================
int BulletCnt(void)
{
	return g_nBulletCnt;
}

