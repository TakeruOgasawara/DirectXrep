//====================================================================
//
// ポリゴンの処理[polygon.h]
// Author: 小笠原彪
//
//====================================================================
#ifndef _SHADOW_H_
#define _SHADOW_H_

#include "main.h"

//影構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;					//位置
	D3DXVECTOR3 rot;					//向き
	D3DXMATRIX mtxWorld;				//ワールドマトリックス
	bool bUse;							//使っているか
} Shadow;


//プロトタイプ宣言
void InitShadow(void);
void UninitShadow(void);
void UpdateShadow(void);
void DrawShadow(void);

int SetShadow(float  size);
void SetPositionShadow(int nIdxShadow, D3DXVECTOR3 pos);
void FalseShadow(int nFalseShadow);

#endif