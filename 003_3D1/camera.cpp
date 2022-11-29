//======================================================================================
//
// カメラの処理[camera.cpp]
// Author;小笠原　彪
//
//======================================================================================
#include <stdio.h>
#include "camera.h"
#include "input.h"
#include "player.h"

//マクロ定義
#define CAMERA_SPEED		(0.9f)			//カメラの速度
#define CAMERA_DISTANCE		(200.0f)		//視点と注視点の距離
#define CAMELA_AUTO			(0.0001f)		//カメラが後ろに回る時の慣性

//プロトタイプ宣言
void CameraOps(void);			//カメラ操作の処理
void CameraV(void);				//視点操作の処理
void CameraR(void);				//注視点操作の処理
void Camerafollow(void);		//カメラ追従の処理

//グローバル宣言
Camera g_camera;			//カメラ情報

//====================================================================
// カメラの初期化処理
//====================================================================
void InitCamera(void)
{
	//変数の初期化
	g_camera.posV = D3DXVECTOR3(0.0f, 200.0f, -50.0f);			//視点
	g_camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//注視点
	g_camera.vecU = D3DXVECTOR3(0.0, 1.0f, 0.0f);				//上方向ベクトル

	g_camera.posVDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//目的の視点
	g_camera.posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//目的の注視点

	g_camera.rot = D3DXVECTOR3(0.0f, 0.0f, -0.55f);				//向き

	g_camera.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//移動量

	g_camera.fLengthCamera = 230.0f;			//注視点から視点間の距離
}

//====================================================================
//カメラの終了処理処理
//====================================================================
void UninitCamera(void)
{

}

//====================================================================
//カメラの更新処理
//====================================================================
void UpdateCamera(void)
{
	//カメラの操作が入ってる関数
	CameraOps();
}

//====================================================================
//カメラの操作
//====================================================================
void CameraOps(void)
{
	Player *pPlayer = GetPlayer();

	//八方向移動
	//if (GetKeyboardPress(DIK_A) == true)
	//{//Aキーが押された
	//	if (GetKeyboardPress(DIK_W) == true)
	//	{//左上移動
	//		g_camera.posV.x += sinf(g_camera.rot.y + -D3DX_PI * 0.25f) * CAMERA_SPEED;
	//		g_camera.posR.x += sinf(g_camera.rot.y + -D3DX_PI * 0.25f) * CAMERA_SPEED;
	//		g_camera.posV.z += cosf(g_camera.rot.y + -D3DX_PI * 0.25f) * CAMERA_SPEED;
	//		g_camera.posR.z += cosf(g_camera.rot.y + -D3DX_PI * 0.25f) * CAMERA_SPEED;
	//	}
	//	else if (GetKeyboardPress(DIK_S) == true)
	//	{//左下移動
	//		g_camera.posV.x += sinf(g_camera.rot.y + -D3DX_PI * 0.75f) * CAMERA_SPEED;
	//		g_camera.posR.x += sinf(g_camera.rot.y + -D3DX_PI * 0.75f) * CAMERA_SPEED;
	//		g_camera.posV.z += cosf(g_camera.rot.y + -D3DX_PI * 0.75f) * CAMERA_SPEED;
	//		g_camera.posR.z += cosf(g_camera.rot.y + -D3DX_PI * 0.75f) * CAMERA_SPEED;
	//	}
	//	else
	//	{//左移動
	//		//カメラ位置情報の更新
	//		g_camera.posV.x += sinf(g_camera.rot.y + -D3DX_PI * 0.5f) * CAMERA_SPEED;
	//		g_camera.posR.x += sinf(g_camera.rot.y + -D3DX_PI * 0.5f) * CAMERA_SPEED;
	//		g_camera.posV.z += cosf(g_camera.rot.y + -D3DX_PI * 0.5f) * CAMERA_SPEED;
	//		g_camera.posR.z += cosf(g_camera.rot.y + -D3DX_PI * 0.5f) * CAMERA_SPEED;
	//	}
	//}
	//else if (GetKeyboardPress(DIK_D) == true)
	//{//Dキーが押された
	//	if (GetKeyboardPress(DIK_W) == true)
	//	{//右上移動
	//		g_camera.posV.x += sinf(g_camera.rot.y + D3DX_PI * 0.25f) * CAMERA_SPEED;
	//		g_camera.posR.x += sinf(g_camera.rot.y + D3DX_PI * 0.25f) * CAMERA_SPEED;
	//		g_camera.posV.z += cosf(g_camera.rot.y + D3DX_PI * 0.25f) * CAMERA_SPEED;
	//		g_camera.posR.z += cosf(g_camera.rot.y + D3DX_PI * 0.25f) * CAMERA_SPEED;
	//	}
	//	else if (GetKeyboardPress(DIK_S) == true)
	//	{//右下移動
	//		g_camera.posV.x += sinf(g_camera.rot.y + D3DX_PI * 0.75f) * CAMERA_SPEED;
	//		g_camera.posR.x += sinf(g_camera.rot.y + D3DX_PI * 0.75f) * CAMERA_SPEED;
	//		g_camera.posV.z += cosf(g_camera.rot.y + D3DX_PI * 0.75f) * CAMERA_SPEED;
	//		g_camera.posR.z += cosf(g_camera.rot.y + D3DX_PI * 0.75f) * CAMERA_SPEED;
	//	}
	//	else
	//	{//右移動
	//		//カメラ位置情報の更新
	//		g_camera.posV.x += sinf(g_camera.rot.y + D3DX_PI * 0.5f) * CAMERA_SPEED;
	//		g_camera.posR.x += sinf(g_camera.rot.y + D3DX_PI * 0.5f) * CAMERA_SPEED;
	//		g_camera.posV.z += cosf(g_camera.rot.y + D3DX_PI * 0.5f) * CAMERA_SPEED;
	//		g_camera.posR.z += cosf(g_camera.rot.y + D3DX_PI * 0.5f) * CAMERA_SPEED;
	//	}
	//}
	//else if (GetKeyboardPress(DIK_W) == true)
	//{//Wキーが押された
	//	//上移動
	//	g_camera.posV.x += sinf(g_camera.rot.y) * CAMERA_SPEED;
	//	g_camera.posR.x += sinf(g_camera.rot.y) * CAMERA_SPEED;
	//	g_camera.posV.z += cosf(g_camera.rot.y) * CAMERA_SPEED;
	//	g_camera.posR.z += cosf(g_camera.rot.y) * CAMERA_SPEED;
	//}
	//else if (GetKeyboardPress(DIK_S) == true)
	//{//Sキーが押された
	//	//下移動
	//	g_camera.posV.x += sinf(g_camera.rot.y + D3DX_PI) * CAMERA_SPEED;
	//	g_camera.posR.x += sinf(g_camera.rot.y + D3DX_PI) * CAMERA_SPEED;
	//	g_camera.posV.z += cosf(g_camera.rot.y + D3DX_PI) * CAMERA_SPEED;
	//	g_camera.posR.z += cosf(g_camera.rot.y + D3DX_PI) * CAMERA_SPEED;
	//}

	//カメラの追従
	Camerafollow();

	//視点操作
	CameraV();

	//注視点移動
	CameraR();

	//if (pPlayer->move.x <= CAMELA_AUTO && pPlayer->move.y <= CAMELA_AUTO && pPlayer->move.z <= CAMELA_AUTO &&
	//	pPlayer->move.x >= -CAMELA_AUTO && pPlayer->move.y >= -CAMELA_AUTO && pPlayer->move.z >= -CAMELA_AUTO)
	//{//カメラを背後に回す処理
	//	CameraAuto();
	//}
	
	//向きが3.14以上-3.14以下に行かないようにする
	//y
	if (g_camera.rot.y > D3DX_PI)
	{
		g_camera.rot.y = -D3DX_PI;
	}
	if (g_camera.rot.y < -D3DX_PI)
	{
		g_camera.rot.y = D3DX_PI;
	}
	//z
	if (g_camera.rot.z > D3DX_PI)
	{
		g_camera.rot.z = -D3DX_PI;
	}
	if (g_camera.rot.z < -D3DX_PI)
	{
		g_camera.rot.z = D3DX_PI;
	}
	//x
	if (g_camera.rot.x > D3DX_PI)
	{
		g_camera.rot.x = -D3DX_PI;
	}
	if (g_camera.rot.x < -D3DX_PI)
	{
		g_camera.rot.x = D3DX_PI;
	}
}

//====================================================================
// カメラ視点の移動処理
//====================================================================
void CameraV(void)
{
	//ポインタ情報の取得
	Player *pPlayer = GetPlayer();

	//縦回転
	if (GetKeyboardPress(DIK_Y) == true)
	{//Yキーが押された
		g_camera.rot.z -= 0.05f;
	}
	else if (GetKeyboardPress(DIK_N) == true)
	{//Nキーが押された
		g_camera.rot.z += 0.05f;
	}
	//横回転
	if (GetKeyboardPress(DIK_Z) == true)
	{//Zキーが押された
		g_camera.rot.y += 0.05f;
	}
	else if (GetKeyboardPress(DIK_C) == true)
	{//Cキーが押された
		g_camera.rot.y -= 0.05f;
	}

	g_camera.posVDest.x = pPlayer->pos.x + (cosf(g_camera.rot.z) * sinf(g_camera.rot.y)) * -g_camera.fLengthCamera;
	g_camera.posVDest.y = pPlayer->pos.y + sinf(g_camera.rot.z) * -g_camera.fLengthCamera;			//視点Y
	g_camera.posVDest.z = pPlayer->pos.z + (cosf(g_camera.rot.z) * cosf(g_camera.rot.y)) * -g_camera.fLengthCamera;
}

//====================================================================
// カメラ注視点の移動処理
//====================================================================
void CameraR(void)
{
	//縦回転
	if (GetKeyboardPress(DIK_T) == true)
	{//Tキーが押された
		g_camera.rot.z += 0.05f;
	}
	else if (GetKeyboardPress(DIK_B) == true)
	{//Bキーが押された
		g_camera.rot.z -= 0.05f;
	}
	//横回転
	if (GetKeyboardPress(DIK_Q) == true)
	{//Qキーが押された
		g_camera.rot.y -= 0.05f;
	}
	else if (GetKeyboardPress(DIK_E) == true)
	{//Eキーが押された
		g_camera.rot.y += 0.05f;
	}

	g_camera.posRDest.x = g_camera.posVDest.x + (cosf(g_camera.rot.z) * sinf(g_camera.rot.y)) * g_camera.fLengthCamera;
	g_camera.posRDest.y = g_camera.posVDest.y + sinf(g_camera.rot.z) * g_camera.fLengthCamera;			//視点Y
	g_camera.posRDest.z = g_camera.posVDest.z + (cosf(g_camera.rot.z) * cosf(g_camera.rot.y)) * g_camera.fLengthCamera;
}

//====================================================================
// カメラの追従処理
//====================================================================
void Camerafollow(void)
{
	//ポインタ情報の取得
	Player *pPlayer = GetPlayer();

	D3DXVECTOR3 posRDiff;
	D3DXVECTOR3 posVDiff;

	//目的の視点/注視点を設定(初期値)
	g_camera.posRDest = D3DXVECTOR3(pPlayer->pos.x + sinf(pPlayer->rot.y + D3DX_PI) * 20.0f, pPlayer->pos.y, pPlayer->pos.z + cosf(pPlayer->rot.y + D3DX_PI) * 20.0f);				//注視点

	g_camera.posVDest = D3DXVECTOR3(g_camera.posRDest.x + (cosf(g_camera.rot.z) * sinf(g_camera.rot.y)) * -g_camera.fLengthCamera, 
									pPlayer->pos.y + 50.0f, 
									g_camera.posRDest.z + (cosf(g_camera.rot.z) * cosf(g_camera.rot.y)) * -g_camera.fLengthCamera);		//視点

	posRDiff = g_camera.posRDest - g_camera.posR;			//注視点の差分
	posVDiff = g_camera.posVDest - g_camera.posV;			//視点の差分

	g_camera.posR += posRDiff * 0.2f;			//注視点を補正する
	
	g_camera.posV += posVDiff * 0.3f;			//視点を補正する
}

//====================================================================
// カメラの位置を自動的に後ろ側へ
//====================================================================
void CameraAuto(void)
{
	//変数宣言
	float fRotDiff = 0.0f;			//差分保存用

	//ポインタ情報の取得
	Player *pPlayer = GetPlayer();

	fRotDiff = (pPlayer->rot.y + D3DX_PI) - g_camera.rot.y;			//差分を計算

	//目標の角度の補正
	if (fRotDiff > D3DX_PI)
	{
		fRotDiff -= 6.28f;
	}
	if (fRotDiff < -D3DX_PI)
	{
		fRotDiff += 6.28f;
	}

	g_camera.rot.y += fRotDiff * 0.045f;			//補正する

	//角度の補正
	if (g_camera.rot.y > D3DX_PI)
	{
		g_camera.rot.y -= 6.28f;
	}
	if (g_camera.rot.y < -D3DX_PI)
	{
		g_camera.rot.y += 6.28f;
	}

	//カメラを更新する
	g_camera.posVDest.x = pPlayer->pos.x + (cosf(g_camera.rot.z) * sinf(g_camera.rot.y)) * -g_camera.fLengthCamera;
	g_camera.posVDest.y = pPlayer->pos.y + sinf(g_camera.rot.z) * -g_camera.fLengthCamera;			//視点Y
	g_camera.posVDest.z = pPlayer->pos.z + (cosf(g_camera.rot.z) * cosf(g_camera.rot.y)) * -g_camera.fLengthCamera;
}

//====================================================================
//カメラの設定処理処理
//====================================================================
void SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得

	//プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&g_camera.mtxProjection);

	//プロジェクションマトリックスを作成
	D3DXMatrixPerspectiveFovLH(&g_camera.mtxProjection,
		D3DXToRadian(45.0f),							//視野角
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,		//画面のアスペクト比
		10.0f,											//z値の最小値
		10000.0f);										//z値の最大値

	//プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &g_camera.mtxProjection);

	//ビューマトリックスの初期化
	D3DXMatrixIdentity(&g_camera.mtxView);

	//ビューマトリックスの作成
	D3DXMatrixLookAtLH(&g_camera.mtxView,
						&g_camera.posV,				//視点
						&g_camera.posR,				//注視点
						&g_camera.vecU);			//情報ベクトル

	//ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &g_camera.mtxView);
}

//===================================================
// カメラ位置の表示
//===================================================
void DrawCameraPos(void)
{
	RECT rect = { 0, 60, SCREEN_WIDTH, SCREEN_HEIGHT };
	char aStr[256];

	Camera PosCamera = GetCamera();
	LPD3DXFONT pFont = GetFont();

	//文字列を代入
	sprintf(&aStr[0], "カメラ視点:[%0.2f, %0.2f, %0.2f]\nカメラ注視点:[%0.2f, %0.2f, %0.2f]\nカメラの向き：[%0.2f, %0.2f, %0.2f]\n視点と注視点の距離[%0.2f]",
		PosCamera.posV.x, PosCamera.posV.y, PosCamera.posV.z, PosCamera.posR.x, PosCamera.posR.y, PosCamera.posR.z, PosCamera.rot.x, PosCamera.rot.y, PosCamera.rot.z, PosCamera.fLengthCamera);

	//テキスト描画
	pFont->DrawTextA(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}

//===================================================
// カメラの操作説明表示
//===================================================
void DrawCameraOps(void)
{
	RECT rect = { 0, 160, SCREEN_WIDTH, SCREEN_HEIGHT };
	char aStr[256];

	Camera PosCamera = GetCamera();
	LPD3DXFONT pFont = GetFont();

	//文字列を代入
	wsprintf(&aStr[0], "*カメラ移動*\n[W][A][S][D]\n\n*カメラ視点操作*\n上[Y]下[N]右[C]左[Z]\n\n*カメラ注視点移動*\n上[T]下[B]右[E]左[Q]\n\n弾発射");

	//テキスト描画
	pFont->DrawTextA(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}

//====================================================================
//カメラの情報のポインタ
//====================================================================
Camera GetCamera(void)
{
	return g_camera;
}