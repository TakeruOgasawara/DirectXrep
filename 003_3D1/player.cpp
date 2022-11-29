//======================================================================================
//
// プレイヤーの処理[model.cpp]
// Author;小笠原　彪
//
//======================================================================================
#include <stdio.h>
#include "player.h"
#include "input.h"
#include "shadow.h"
#include "camera.h"
#include "bullet.h"
#include "wall.h"
#include "collision.h"
#include "object.h"

//マクロ定義
#define MODEL_SPEED			(1.7f)			//モデルの移動速度
#define MODEL_ATT			(0.2f)			//モデルの減衰

//プロトタイプ宣言
void PlayerOps(void);
void ColliObj(void);

//グローバル宣言
LPDIRECT3DTEXTURE9 g_pTexturePlayer[8] = {};
LPD3DXMESH g_pMeshPlayer = NULL;
LPD3DXBUFFER g_pBuffMatPlayer = NULL;
DWORD g_dwNumMatPlayer = 0;
Player g_player;

int g_nIdxShadow = -1;			//対象の影のインデックス(番号)

//====================================================================
// モデルの初期化処理
//====================================================================
void InitPlayer(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//グローバル宣言の初期化
	g_player.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//Xファイルの読み込み
	D3DXLoadMeshFromX("data\\MODEL\\model000.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatPlayer,
		NULL,
		&g_dwNumMatPlayer,
		&g_pMeshPlayer);

	D3DXMATERIAL *pMat;			//マテリアルへのポインタ

	//マテリアルへのポインタを取得
	pMat = (D3DXMATERIAL*)g_pBuffMatPlayer->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_dwNumMatPlayer; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{//ファイルからテクスチャを読み込む
			D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\wood000.png", &g_pTexturePlayer[2]);
			D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\sumi.jpg", &g_pTexturePlayer[3]);
		}
	}

	//影の位置を設定
	g_nIdxShadow = SetShadow(10.0f);
}

//====================================================================
// モデルの終了処理
//====================================================================
void UninitPlayer(void)
{
	//メッシュの破棄
	if (g_pMeshPlayer != NULL)
	{
		g_pMeshPlayer->Release();
		g_pMeshPlayer = NULL;
	}
	//マテリアルの破棄
	if (g_pBuffMatPlayer != NULL)
	{
		g_pBuffMatPlayer->Release();
		g_pBuffMatPlayer = NULL;
	}
}

//====================================================================
// モデルの更新処理
//====================================================================
void UpdatePlayer(void)
{
	PlayerOps();

	ColliObj();

	//移動量を更新(減衰させる)
	g_player.move.x += (0.0f - g_player.move.x) * MODEL_ATT;
	g_player.move.y += (0.0f - g_player.move.y) * MODEL_ATT;
	g_player.move.z += (0.0f - g_player.move.z) * MODEL_ATT;

	//プレイヤー位置の更新
	g_player.pos += g_player.move;

	//大人の壁との当たり判定
	CollisionAdultWall(&g_player.pos, 10.0f);
	
	//影の位置を設定
	SetPositionShadow(g_nIdxShadow, g_player.pos);
}

void ColliObj(void)
{
	Object *pObject = GetObj();

	for (int nCnt = 0; nCnt < 1; nCnt++, pObject++)
	{
		//オブジェクトとの当たり判定
		if (pObject->vtxMaxObj.x >= g_player.pos.x && pObject->vtxMinObj.x <= g_player.pos.x &&
			pObject->vtxMaxObj.z >= g_player.pos.z && pObject->vtxMinObj.z <= g_player.pos.z)
		{
			g_player.pos.x = 100.0f;
		}
	}
}

//====================================================================
// プレイヤーの操作
//====================================================================
void PlayerOps(void)
{
	//変数宣言
	float fRotDest = g_player.rot.y;			//目標の角度
	float fRotDiff = 0.0f;					//目標と現在の差分

	Camera camera = GetCamera();

	//キー入力で移動する処理
	if (GetKeyboardPress(DIK_A) == true)
	{//Aキーが押された
		if (GetKeyboardPress(DIK_W) == true)
		{
			fRotDest = camera.rot.y + D3DX_PI * 0.75f;

			//左上移動
			g_player.move.x += sinf(camera.rot.y + -D3DX_PI * 0.25f) * MODEL_SPEED;
			g_player.move.z += cosf(camera.rot.y + -D3DX_PI * 0.25f) * MODEL_SPEED;
		}
		else if (GetKeyboardPress(DIK_S) == true)
		{
			fRotDest = camera.rot.y + D3DX_PI * 0.25f;

			//左下移動
			g_player.move.x += sinf(camera.rot.y + -D3DX_PI * 0.75f) * MODEL_SPEED;
			g_player.move.z += cosf(camera.rot.y + -D3DX_PI * 0.75f) * MODEL_SPEED;
		}
		else
		{
			fRotDest = camera.rot.y + D3DX_PI * 0.5f;

			g_player.move.x += sinf(camera.rot.y + -D3DX_PI * 0.5f) * MODEL_SPEED;
			g_player.move.z += cosf(camera.rot.y + -D3DX_PI * 0.5f) * MODEL_SPEED;
		}
	}
	else if (GetKeyboardPress(DIK_D) == true)
	{//Dキーが押された
		if (GetKeyboardPress(DIK_W) == true)
		{
			fRotDest = camera.rot.y + -D3DX_PI * 0.75f;

			//右上移動
			g_player.move.x += sinf(camera.rot.y + D3DX_PI * 0.25f) * MODEL_SPEED;
			g_player.move.z += cosf(camera.rot.y + D3DX_PI * 0.25f) * MODEL_SPEED;
		}
		else if (GetKeyboardPress(DIK_S) == true)
		{
			fRotDest = camera.rot.y + -D3DX_PI * 0.25f;

			//右下移動
			g_player.move.x += sinf(camera.rot.y + D3DX_PI * 0.75f) * MODEL_SPEED;
			g_player.move.z += cosf(camera.rot.y + D3DX_PI * 0.75f) * MODEL_SPEED;
		}
		else
		{
			fRotDest = camera.rot.y + -D3DX_PI * 0.5f;

			g_player.move.x += sinf(camera.rot.y + D3DX_PI * 0.5f) * MODEL_SPEED;
			g_player.move.z += cosf(camera.rot.y + D3DX_PI * 0.5f) * MODEL_SPEED;
		}
	}
	else if (GetKeyboardPress(DIK_W) == true)
	{//Wキーが押された
		fRotDest = camera.rot.y + -D3DX_PI;

		g_player.move.x += sinf(camera.rot.y + 0.0f) * MODEL_SPEED;
		g_player.move.z += cosf(camera.rot.y + 0.0f) * MODEL_SPEED;
	}
	else if (GetKeyboardPress(DIK_S) == true)
	{//Sキーが押された
		fRotDest = camera.rot.y;

		g_player.move.x += sinf(camera.rot.y + D3DX_PI) * MODEL_SPEED;
		g_player.move.z += cosf(camera.rot.y + D3DX_PI) * MODEL_SPEED;
	}

	if (GetKeyboardPress(DIK_LSHIFT) == true)
	{//Sキーが押された
		g_player.rot.y += 0.3f;

		g_player.pos.z = g_player.pos.z + (sinf(g_player.rot.y) * sinf(g_player.rot.x));
		g_player.pos.x = g_player.pos.x + (sinf(g_player.rot.y) * cosf(g_player.rot.x));
	}
	if (GetKeyboardPress(DIK_RSHIFT) == true)
	{//Sキーが押された
		g_player.rot.y -= 0.3f;

		g_player.pos.z = g_player.pos.z + (sinf(g_player.rot.y) * sinf(g_player.rot.x));
		g_player.pos.x = g_player.pos.x + (sinf(g_player.rot.y) * cosf(g_player.rot.x));
	}

	if (GetKeyboardTrigger(DIK_SPACE) == true)
	{//弾を撃つ
		SetBullet(D3DXVECTOR3(g_player.pos.x, g_player.pos.y + 2.0f, g_player.pos.z - 5.0f), D3DXVECTOR3(-sinf(g_player.rot.y), 0.0f, -cosf(g_player.rot.y)), 1000, BULLETTYPE_PLAYER);
	}

	fRotDiff = fRotDest - g_player.rot.y;			//目標の角度までの差分を求める

	if (fRotDiff > D3DX_PI)
	{
		fRotDiff -= 6.28f;
	}
	if (fRotDiff < -D3DX_PI)
	{
		fRotDiff += 6.28f;
	}

	g_player.rot.y += fRotDiff * 0.1f;			//補正する

												//向きが3.14以上-3.14以下に行かないようにする
	if (g_player.rot.y > D3DX_PI)
	{
		g_player.rot.y = -D3DX_PI;
	}
	if (g_player.rot.y < -D3DX_PI)
	{
		g_player.rot.y = D3DX_PI;
	}
}

//====================================================================
// モデルの描画処理
//====================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;				//計算用マトリックス
	D3DMATERIAL9 matDef;						//現在のマテリアル保存用
	D3DXMATERIAL *pMat;							//マテリアルデータへのポインタ

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_player.mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_player.rot.y, g_player.rot.x, g_player.rot.z);

	D3DXMatrixMultiply(&g_player.mtxWorld, &g_player.mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_player.pos.x, g_player.pos.y, g_player.pos.z);

	D3DXMatrixMultiply(&g_player.mtxWorld, &g_player.mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_player.mtxWorld);

	//現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	//マテリアルへのポインタを取得
	pMat = (D3DXMATERIAL*) g_pBuffMatPlayer->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_dwNumMatPlayer; nCntMat++)
	{
		//マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//テクスチャの設定
		pDevice->SetTexture(0, g_pTexturePlayer[nCntMat]);

		//モデル(パーツ)の描画
		g_pMeshPlayer->DrawSubset(nCntMat);
	}

	//保存されていたマテリアルを戻す
	pDevice->SetMaterial(&matDef);
}

//===================================================
// モデル位置の表示
//===================================================
void DrawModelPos(void)
{
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	char aStr[256];

	Player *pPlayer = GetPlayer();
	LPD3DXFONT pFont = GetFont();

	//文字列を代入
	sprintf(&aStr[0], "モデル位置：[%0.2f, %0.2f, %0.2f]\nモデルの移動量：[%0.4f, %0.4f, %0.4f]", pPlayer->pos.x, pPlayer->pos.y, pPlayer->pos.z, pPlayer->move.x, pPlayer->move.y, pPlayer->move.z);

	//テキスト描画
	pFont->DrawTextA(NULL, &aStr[0], -1, &rect, DT_RIGHT, D3DCOLOR_RGBA(255, 255, 255, 255));
}


//====================================================================
// プレイヤー情報の取得
//====================================================================
Player *GetPlayer(void)
{
	return &g_player;
}