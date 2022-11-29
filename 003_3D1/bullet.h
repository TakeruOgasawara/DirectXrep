//======================================================================================
//
//弾の処理[Player.h]
//Author;小笠原　彪
//
//======================================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"

#define SCREEN_RIGHT		(640)			//画面右側の当たり判定

//======敵設定======//
#define BULLET_SIZEX		(20.0f)			//敵のサイズX
#define BULLET_SIZEY		(20.0f)			//敵のサイズY

//弾の種類(種類を増やしたいならここ↓)
typedef enum
{
	BULLETTYPE_PLAYER = 0,			//プレイヤーの弾
	BULLETTYPE_STAGE1,				//ステージ1の敵が使う
	BULLETTYPE_MAX
}BULLETTYPE;

//弾の構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;				//位置
	D3DXVECTOR3 move;				//移動量
	D3DXVECTOR3 rot;				//向き
	D3DXMATRIX mtxWorldBullet;	//ワールドマトリックス
	BULLETTYPE type;				//種類
	int nLife;						//寿命
	int nIdxShadow;					//対象の影のインデックス(番号)
	bool bUse;						//使用しているかどうか
} Bullet;

//プロトタイプ宣言
void InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife, BULLETTYPE type);
int BulletCnt(void);
void DrawDebug(void);
Bullet *GetBullet(void);

#endif
