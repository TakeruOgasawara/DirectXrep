//====================================================================
//
// カメラの処理[camera.h]
// Author: 小笠原彪
//
//====================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"

//カメラ構造体の定義
typedef struct
{
	D3DXVECTOR3 posV;			//視点
	D3DXVECTOR3 posR;			//注視点
	D3DXVECTOR3 posVDest;		//目的の視点
	D3DXVECTOR3 posRDest;		//目的の注視点
	D3DXVECTOR3 vecU;			//上方向ベクトル
	D3DXMATRIX mtxProjection;	//プロジェクションマトリックス
	D3DXMATRIX mtxView;			//ビューマトリックス
	D3DXVECTOR3 move;			//移動量
	D3DXVECTOR3 rot;			//向き
	float fLengthCamera;		//長さ
} Camera;

//プロトタイプ宣言
void InitCamera(void);
void UninitCamera(void);
void UpdateCamera(void);

void SetCamera(void);
void CameraAuto(void);			//カメラを背面へ活かせる処理

void DrawCameraOps(void);		//カメラの操作説明
void DrawCameraPos(void);		//カメラ視点位置の表示

Camera GetCamera(void);


#endif
