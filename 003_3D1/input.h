//======================================================================================
//
//キーボード入力処理[input.h]
//Author;小笠原　彪
//
//======================================================================================
#ifndef _INPUT_H_
#define _INPUT_H_

#include "main.h"

//パッドを使うために必要
#include "Xinput.h"
#pragma comment(lib, "xinput.lib")

//押されたボタンの種類
typedef enum //20以内
{
	BUTTON_0 = 0,				// 十字↑ 
	BUTTON_1,					// 十字↓
	BUTTON_2,					// 十字←
	BUTTON_3,					// 十字→
	BUTTON_START,					// start
	BUTTON_BACK,					// back
	BUTTON_LS,					// 左スティック押し込み
	BUTTON_RS,					// 右スティック押し込み
	BUTTON_LB,					// LB/5
	BUTTON_RB,					// RB/6
	BUTTON_10,					// ?
	BUTTON_11,					// ?
	BUTTON_A,					// A/3 
	BUTTON_B,					// B/4
	BUTTON_X,					// X/1
	BUTTON_Y,					// Y/2
	BUTTON_16,					// ?
	BUTTON_17,					// ?
	BUTTON_18,					// ?
	BUTTON_19,					// ?
	BUTTON_20,					// ?
	BUTTON_MAX
} JOYKEY;

//プロトタイプ宣言
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd);
void UninitKeyboard(void);
void UpdateKeyboard(void);
bool GetKeyboardPress(int nKey);
bool GetKeyboardTrigger(int nKey);
bool GetKeyboardRipeat(int nKey);
bool GetKeyboardRelease(int nKey);

//ゲームパッド
HRESULT InitGamePad(void);
void UninitGamePad(void);
void UpdateGamePad(void);
bool GetGamePadPress(JOYKEY nKey, int nPlayer);
bool GetGamePadTrigger(JOYKEY nKey, int nPlayer);
bool GetGamePadRepeat(JOYKEY nKey, int nPlayer);
bool GetGamePadRelease(JOYKEY nKey, int nPlayer);
SHORT GetJoyStickLX(int nPlayer);
SHORT GetJoyStickLY(int nPlayer);
SHORT GetJoyStickRX(int nPlayer);
SHORT GetJoyStickRY(int nPlayer);

#endif