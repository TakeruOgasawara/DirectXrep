//===========================================================================================
//
//[main.cpp]
//Author:���}���@�V
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

//�}�N����`
#define CLASS_NAME		"Windowclass"			//�E�B���h�E�N���X�̖��O
#define WINDOW_NAME		"3D"		//�E�B���h�E�̖��O

#define ID_BUTTON_FINISH	(101)				//�I���{�^����ID

//�v���^�C�v�錾
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lPalam);
HRESULT Init(HINSTANCE hInstance, HWND hwnd, BOOL bWindow);							//����������
void Uninit(void);				
void Update(void);
void Draw(void);
void DrawFPS(void);				//FPS�̕\������

//�O���[�o���ϐ�
//�v���^�C�v�錾
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lPalam);
HRESULT Init(HINSTANCE hInstance, HWND hwnd, BOOL bWindow);							//����������
LPDIRECT3D9 g_pD3D = NULL;						//Directx3D�I�u�W�F�N�g�ւ̃|�C���^
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;			//Directx3D�ւ̃f�o�C�X�ւ̃|�C���^
LPD3DXFONT g_pFont = NULL;						//�t�H���g�ւ̃|�C���^
int g_nCountFPS = 0;							//FPS�J�E���^
bool g_DispDebug = false;						//�f�o�b�O�\����ON/OFF
bool g_bWireframe = false;

//===========================================================================================
//���C���֐�
//===========================================================================================

int  WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR LpCmadLine, int nCmdShow)
{
	WNDCLASSEX wcex
	{
		sizeof(WNDCLASSEX),					//WNDCLASSEX�̃������T�C�Y
		CS_CLASSDC,							//�E�B���h�E�̃X�^�C��
		WindowProc,							//�E�B���h�E�v���V�[�W��
		0,									//0�ɂ���(�ʏ�͎g�p���Ȃ�)
		0,									//0�ɂ���(�ʏ�͎g�p���Ȃ�)
		hInstance,							//�C���X�^���X�n���h��
		LoadIcon(NULL, IDI_APPLICATION),	//�^�X�N�o�[�̃A�C�R��
		LoadCursor(NULL, IDC_ARROW),		//�}�E�X�J�[�\��
		(HBRUSH)(COLOR_WINDOW + 1),			//�N���C�A���g�̈�̔w�i�F
		NULL,								//���j���[�o�[
		CLASS_NAME,							//�E�B���h�E�N���X�̖��O
		LoadIcon(NULL, IDI_APPLICATION)		//�t�@�C���̃A�C�R��
	};

	HWND hWnd;				//�E�B���h�E�n���h��(���ʎq)
	MSG msg;				//���b�Z�[�W���i�[����ϐ�

							//�E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	//�E�B���h�E�𐶐�
	hWnd = CreateWindowEx(0,	//�g���E�B���h�E�X�^�C��
		CLASS_NAME,				//�E�B���h�E�N���X��
		WINDOW_NAME,			//�E�B���h�E�̖��O
		WS_OVERLAPPEDWINDOW,	//�E�B���h�E�X�^�C��
		CW_USEDEFAULT,			//�E�B���h�E�̍���X���W
		CW_USEDEFAULT,			//�E�B���h�E�̍���Y���W
		SCREEN_WIDTH,			//�E�B���h�E�̕�
		SCREEN_HEIGHT,			//�E�B���h�E�̍���
		NULL,					//�e�E�B���h�E�̃n���h��
		NULL,					//���j���[�n���h���܂��͎q�E�B���h�EID
		hInstance,				//�C���X�^���X�n���h��
		NULL);					//�E�B���h�E����f�[�^

	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };				//��ʃT�C�Y�̍\����

	//�E�C���h�N���X�̓o�^
	RegisterClassEx(&wcex);

	//�N���C�A���g�̈�̃T�C�Y�ɒ���
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	//�E�B���h�E�𐶐�
	hWnd = CreateWindowEx(0,	//�g���E�B���h�E�X�^�C��
		CLASS_NAME,				//�E�B���h�E�N���X��
		WINDOW_NAME,			//�E�B���h�E�̖��O
		WS_OVERLAPPEDWINDOW,	//�E�B���h�E�X�^�C��
		CW_USEDEFAULT,			//�E�B���h�E�̍���X���W
		CW_USEDEFAULT,			//�E�B���h�E�̍���Y���W
		(rect.right-rect.left),			//�E�B���h�E�̕�
		(rect.bottom-rect.top),			//�E�B���h�E�̍���
		NULL,					//�e�E�B���h�E�̃n���h��
		NULL,					//���j���[�n���h���܂��͎q�E�B���h�EID
		hInstance,				//�C���X�^���X�n���h��
		NULL);					//�E�B���h�E����f�[�^

	DWORD dwCurrentTime;		//���ݎ���
	DWORD dwExecLastTime;		//�Ō�ɏ�����������
	DWORD dwFrameCount;			//�t���[���J�E���g
	DWORD dwFPSLastTime;		//�Ō��FPS��

	//����\��ݒ�
	timeBeginPeriod(1);

	//����������
	dwCurrentTime = 0;					//����������
	dwExecLastTime = timeGetTime();		//���ݎ������擾(�ۑ�)
	dwFrameCount = 0;
	dwFPSLastTime = timeGetTime();
		
	if (FAILED(Init(hInstance, hWnd, TRUE)))
	{
		return -1;
	}

	//�E�B���h�E�̕\��
	ShowWindow(hWnd, nCmdShow);			//�E�B���h�E�̕\����Ԃ�ݒ�
	UpdateWindow(hWnd);					//�N���C�A���g�̈���X�V

	//���b�Z�[�W���[�v
	while (1)
	{//windows�̏���
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{//windows�̏���
			if (msg.message == WM_QUIT)
			{//WM_QUIT���b�Z�[�W���󂯎�����烁�b�Z�[�W���[�v�𔲂���
				break;
			}
			else 
			{
				//���b�Z�[�W��ݒ�
				TranslateMessage(&msg);			//���z�L�[���b�Z�[�W�𕶎��֕ϊ�
				DispatchMessage(&msg);			//�E�B���h�E�v���V�[�W���փ��b�Z�[�W�𑗏o
			}
		}
		else
		{//Directx�̏���
			dwCurrentTime = timeGetTime();		//���ݎ������擾

			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{//0.5�b�o��
			 //FPS���o��
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);
				dwFPSLastTime = dwCurrentTime;					//FPS�𑪒肵��������ۑ�
				dwFrameCount = 0;								//�t���[���J�E���g���N���A

			}
			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{//60����1�b�o��
				dwExecLastTime = dwCurrentTime;				//�����J�n�̎���(���ݎ���)��ۑ�
		
			//�X�V����
			Update();
			//�`�揈��
			Draw();

			dwFrameCount++;					//�t���[���J�E���g�����Z
			}
		}
	}

	//����\��߂�
	timeEndPeriod(1);

	//�I������
	Uninit();

	//�E�B���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;
}

//�E�B���h�E�v���V�[�W��
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID;							//�Ԃ�l���i�[

	switch (uMsg)
	{
	case WM_DESTROY:			//�E�B���h�E�j���̃��b�Z�[�W

								//WM_QUIT���b�Z�[�W�𑗂�
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:			//�L�[�����̃��b�Z�[�W

		switch (wParam)
		{//[ESC]�L�[�������ꂽ
		case VK_ESCAPE:

			nID = MessageBox(hWnd, "�I�����܂����H", "�I�����b�Z�[�W", MB_YESNO);

			if (nID == IDYES)
			{
				//�E�B���h�E��j������(WM_DESTROY���b�Z�[�W�𑗂�)
				DestroyWindow(hWnd);
				break;
			}
		}
		break;

	case WM_COMMAND:	//�R�}���h���s�̃��b�Z�[�W
		if (LOWORD(wParam) == ID_BUTTON_FINISH)
		{//�I���{�^���������ꂽ
			nID = MessageBox(hWnd, "�I�����܂����H", "�I�����b�Z�[�W", MB_YESNO);

			if (nID == IDYES)
			{
				//�E�B���h�E��j������(WM_DESTROY���b�Z�[�W�𑗂�)
				DestroyWindow(hWnd);
			}
		}

		break;

	case WM_CLOSE:		//�R�}���h���s�̃��b�Z�[�W
		nID = MessageBox(hWnd, "�I�����܂����H", "�I�����b�Z�[�W", MB_YESNO);

		if (nID == IDYES)
		{
			//�E�B���h�E��j������(WM_DESTROY���b�Z�[�W�𑗂�)
			DestroyWindow(hWnd);
		}
		else
		{
			return 0;		//0��Ԃ��Ȃ��ƏI�����Ă��܂�
		}
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//========================================================================
//����������
//========================================================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;				//�f�B�X�v���C���[�h
	D3DPRESENT_PARAMETERS d3dpp;		//�v���[���e�[�V�����p�����[�^

	//DIrect3D�I�u�W�F�N�g�̍쐬
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}

	//���݂̃f�o�C�X�v���C���[�h���擾
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	//�f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));				//�p�����[�^�̃[���N���A

	d3dpp.BackBufferWidth = SCREEN_WIDTH;			//�Q�[����ʃT�C�Y(��)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;			//�Q�[���̉�ʃT�C�Y(����)
	d3dpp.BackBufferFormat = d3ddm.Format;			//�o�b�N�o�b�t�@�`��
	d3dpp.BackBufferCount = 1;						//�o�b�N�o�b�t�@�̐�

	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;		//�_�u���o�b�t�@�̐؂�ւ�(�f���M���ɓ���)
	d3dpp.EnableAutoDepthStencil = TRUE;			//�f�v�X�o�b�t�@�ƃX�e���V���o�b�t�@���쐬
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;		//�f�v�X�o�b�t�@�Ƃ���16bit����
	d3dpp.Windowed = bWindow;						//�E�C���h���[�h
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;			//���t���b�V�����[�g
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;				//�C���^�[�o��

	//Direct3D�f�o�C�X�̐���
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

	//�����_�[�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	//�T���v���[�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	//�w�i
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
	//�e�N�X�`���[�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	//�f�o�b�N�\���p�t�H���g�̐���
	D3DXCreateFont(g_pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &g_pFont);

	//�L�[�{�[�h�̏���������
	if (FAILED(InitKeyboard(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	//�p�b�h�̏���������
	InitGamePad();

	//�J�����̏���������
	InitCamera();
	//���C�g�̏���������
	InitLight();
	//�|���S���̏���������
	InitPolygon();
	//�e�̏���������
	InitShadow();
	//���f���̏���������
	//InitModel();
	//�v���C���[�̏���������
	InitPlayer();
	//�t�B�[���h�̏���������
	//InitField();
	//�ǂ̏���������
	InitWall();
	//�r���{�[�h�̏���������
	InitBillboard();
	//�e�̏���������
	InitBullet();
	//�����̏���������
	InitExplosion();
	//�G�t�F�N�g�̏���������
	InitEffect();
	//�p�[�e�B�N���̏���������
	InitParticle();
	//���b�V���t�B�[���h�̏���������
	InitMeshField();
	//���b�V���E�H�[���̏���������
	InitMeshWall();
	//���b�V���V�����_�[�̏���������
	InitMeshCylinder();
	//�I�u�W�F�N�g�̏���������
	InitObject();

	return S_OK;
}


//==================================================
//�I������
//==================================================
void Uninit(void)
{
	//�|���S���̏I������
	UninitPolygon();
	//���f���̏I������
	//UninitModel();
	//�v���C���[�̏I������
	UninitPlayer();
	//�e�̏I������
	UninitShadow();
	//�t�B�[���h�̏I������
	//UninitField();
	//�ǂ̏I������
	UninitWall();
	//�r���{�[�h�̏I������
	UninitBillboard();
	//�L�[�{�[�h�̏I������
	UninitKeyboard();
	//�e�̏I������
	UninitBullet();
	//�����̏I������
	UninitExplosion();
	//�G�t�F�N�g�̏I������
	UninitEffect();
	//�p�[�e�B�N���̏I������
	UninitParticle();
	//���b�V���t�B�[���h�̏I������
	UninitMeshField();
	//���b�V���E�H�[���̏I������
	UninitMeshWall();
	//���b�V���V�����_�[�̏I������
	UninitMeshCylinder();
	//�I�u�W�F�N�g�̏I������
	UninitObject();
	
	//�f�o�b�N�\���p�t�H���g�̔j��
	if (g_pFont != NULL)
	{
		g_pFont->Release();
		g_pFont = NULL;
	}
	//Direct3D�f�o�C�X�̔j��
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}
	//Direct3D�I�u�W�F�N�g�̔j��
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}
}

//===================================================
//�X�V����
//===================================================
void Update(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�L�[�{�[�h�̍X�V����
	UpdateKeyboard();
	
	if (GetKeyboardTrigger(DIK_F1) == true)
	{//�f�o�b�O�\������
		g_DispDebug = g_DispDebug ^ 1;
	}

	if (GetKeyboardTrigger(DIK_F2) == true)
	{//�f�o�b�O�\������
		g_bWireframe = g_bWireframe ? false : true;
	}

	if (g_bWireframe == true)
	{
		pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	}

	//�J�����̍X�V����
	UpdateCamera();
	//���C�g�̍X�V����
	UpdateLight();
	//�|���S���̍X�V����
	UpdatePolygon();
	//���f���̍X�V����
	//UpdateModel();
	//�v���C���[�̍X�V����
	UpdatePlayer();
	//�e�̍X�V����
	UpdateBullet();
	//�����̍X�V����
	UpdateExplosion();
	//�G�t�F�N�g�̍X�V����
	UpdateEffect();
	//�p�[�e�B�N���̍X�V����
	UpdateParticle();
	//���b�V���t�B�[���h�̍X�V����
	UpdateMeshField();
	//���b�V���E�H�[���̍X�V����
	UpdateMeshWall();
	//���b�V���V�����_�[�̍X�V����
	UpdateMeshCylinder();
	//�I�u�W�F�N�g�̍X�V����
	UpdateObject();
}

//===================================================
//�`�揈��
//===================================================
void Draw(void)
{
	//��ʂ��N���A(�o�b�N�o�b�t�@��Z�o�b�t�@�̃N���A)
	g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 255), 1.0f, 0);

	//�`��J�n
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{//�`��J�n�����������ꍇ

		//�J�����̕`�揈��
		SetCamera();
		
		//�|���S���̕`�揈��
		//DrawPolygon();
		//�t�B�[���h�̕`�揈��
		//DrawField();
		//���b�V���t�B�[���h�̕`�揈��
		DrawMeshField();
		//���b�V���E�H�[���̕`�揈��
		DrawMeshWall();
		//���b�V���V�����_�[�̕`�揈��
		DrawMeshCylinder();
		//���f���̕`�揈��
		//DrawModel();
		//�v���C���[�̕`�揈��
		DrawPlayer();
		//�I�u�W�F�N�g�̕`�揈��
		DrawObject();
		//�e�̕`�揈��
		DrawShadow();
		//�ǂ̕`�揈��
		//DrawWall();
		//�r���{�[�h�̕`�揈��
		DrawBillboard();
		//�e�̕`�揈��
		DrawBullet();
		//�G�t�F�N�g�̕`�揈��
		DrawEffect();
		//�����̕`�揈��
		DrawExplosion();
		//�p�[�e�B�N���̕`�揈��
		DrawParticle();

		//�`��I��
		g_pD3DDevice->EndScene();
	}

//#ifdef _DEBUG	//�f�o�b�N���ɕ\��
	DrawFPS();
	DrawCameraPos();
	DrawCameraOps();
	DrawModelPos();
	DrawDebug();
//#endif

	//�o�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//===================================================
// FPS�̕\��
//===================================================
void DrawFPS(void)
{
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	char aStr[256];

	//���������
	wsprintf(&aStr[0], "FPS:%d", g_nCountFPS);

	//�e�L�X�g�`��
	g_pFont->DrawTextA(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}

//===================================================
// �f�o�C�X�̎擾
//===================================================
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}

//===================================================
// �t�H���g�̎擾
//===================================================
LPD3DXFONT GetFont(void)
{
	return g_pFont;
}