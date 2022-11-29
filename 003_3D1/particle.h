//======================================================================================
//
//パーティクルの処理[Player.h]
//Author;小笠原　彪
//
//======================================================================================
#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include "main.h"

//パーティクルの種類
typedef enum
{
	PARTICLE_TYPE_NONE = 0,								//マズルフラッシュ
	PARTICLE_TYPE_EXPLO,							//爆発
	PARTICLE_TYPE_MAX
}PARTICLE_TYPE;

//パーティクル構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;				//位置
	D3DXVECTOR3 move;				//移動量
	D3DXVECTOR3 rot;				//向き
	D3DXCOLOR col;					//色
	PARTICLE_TYPE type;			//種類
	float fRadius;					//半径(大きさ)
	int nLife;						//寿命
	bool bUse;						//使用しているかどうか
}Particle;

//プロトタイプ宣言
void InitParticle(void);
void UninitParticle(void);
void UpdateParticle(void);
void DrawParticle(void);
void SetParticle(D3DXVECTOR3 pos, D3DXVECTOR3 rot, PARTICLE_TYPE type);

#endif