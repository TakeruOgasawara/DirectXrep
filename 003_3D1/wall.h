//====================================================================
//
// ポリゴンの処理[polygon.h]
// Author: 小笠原彪
//
//====================================================================
#ifndef _WALL_H_
#define _WALL_H_

#include "main.h"

//壁構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;					//位置
	D3DXVECTOR3 rot;					//向き
	D3DXMATRIX mtxWorldWall;			//ワールドマトリックス
	bool bUse;							//使っているか
} Wall;

//プロトタイプ宣言
void InitWall(void);
void UninitWall(void);
void UpdateWall(void);
void DrawWall(void);
void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

#endif