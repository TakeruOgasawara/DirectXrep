//====================================================================
//
// メッシュシリンダーの処理[meshcylindwe.h]
// Author: 小笠原彪
//
//====================================================================
#ifndef _MESHCYLINDER_H_
#define _MESHCYLINDER_H_

#include "main.h"

//フィールド構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;					//位置
	D3DXVECTOR3 rot;					//向き
	D3DXMATRIX mtxWorldField;			//ワールドマトリックス
	bool bUse;							//使っているか
} MeshCylinder;

//プロトタイプ宣言
void InitMeshCylinder(void);
void UninitMeshCylinder(void);
void UpdateMeshCylinder(void);
void DrawMeshCylinder(void);

#endif