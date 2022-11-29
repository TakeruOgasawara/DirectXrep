//====================================================================
//
// モデルの処理[object.h]
// Author: 小笠原彪
//
//====================================================================
#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "main.h"

//マクロ定義
#define MAX_OBJTEX				(10)			//テクスチャのかず


//オブジェクト構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;					//位置
	D3DXVECTOR3 rot;					//向き
	D3DXVECTOR3 move;					//移動量
	D3DXVECTOR3 vtxMinObj, vtxMaxObj;	//オブジェクトの最大値・最小値
	D3DXMATRIX mtxWorld;				//ワールドマトリックス
	int nIdxShadow;						//対象の影のインデックス(番号)
	int nType;							//種類
	bool bUse;							//使っているか
} Object;

typedef struct
{
	LPDIRECT3DTEXTURE9 pTexture[MAX_OBJTEX];
} Obj;

//プロトタイプ宣言
void InitObject(void);
void UninitObject(void);
void UpdateObject(void);
void DrawObject(void);
void SetObject(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType);
Object *GetObj(void);

#endif