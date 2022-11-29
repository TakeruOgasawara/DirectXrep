//===========================================================================================
//
//[main.cpp]
//Author:小笠原　彪
//
//===========================================================================================
#include <stdio.h>
#include "main.h"
#include "input.h"
#include "camera.h"
#include "polygon.h"
#include "light.h"
#include "model.h"
#include "shadow.h"
#include "wall.h"
#include "field.h"
#include "billboard.h"
#include "bullet.h"
#include "player.h"
#include "explosion.h"
#include "effect.h"
#include "particle.h"
#include "meshfield.h"
#include "meshwall.h"
#include "meshcylinder.h"
#include "object.h"

//マクロ定義
#define CLASS_NAME		"Windowclass"			//ウィンドウクラスの名前
#define WINDOW_NAME		"3D"		//ウィンドウの名前

#define ID_BUTTON_FINISH	(101)				//終了ボタンのID

//プロタイプ宣言
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lPalam);
HRESULT Init(HINSTANCE hInstance, HWND hwnd, BOOL bWindow);							//初期化処理
void Uninit(void);				
void Update(void);
void Draw(void);
void DrawFPS(void);				//FPSの表示処理

//グローバル変数
//プロタイプ宣言
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lPalam);
HRESULT Init(HINSTANCE hInstance, HWND hwnd, BOOL bWindow);							//初期化処理
LPDIRECT3D9 g_pD3D = NULL;						//Directx3Dオブジェクトへのポインタ
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;			//Directx3Dへのデバイスへのポインタ
LPD3DXFONT g_pFont = NULL;						//フォントへのポインタ
int g_nCountFPS = 0;							//FPSカウンタ
bool g_DispDebug = false;						//デバッグ表示のON/OFF
bool g_bWireframe = false;

//===========================================================================================
//メイン関数
//===========================================================================================

int  WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR LpCmadLine, int nCmdShow)
{
	WNDCLASSEX wcex
	{
		sizeof(WNDCLASSEX),					//WNDCLASSEXのメモリサイズ
		CS_CLASSDC,							//ウィンドウのスタイル
		WindowProc,							//ウィンドウプロシージャ
		0,									//0にする(通常は使用しない)
		0,									//0にする(通常は使用しない)
		hInstance,							//インスタンスハンドル
		LoadIcon(NULL, IDI_APPLICATION),	//タスクバーのアイコン
		LoadCursor(NULL, IDC_ARROW),		//マウスカーソル
		(HBRUSH)(COLOR_WINDOW + 1),			//クライアント領域の背景色
		NULL,								//メニューバー
		CLASS_NAME,							//ウィンドウクラスの名前
		LoadIcon(NULL, IDI_APPLICATION)		//ファイルのアイコン
	};

	HWND hWnd;				//ウィンドウハンドル(識別子)
	MSG msg;				//メッセージを格納する変数

							//ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	//ウィンドウを生成
	hWnd = CreateWindowEx(0,	//拡張ウィンドウスタイル
		CLASS_NAME,				//ウィンドウクラス名
		WINDOW_NAME,			//ウィンドウの名前
		WS_OVERLAPPEDWINDOW,	//ウィンドウスタイル
		CW_USEDEFAULT,			//ウィンドウの左上X座標
		CW_USEDEFAULT,			//ウィンドウの左上Y座標
		SCREEN_WIDTH,			//ウィンドウの幅
		SCREEN_HEIGHT,			//ウィンドウの高さ
		NULL,					//親ウィンドウのハンドル
		NULL,					//メニューハンドルまたは子ウィンドウID
		hInstance,				//インスタンスハンドル
		NULL);					//ウィンドウ制作データ

	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };				//画面サイズの構造体

	//ウインドクラスの登録
	RegisterClassEx(&wcex);

	//クライアント領域のサイズに調整
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	//ウィンドウを生成
	hWnd = CreateWindowEx(0,	//拡張ウィンドウスタイル
		CLASS_NAME,				//ウィンドウクラス名
		WINDOW_NAME,			//ウィンドウの名前
		WS_OVERLAPPEDWINDOW,	//ウィンドウスタイル
		CW_USEDEFAULT,			//ウィンドウの左上X座標
		CW_USEDEFAULT,			//ウィンドウの左上Y座標
		(rect.right-rect.left),			//ウィンドウの幅
		(rect.bottom-rect.top),			//ウィンドウの高さ
		NULL,					//親ウィンドウのハンドル
		NULL,					//メニューハンドルまたは子ウィンドウID
		hInstance,				//インスタンスハンドル
		NULL);					//ウィンドウ制作データ

	DWORD dwCurrentTime;		//現在時刻
	DWORD dwExecLastTime;		//最後に処理した時刻
	DWORD dwFrameCount;			//フレームカウント
	DWORD dwFPSLastTime;		//最後にFPSを

	//分解能を設定
	timeBeginPeriod(1);

	//初期化処理
	dwCurrentTime = 0;					//初期化する
	dwExecLastTime = timeGetTime();		//現在時刻を取得(保存)
	dwFrameCount = 0;
	dwFPSLastTime = timeGetTime();
		
	if (FAILED(Init(hInstance, hWnd, TRUE)))
	{
		return -1;
	}

	//ウィンドウの表示
	ShowWindow(hWnd, nCmdShow);			//ウィンドウの表示状態を設定
	UpdateWindow(hWnd);					//クライアント領域を更新

	//メッセージループ
	while (1)
	{//windowsの処理
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{//windowsの処理
			if (msg.message == WM_QUIT)
			{//WM_QUITメッセージを受け取ったらメッセージループを抜ける
				break;
			}
			else 
			{
				//メッセージを設定
				TranslateMessage(&msg);			//仮想キーメッセージを文字へ変換
				DispatchMessage(&msg);			//ウィンドウプロシージャへメッセージを送出
			}
		}
		else
		{//Directxの処理
			dwCurrentTime = timeGetTime();		//現在時刻を取得

			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{//0.5秒経過
			 //FPSを経過
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);
				dwFPSLastTime = dwCurrentTime;					//FPSを測定した時刻を保存
				dwFrameCount = 0;								//フレームカウントをクリア

			}
			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{//60分の1秒経過
				dwExecLastTime = dwCurrentTime;				//処理開始の時刻(現在時刻)を保存
		
			//更新処理
			Update();
			//描画処理
			Draw();

			dwFrameCount++;					//フレームカウントを加算
			}
		}
	}

	//分解能を戻す
	timeEndPeriod(1);

	//終了処理
	Uninit();

	//ウィンドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;
}

//ウィンドウプロシージャ
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID;							//返り値を格納

	switch (uMsg)
	{
	case WM_DESTROY:			//ウィンドウ破棄のメッセージ

								//WM_QUITメッセージを送る
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:			//キー押下のメッセージ

		switch (wParam)
		{//[ESC]キーが押された
		case VK_ESCAPE:

			nID = MessageBox(hWnd, "終了しますか？", "終了メッセージ", MB_YESNO);

			if (nID == IDYES)
			{
				//ウィンドウを破棄する(WM_DESTROYメッセージを送る)
				DestroyWindow(hWnd);
				break;
			}
		}
		break;

	case WM_COMMAND:	//コマンド発行のメッセージ
		if (LOWORD(wParam) == ID_BUTTON_FINISH)
		{//終了ボタンが押された
			nID = MessageBox(hWnd, "終了しますか？", "終了メッセージ", MB_YESNO);

			if (nID == IDYES)
			{
				//ウィンドウを破棄する(WM_DESTROYメッセージを送る)
				DestroyWindow(hWnd);
			}
		}

		break;

	case WM_CLOSE:		//コマンド発行のメッセージ
		nID = MessageBox(hWnd, "終了しますか？", "終了メッセージ", MB_YESNO);

		if (nID == IDYES)
		{
			//ウィンドウを破棄する(WM_DESTROYメッセージを送る)
			DestroyWindow(hWnd);
		}
		else
		{
			return 0;		//0を返さないと終了してしまう
		}
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//========================================================================
//初期化処理
//========================================================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;				//ディスプレイモード
	D3DPRESENT_PARAMETERS d3dpp;		//プレゼンテーションパラメータ

	//DIrect3Dオブジェクトの作成
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}

	//現在のデバイスプレイモードを取得
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	//デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));				//パラメータのゼロクリア

	d3dpp.BackBufferWidth = SCREEN_WIDTH;			//ゲーム画面サイズ(幅)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;			//ゲームの画面サイズ(高さ)
	d3dpp.BackBufferFormat = d3ddm.Format;			//バックバッファ形式
	d3dpp.BackBufferCount = 1;						//バックバッファの数

	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;		//ダブルバッファの切り替え(映像信号に同期)
	d3dpp.EnableAutoDepthStencil = TRUE;			//デプスバッファとステンシルバッファを作成
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;		//デプスバッファとして16bit扱う
	d3dpp.Windowed = bWindow;						//ウインドモード
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;			//リフレッシュレート
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;				//インターバル

	//Direct3Dデバイスの生成
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&g_pD3DDevice)))
	{
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&g_pD3DDevice)))
		{
			if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&g_pD3DDevice)))
			{
				return E_FAIL;
			}
		}
	}

	//レンダーステートの設定
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	//サンプラーステートの設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	//背景
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
	//テクスチャーステートの設定
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	//デバック表示用フォントの生成
	D3DXCreateFont(g_pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &g_pFont);

	//キーボードの初期化処理
	if (FAILED(InitKeyboard(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	//パッドの初期化処理
	InitGamePad();

	//カメラの初期化処理
	InitCamera();
	//ライトの初期化処理
	InitLight();
	//ポリゴンの初期化処理
	InitPolygon();
	//影の初期化処理
	InitShadow();
	//モデルの初期化処理
	//InitModel();
	//プレイヤーの初期化処理
	InitPlayer();
	//フィールドの初期化処理
	//InitField();
	//壁の初期化処理
	InitWall();
	//ビルボードの初期化処理
	InitBillboard();
	//弾の初期化処理
	InitBullet();
	//爆発の初期化処理
	InitExplosion();
	//エフェクトの初期化処理
	InitEffect();
	//パーティクルの初期化処理
	InitParticle();
	//メッシュフィールドの初期化処理
	InitMeshField();
	//メッシュウォールの初期化処理
	InitMeshWall();
	//メッシュシリンダーの初期化処理
	InitMeshCylinder();
	//オブジェクトの初期化処理
	InitObject();

	return S_OK;
}


//==================================================
//終了処理
//==================================================
void Uninit(void)
{
	//ポリゴンの終了処理
	UninitPolygon();
	//モデルの終了処理
	//UninitModel();
	//プレイヤーの終了処理
	UninitPlayer();
	//影の終了処理
	UninitShadow();
	//フィールドの終了処理
	//UninitField();
	//壁の終了処理
	UninitWall();
	//ビルボードの終了処理
	UninitBillboard();
	//キーボードの終了処理
	UninitKeyboard();
	//弾の終了処理
	UninitBullet();
	//爆発の終了処理
	UninitExplosion();
	//エフェクトの終了処理
	UninitEffect();
	//パーティクルの終了処理
	UninitParticle();
	//メッシュフィールドの終了処理
	UninitMeshField();
	//メッシュウォールの終了処理
	UninitMeshWall();
	//メッシュシリンダーの終了処理
	UninitMeshCylinder();
	//オブジェクトの終了処理
	UninitObject();
	
	//デバック表示用フォントの破棄
	if (g_pFont != NULL)
	{
		g_pFont->Release();
		g_pFont = NULL;
	}
	//Direct3Dデバイスの破棄
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}
	//Direct3Dオブジェクトの破棄
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}
}

//===================================================
//更新処理
//===================================================
void Update(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//キーボードの更新処理
	UpdateKeyboard();
	
	if (GetKeyboardTrigger(DIK_F1) == true)
	{//デバッグ表示処理
		g_DispDebug = g_DispDebug ^ 1;
	}

	if (GetKeyboardTrigger(DIK_F2) == true)
	{//デバッグ表示処理
		g_bWireframe = g_bWireframe ? false : true;
	}

	if (g_bWireframe == true)
	{
		pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	}

	//カメラの更新処理
	UpdateCamera();
	//ライトの更新処理
	UpdateLight();
	//ポリゴンの更新処理
	UpdatePolygon();
	//モデルの更新処理
	//UpdateModel();
	//プレイヤーの更新処理
	UpdatePlayer();
	//弾の更新処理
	UpdateBullet();
	//爆発の更新処理
	UpdateExplosion();
	//エフェクトの更新処理
	UpdateEffect();
	//パーティクルの更新処理
	UpdateParticle();
	//メッシュフィールドの更新処理
	UpdateMeshField();
	//メッシュウォールの更新処理
	UpdateMeshWall();
	//メッシュシリンダーの更新処理
	UpdateMeshCylinder();
	//オブジェクトの更新処理
	UpdateObject();
}

//===================================================
//描画処理
//===================================================
void Draw(void)
{
	//画面をクリア(バックバッファとZバッファのクリア)
	g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 255), 1.0f, 0);

	//描画開始
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{//描画開始が成功した場合

		//カメラの描画処理
		SetCamera();
		
		//ポリゴンの描画処理
		//DrawPolygon();
		//フィールドの描画処理
		//DrawField();
		//メッシュフィールドの描画処理
		DrawMeshField();
		//メッシュウォールの描画処理
		DrawMeshWall();
		//メッシュシリンダーの描画処理
		DrawMeshCylinder();
		//モデルの描画処理
		//DrawModel();
		//プレイヤーの描画処理
		DrawPlayer();
		//オブジェクトの描画処理
		DrawObject();
		//影の描画処理
		DrawShadow();
		//壁の描画処理
		//DrawWall();
		//ビルボードの描画処理
		DrawBillboard();
		//弾の描画処理
		DrawBullet();
		//エフェクトの描画処理
		DrawEffect();
		//爆発の描画処理
		DrawExplosion();
		//パーティクルの描画処理
		DrawParticle();

		//描画終了
		g_pD3DDevice->EndScene();
	}

//#ifdef _DEBUG	//デバック時に表示
	DrawFPS();
	DrawCameraPos();
	DrawCameraOps();
	DrawModelPos();
	DrawDebug();
//#endif

	//バクバッファとフロントバッファの入れ替え
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//===================================================
// FPSの表示
//===================================================
void DrawFPS(void)
{
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	char aStr[256];

	//文字列を代入
	wsprintf(&aStr[0], "FPS:%d", g_nCountFPS);

	//テキスト描画
	g_pFont->DrawTextA(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}

//===================================================
// デバイスの取得
//===================================================
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}

//===================================================
// フォントの取得
//===================================================
LPD3DXFONT GetFont(void)
{
	return g_pFont;
}