//====================================================================
//
// モデルの処理[model.h]
// Author: 小笠原彪
//
//====================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"

//プレイヤー構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;			//位置
	D3DXVECTOR3 rot;			//向き
	D3DXMATRIX mtxWorld;		//ワールドマトリックス
	D3DXVECTOR3 move;			//移動量
	int nIdxShadow;			//対象の影のインデックス(番号)
	bool bUse;					//使っているか
} Player;

//プロトタイプ宣言
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);

void DrawModelPos(void);

Player *GetPlayer(void);

#endif