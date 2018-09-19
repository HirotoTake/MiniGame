

//*************** �C���N���[�h ***************
#include "include\main.h"
#include "include\common.h"
//�}�l�[�W��
#include "include\sceneMgr.h"
#include "include\fade.h"


//*************** �萔�E�}�N�� ***************




//***************�O���[�o���錾***************
#ifdef WIN_
//�V�X�e���n
LPDIRECT3D9  g_pD3D = NULL;						// Direct3D �I�u�W�F�N�g 
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;			// Device�I�u�W�F�N�g(�`��ɕK�v)
#ifdef _DEBUG 
LPD3DXFONT g_pD3DXFont = NULL;					// �t�H���g�ւ̃|�C���^ 
int  g_nCountFPS;								// FPS�J�E���^ 
#endif
#endif // WIN_




//*************** �v���g�^�C�v ***************
#ifdef WIN_


/*------------------------------------------------------------------------------------------------------/
I / O:
�@ �\:�v���V�[�W��
-------------------------------------------------------------------------------------------------------*/
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

/*------------------------------------------------------------------------------------------------------/
I / O:
�@ �\:�Q�[�����[�v�O�̃V�X�e��������
-------------------------------------------------------------------------------------------------------*/
HRESULT InitSystem(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
#endif // WIN_

/*------------------------------------------------------------------------------------------------------/
I / O:
�@ �\:�Q�[�����̏�ԕω������̏�����
-------------------------------------------------------------------------------------------------------*/
void Init(void);

/*------------------------------------------------------------------------------------------------------/
I / O:
�@ �\:�Q�[�����̍X�V����
-------------------------------------------------------------------------------------------------------*/
void UpDate(void);

/*------------------------------------------------------------------------------------------------------/
I / O:
�@ �\:�Q�[�����̕`�揈��
-------------------------------------------------------------------------------------------------------*/
void Draw(void);

/*------------------------------------------------------------------------------------------------------/
I / O:
�@ �\:�Q�[���I�����̏I������
-------------------------------------------------------------------------------------------------------*/
void UnInit(void);

#ifdef WIN_

/*------------------------------------------------------------------------------------------------------/
I / O:
�@ �\:
-------------------------------------------------------------------------------------------------------*/
#ifdef _DEBUG 
void DrawFPS(void);
#endif
#endif // WIN_

//*******************���C������*******************
#ifdef WIN_

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//---------- �ϐ��錾 ----------
	UNREFERENCED_PARAMETER(hPrevInstance);		// �����Ă��ǂ����ǁA�x�����o��i���g�p�錾�j 
	UNREFERENCED_PARAMETER(lpCmdLine);			// �����Ă��ǂ����ǁA�x�����o��i���g�p�錾�j 

	//�t���[�����[�g����p
	DWORD dwExecLastTime;
	DWORD dwFPSLastTime;
	DWORD dwCurrentTime;
	DWORD dwFrameCount;

	WNDCLASSEX wcex;
	HWND hWnd;
	MSG msg;

	//---------- ���������� ----------	
	//�E�B���h�E�N���X�o�^
	wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WndProc,
		0,
		0,
		hInstance,
		NULL,
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		NULL
	};

	//COM���C�u����������
	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	// �E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	// �E�B���h�E�̍쐬 
	hWnd = CreateWindowEx(0,
		CLASS_NAME,
		WINDOW_NAME,
		//WS_OVERLAPPEDWINDOW,
		WS_OVERLAPPEDWINDOW ^ WS_MAXIMIZEBOX ^ WS_THICKFRAME | WS_VISIBLE,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		SCREEN_WIDTH + GetSystemMetrics(SM_CXDLGFRAME) * 2,
		SCREEN_HEIGHT + GetSystemMetrics(SM_CXDLGFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION),
		NULL,
		NULL,
		hInstance,
		NULL);

	// �E�C���h�E�̕\��
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// ����������(�E�B���h�E���쐬���Ă���s��) 
	if (FAILED(InitSystem(hInstance, hWnd, TRUE)))
	{
		return -1;
	}
	//�t���[���J�E���g������ 
	timeBeginPeriod(1);  // ����\��ݒ� 
	dwExecLastTime = dwFPSLastTime = timeGetTime();
	dwCurrentTime = dwFrameCount = 0;

	//�Q�[��������
	Init();

	//���C�����[�v
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{// PostQuitMessage()���Ă΂ꂽ�烋�[�v�I�� 
				break;
			}
			else
			{
				// ���b�Z�[�W�̖|��ƃf�B�X�p�b�` 
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			dwCurrentTime = timeGetTime();
			if ((dwCurrentTime - dwFPSLastTime) >= 500) // 0.5�b���ƂɎ��s 
			{
#ifdef _DEBUG 
				g_nCountFPS = dwFrameCount * 1000 / (dwCurrentTime - dwFPSLastTime);
#endif 

				dwFPSLastTime = dwCurrentTime;
				dwFrameCount = 0;
			}

			//�Q�[���X�V
			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{
				dwExecLastTime = dwCurrentTime;

				// �X�V���� 
				UpDate();

				// �`�揈�� 
				Draw();

				dwFrameCount++;
			}
		}
	}

	//---------- �I������ ----------
	timeEndPeriod(1);    // ����\��߂�
						 // �I������ 
	UnInit();
	// �E�B���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);
	//COM���C�u��������
	CoUninitialize();

	return (int)msg.wParam;
}

/*------------------------------------------------------------------------------------------------------/
I / O:
�@ �\:
-------------------------------------------------------------------------------------------------------*/
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(hWnd);
			return 0;
		}
		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

/*------------------------------------------------------------------------------------------------------/
I / O:
�@ �\:�Q�[�����[�v�O�̃V�X�e��������
-------------------------------------------------------------------------------------------------------*/
HRESULT InitSystem(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DPRESENT_PARAMETERS	d3dpp;
	D3DDISPLAYMODE			d3ddm;
	HRESULT					hr;

	// Direct3D�I�u�W�F�N�g�̍쐬 
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}

	// ���݂̃f�B�X�v���C���[�h���擾 
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// �f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ� 
	ZeroMemory(&d3dpp, sizeof(d3dpp));					// ���[�N���[���N���A
	d3dpp.BackBufferCount = 1;							// �o�b�N�o�b�t�@�̐� 
	d3dpp.BackBufferWidth = (UINT)SCREEN_WIDTH;			// �Q�[����ʃT�C�Y(��)
	d3dpp.BackBufferHeight = (UINT)SCREEN_HEIGHT;		// �Q�[����ʃT�C�Y(����) 
	d3dpp.BackBufferFormat = d3ddm.Format;				// �o�b�N�o�b�t�@�t�H�[�}�b�g�� �f�B�X�v���C���[�h�ɍ��킹�Đݒ�
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;			// �f���M���ɓ������ăt���b�v�� ��
	d3dpp.Windowed = bWindow;							// �E�B���h�E���[�h
	d3dpp.EnableAutoDepthStencil = TRUE;				// �f�v�X�o�b�t�@�i�y�o�b�t�@�j �ƃX�e���V���o�b�t�@���쐬 
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;		// �f�v�X�o�b�t�@�Ƃ���16bit�� �g��

	if (bWindow)
	{		// �E�B���h�E���[�h 
		d3dpp.FullScreen_RefreshRateInHz = 0;			// ���t���b�V�����[ �g 
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE; // �C���^�[�o�� 
	}
	else
	{	// �t���X�N���[�����[�h 
		d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT; // ���t���b�V�����[ �g 
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT; // �C���^�[�o�� 
	}

	// �f�o�C�X�I�u�W�F�N�g�̐��� 
	// [�f�o�C�X�쐬����]<�`��>��<���_����>���n�[�h�E�F�A�ōs�Ȃ� 
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &g_pD3DDevice)))
	{
		// ��L�̐ݒ肪���s������ 
		// [�f�o�C�X�쐬����]<�`��>���n�[�h�E�F�A�ōs���A<���_����>��CPU�ōs�Ȃ� 
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &g_pD3DDevice)))
		{
			// ��L�̐ݒ肪���s������ 
			// [�f�o�C�X�쐬����]<�`��>��<���_����>��CPU�ōs�Ȃ� 
			if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &g_pD3DDevice)))
			{
				// ���������s 
				return E_FAIL;
			}
		}
	}

	// �����_�[�X�e�[�g�p�����[�^�̐ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);		// ���ʂ��J�����O 
	g_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);				// Z�o�b�t�@���g�p 
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);		// ���u�����h���s�� 
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA); // ���\�[�X�J���[�� �w�� 
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA); // ���f�X�e�B�l�[�V�����J���[�̎w�� 

																		 // �T���v���[�X�e�[�g�p�����[�^�̐ݒ� 
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP); // �e�N�X�`���A�h�� �b�V���O���@(U�l)��ݒ� 
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP); // �e�N�X�`���A�h�� �b�V���O���@(V�l)��ݒ� 
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT); // �e�N�X�`���k���t �B���^���[�h��ݒ� 
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT); // �e�N�X�`���g��t �B���^���[�h��ݒ� 
																		//LINEAR����ύX����
																		// �e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ� 
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE); // �A���t�@�u�����f �B���O���� 
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE); // �ŏ��̃A���t�@�� �� 
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT); // �Q�Ԗڂ̃A���t�@ ���� 


#ifdef _DEBUG 
																			// ���\���p�t�H���g��ݒ� 
	D3DXCreateFont(g_pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Terminal"), &g_pD3DXFont);
#endif
	//�������������������������������������������ɏ�����������`��������������������������������������������
	//DirectInput������
	hr = InitDInput(hWnd);	
	if (SUCCEEDED(hr)) {
#ifdef USE_WIN_SOUND
		hr = InitSound(hWnd);
#endif // USE_WIN_SOUND
		InitFade();
		
	}
	return hr;
}


/*------------------------------------------------------------------------------------------------------/
I / O:
�@ �\:�Q�[�����̏�ԕω������̏�����
-------------------------------------------------------------------------------------------------------*/
void Init(void)
{
	InitScene();
}

/*------------------------------------------------------------------------------------------------------/
I / O:
�@ �\:�Q�[�����̍X�V����
-------------------------------------------------------------------------------------------------------*/
void UpDate(void)
{
	//DI�X�V����
	UpdateDInput();

	UpdateScene();

}

/*------------------------------------------------------------------------------------------------------/
I / O:
�@ �\:�Q�[�����̕`�揈��
-------------------------------------------------------------------------------------------------------*/
void Draw()
{
	// �o�b�N�o�b�t�@ �� �y�o�b�t�@ ���X�e���V���o�b�t�@ �̃N���A 
	g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);
	
	// Direct3D�ɂ��`��̊J�n 
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		
		//�`�揈���L����

		DrawScene();
#ifdef _DEBUG 
		// FPS�\�� 
		DrawFPS();
#endif 

		// Direct3D�ɂ��`��̏I�� 
		g_pD3DDevice->EndScene();
	}

	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ� 
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

/*------------------------------------------------------------------------------------------------------/
I / O:
�@ �\:�Q�[���I�����̏I������
-------------------------------------------------------------------------------------------------------*/
void UnInit()
{
	//DI�I������
#ifdef USE_WIN_SOUND
	StopSound();
	UninitSound();
#endif // uSE_WIN_SOUND

	
	UninitDInput();
	
	UninitScene();
	UninitFade();
	
#ifdef _DEBUG 
	if (g_pD3DXFont != NULL)
	{	// ���\���p�t�H���g�̊J�� 
		g_pD3DXFont->Release();
		g_pD3DXFont = NULL;
	}
#endif 
	if (g_pD3DDevice != NULL)
	{	// �f�o�C�X�̊J�� 
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	if (g_pD3D != NULL)
	{	// Direct3D�I�u�W�F�N�g�̊J�� 
		g_pD3D->Release();
		g_pD3D = NULL;
	}
}

/*------------------------------------------------------------------------------------------------------/
I / O:
�@ �\:
-------------------------------------------------------------------------------------------------------*/
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}

#ifdef _DEBUG 
/*------------------------------------------------------------------------------------------------------/
I / O:
�@ �\:
-------------------------------------------------------------------------------------------------------*/
void DrawFPS(void)
{
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	TCHAR str[256];

	wsprintf(str, _T("FPS:%d\n"), g_nCountFPS);

	// �e�L�X�g�`�� 
	g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(255, 255, 255, 255));
}

static int OnCreate(HWND hWnd, LPCREATESTRUCT lpcs) {
	RECT rcWnd, rcClnt;
	SIZE sizeWnd;

	GetWindowRect(hWnd, &rcWnd);
	GetClientRect(hWnd, &rcClnt);

	sizeWnd.cx = (rcWnd.right - rcWnd.left) - (rcClnt.right - rcClnt.left) + SCREEN_WIDTH;
	sizeWnd.cy = (rcWnd.bottom - rcWnd.top) - (rcClnt.bottom - rcClnt.top) + SCREEN_HEIGHT;
}
#endif
#endif // WIN_