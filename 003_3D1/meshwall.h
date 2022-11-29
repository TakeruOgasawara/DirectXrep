//====================================================================
//
// メッシュウォールの処理[field.h]
// Author: 小笠原彪
//
//====================================================================
#ifndef _MESHWALL_H_
#define _MESHWALL_H_

#include "main.h"

//フィールド構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;					//位置
	D3DXVECTOR3 rot;					//向き
	D3DXMATRIX mtxWorldField;			//ワールドマトリックス
	bool bUse;							//使っているか
} MeshWall;

//プロトタイプ宣言
void InitMeshWall(void);
void UninitMeshWall(void);
void UpdateMeshWall(void);
void DrawMeshWall(void);
void SetMeshWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
MeshWall *GetMeshWall(void);

#endif