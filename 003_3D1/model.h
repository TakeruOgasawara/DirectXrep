//====================================================================
//
// モデルの処理[model.h]
// Author: 小笠原彪
//
//====================================================================
#ifndef _MODEL_H_
#define _MODEL_H_

#include "main.h"

//プロトタイプ宣言
void InitModel(void);
void UninitModel(void);
void UpdateModel(void);
void DrawModel(void);
D3DXVECTOR3 GetModel(void);

#endif