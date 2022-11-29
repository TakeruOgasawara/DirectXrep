//======================================================================================
//
//パーティクルの処理[Player.cpp]
//Author;小笠原　彪
//
//======================================================================================
#include "main.h"
#include "particle.h"
#include "effect.h"

//マクロ定義
#define MAX_PARTICLE			(128)			//パーティクルの最大数

//グローバル宣言
Particle g_aParticle[MAX_PARTICLE];			//パーティクルの情報

//========================================================================
//パーティクルの初期化処理
//========================================================================
void InitParticle(void)
{
	//変数宣言
	int nCntParticle;

	for (nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		//構造体の初期化
		g_aParticle[nCntParticle].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aParticle[nCntParticle].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//移動量を初期化する
		g_aParticle[nCntParticle].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//向きを初期化する(Z値を使用)
		g_aParticle[nCntParticle].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_aParticle[nCntParticle].type = PARTICLE_TYPE_NONE;
		g_aParticle[nCntParticle].fRadius = 0.0f;
		g_aParticle[nCntParticle].nLife = 0;
		g_aParticle[nCntParticle].bUse = false;				//使用していない状態にする
	}
}

//========================================================================
//パーティクルの終了処理
//========================================================================
void UninitParticle(void)
{

}

//========================================================================
//パーティクルの更新処理
//========================================================================
void UpdateParticle(void)
{
	//変数宣言
	int nCntParticle;
	float fRot;
	float fMove;

	for (nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		if (g_aParticle[nCntParticle].bUse == true)
		{
			for (int nCntApper = 0; nCntApper < 20; nCntApper++)
			{
				//位置の設定
				g_aParticle[nCntParticle].pos;

				switch (g_aParticle[nCntParticle].type)
				{//タイプによって分ける
				case PARTICLE_TYPE_EXPLO:

					//移動方向の設定
					fRot = rand() % 629 - 314 / 50.0f;

					//移動量の設定
					fMove = (float)(rand() % 100) / 10 + 500;

					g_aParticle[nCntParticle].move.x = sinf(fRot) * fMove;
					g_aParticle[nCntParticle].move.y = cosf(fRot) * fMove;

					//色の設定
					g_aParticle[nCntParticle].col = D3DXCOLOR{ 1.0f,0.6f,0.0f,1.0f };

					//半径の設定
					g_aParticle[nCntParticle].fRadius = 5.0f;

					//エフェクト設定
					SetEffect(g_aParticle[nCntParticle].pos, g_aParticle[nCntParticle].move,
						g_aParticle[nCntParticle].col, g_aParticle[nCntParticle].fRadius, g_aParticle[nCntParticle].nLife);
				}

				if (g_aParticle[nCntParticle].nLife >= 0)
				{//寿命が0以上の時
					g_aParticle[nCntParticle].nLife--;			//減算
				}
			}

			if (g_aParticle[nCntParticle].nLife <= 0)
			{//寿命が尽きた時
				g_aParticle[nCntParticle].bUse = false;			//使っていない状態へ
			}
		}
	}
}

//========================================================================
//パーティクルの描画処理
//========================================================================
void DrawParticle(void)
{

}

//========================================================================
//パーティクルの設定処理
//========================================================================
void SetParticle(D3DXVECTOR3 pos, D3DXVECTOR3 rot, PARTICLE_TYPE type)
{
	for (int nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		if (g_aParticle[nCntParticle].bUse == false)
		{//使用していない状態なら
			g_aParticle[nCntParticle].pos = pos;
			g_aParticle[nCntParticle].rot = rot;
			g_aParticle[nCntParticle].type = type;
			g_aParticle[nCntParticle].bUse = true;

			switch (g_aParticle[nCntParticle].type)
			{//タイプによる分岐
			case PARTICLE_TYPE_EXPLO:
				g_aParticle[nCntParticle].nLife = 100;
				break;
			}

			break;
		}
	}
}
