

//*************** インクルード ***************
#include "include\main.h"
#include "include\common.h"
//マネージャ
#include "include\sceneMgr.h"
#include "include\fade.h"


//*************** 定数・マクロ ***************




//***************グローバル宣言***************
#ifdef WIN_
//システム系
LPDIRECT3D9  g_pD3D = NULL;						// Direct3D オブジェクト 
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;			// Deviceオブジェクト(描画に必要)
#ifdef _DEBUG 
LPD3DXFONT g_pD3DXFont = NULL;					// フォントへのポインタ 
int  g_nCountFPS;								// FPSカウンタ 
#endif
#endif // WIN_




//*************** プロトタイプ ***************
#ifdef WIN_


/*------------------------------------------------------------------------------------------------------/
I / O:
機 能:プロシージャ
-------------------------------------------------------------------------------------------------------*/
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

/*------------------------------------------------------------------------------------------------------/
I / O:
機 能:ゲームループ前のシステム初期化
-------------------------------------------------------------------------------------------------------*/
HRESULT InitSystem(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
#endif // WIN_

/*------------------------------------------------------------------------------------------------------/
I / O:
機 能:ゲーム中の状態変化時等の初期化
-------------------------------------------------------------------------------------------------------*/
void Init(void);

/*------------------------------------------------------------------------------------------------------/
I / O:
機 能:ゲーム中の更新処理
-------------------------------------------------------------------------------------------------------*/
void UpDate(void);

/*------------------------------------------------------------------------------------------------------/
I / O:
機 能:ゲーム中の描画処理
-------------------------------------------------------------------------------------------------------*/
void Draw(void);

/*------------------------------------------------------------------------------------------------------/
I / O:
機 能:ゲーム終了時の終了処理
-------------------------------------------------------------------------------------------------------*/
void UnInit(void);

#ifdef WIN_

/*------------------------------------------------------------------------------------------------------/
I / O:
機 能:
-------------------------------------------------------------------------------------------------------*/
#ifdef _DEBUG 
void DrawFPS(void);
#endif
#endif // WIN_

//*******************メイン処理*******************
#ifdef WIN_

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//---------- 変数宣言 ----------
	UNREFERENCED_PARAMETER(hPrevInstance);		// 無くても良いけど、警告が出る（未使用宣言） 
	UNREFERENCED_PARAMETER(lpCmdLine);			// 無くても良いけど、警告が出る（未使用宣言） 

	//フレームレート制御用
	DWORD dwExecLastTime;
	DWORD dwFPSLastTime;
	DWORD dwCurrentTime;
	DWORD dwFrameCount;

	WNDCLASSEX wcex;
	HWND hWnd;
	MSG msg;

	//---------- 初期化処理 ----------	
	//ウィンドウクラス登録
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

	//COMライブラリ初期化
	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	// ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	// ウィンドウの作成 
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

	// ウインドウの表示
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// 初期化処理(ウィンドウを作成してから行う) 
	if (FAILED(InitSystem(hInstance, hWnd, TRUE)))
	{
		return -1;
	}
	//フレームカウント初期化 
	timeBeginPeriod(1);  // 分解能を設定 
	dwExecLastTime = dwFPSLastTime = timeGetTime();
	dwCurrentTime = dwFrameCount = 0;

	//ゲーム初期化
	Init();

	//メインループ
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{// PostQuitMessage()が呼ばれたらループ終了 
				break;
			}
			else
			{
				// メッセージの翻訳とディスパッチ 
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			dwCurrentTime = timeGetTime();
			if ((dwCurrentTime - dwFPSLastTime) >= 500) // 0.5秒ごとに実行 
			{
#ifdef _DEBUG 
				g_nCountFPS = dwFrameCount * 1000 / (dwCurrentTime - dwFPSLastTime);
#endif 

				dwFPSLastTime = dwCurrentTime;
				dwFrameCount = 0;
			}

			//ゲーム更新
			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{
				dwExecLastTime = dwCurrentTime;

				// 更新処理 
				UpDate();

				// 描画処理 
				Draw();

				dwFrameCount++;
			}
		}
	}

	//---------- 終了処理 ----------
	timeEndPeriod(1);    // 分解能を戻す
						 // 終了処理 
	UnInit();
	// ウィンドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);
	//COMライブラリ閉じる
	CoUninitialize();

	return (int)msg.wParam;
}

/*------------------------------------------------------------------------------------------------------/
I / O:
機 能:
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
機 能:ゲームループ前のシステム初期化
-------------------------------------------------------------------------------------------------------*/
HRESULT InitSystem(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DPRESENT_PARAMETERS	d3dpp;
	D3DDISPLAYMODE			d3ddm;
	HRESULT					hr;

	// Direct3Dオブジェクトの作成 
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}

	// 現在のディスプレイモードを取得 
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// デバイスのプレゼンテーションパラメータの設定 
	ZeroMemory(&d3dpp, sizeof(d3dpp));					// ワークをゼロクリア
	d3dpp.BackBufferCount = 1;							// バックバッファの数 
	d3dpp.BackBufferWidth = (UINT)SCREEN_WIDTH;			// ゲーム画面サイズ(幅)
	d3dpp.BackBufferHeight = (UINT)SCREEN_HEIGHT;		// ゲーム画面サイズ(高さ) 
	d3dpp.BackBufferFormat = d3ddm.Format;				// バックバッファフォーマットは ディスプレイモードに合わせて設定
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;			// 映像信号に同期してフリップす る
	d3dpp.Windowed = bWindow;							// ウィンドウモード
	d3dpp.EnableAutoDepthStencil = TRUE;				// デプスバッファ（Ｚバッファ） とステンシルバッファを作成 
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;		// デプスバッファとして16bitを 使う

	if (bWindow)
	{		// ウィンドウモード 
		d3dpp.FullScreen_RefreshRateInHz = 0;			// リフレッシュレー ト 
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE; // インターバル 
	}
	else
	{	// フルスクリーンモード 
		d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT; // リフレッシュレー ト 
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT; // インターバル 
	}

	// デバイスオブジェクトの生成 
	// [デバイス作成制御]<描画>と<頂点処理>をハードウェアで行なう 
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &g_pD3DDevice)))
	{
		// 上記の設定が失敗したら 
		// [デバイス作成制御]<描画>をハードウェアで行い、<頂点処理>はCPUで行なう 
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &g_pD3DDevice)))
		{
			// 上記の設定が失敗したら 
			// [デバイス作成制御]<描画>と<頂点処理>をCPUで行なう 
			if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &g_pD3DDevice)))
			{
				// 初期化失敗 
				return E_FAIL;
			}
		}
	}

	// レンダーステートパラメータの設定
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);		// 裏面をカリング 
	g_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);				// Zバッファを使用 
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);		// αブレンドを行う 
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA); // αソースカラーの 指定 
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA); // αデスティネーションカラーの指定 

																		 // サンプラーステートパラメータの設定 
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP); // テクスチャアドレ ッシング方法(U値)を設定 
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP); // テクスチャアドレ ッシング方法(V値)を設定 
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT); // テクスチャ縮小フ ィルタモードを設定 
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT); // テクスチャ拡大フ ィルタモードを設定 
																		//LINEARから変更した
																		// テクスチャステージステートの設定 
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE); // アルファブレンデ ィング処理 
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE); // 最初のアルファ引 数 
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT); // ２番目のアルファ 引数 


#ifdef _DEBUG 
																			// 情報表示用フォントを設定 
	D3DXCreateFont(g_pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Terminal"), &g_pD3DXFont);
#endif
	//＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊ここに初期化処理を描く＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊
	//DirectInput初期化
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
機 能:ゲーム中の状態変化時等の初期化
-------------------------------------------------------------------------------------------------------*/
void Init(void)
{
	InitScene();
}

/*------------------------------------------------------------------------------------------------------/
I / O:
機 能:ゲーム中の更新処理
-------------------------------------------------------------------------------------------------------*/
void UpDate(void)
{
	//DI更新処理
	UpdateDInput();

	UpdateScene();

}

/*------------------------------------------------------------------------------------------------------/
I / O:
機 能:ゲーム中の描画処理
-------------------------------------------------------------------------------------------------------*/
void Draw()
{
	// バックバッファ ＆ Ｚバッファ ＆ステンシルバッファ のクリア 
	g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);
	
	// Direct3Dによる描画の開始 
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		
		//描画処理記入↓

		DrawScene();
#ifdef _DEBUG 
		// FPS表示 
		DrawFPS();
#endif 

		// Direct3Dによる描画の終了 
		g_pD3DDevice->EndScene();
	}

	// バックバッファとフロントバッファの入れ替え 
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

/*------------------------------------------------------------------------------------------------------/
I / O:
機 能:ゲーム終了時の終了処理
-------------------------------------------------------------------------------------------------------*/
void UnInit()
{
	//DI終了処理
#ifdef USE_WIN_SOUND
	StopSound();
	UninitSound();
#endif // uSE_WIN_SOUND

	
	UninitDInput();
	
	UninitScene();
	UninitFade();
	
#ifdef _DEBUG 
	if (g_pD3DXFont != NULL)
	{	// 情報表示用フォントの開放 
		g_pD3DXFont->Release();
		g_pD3DXFont = NULL;
	}
#endif 
	if (g_pD3DDevice != NULL)
	{	// デバイスの開放 
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	if (g_pD3D != NULL)
	{	// Direct3Dオブジェクトの開放 
		g_pD3D->Release();
		g_pD3D = NULL;
	}
}

/*------------------------------------------------------------------------------------------------------/
I / O:
機 能:
-------------------------------------------------------------------------------------------------------*/
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}

#ifdef _DEBUG 
/*------------------------------------------------------------------------------------------------------/
I / O:
機 能:
-------------------------------------------------------------------------------------------------------*/
void DrawFPS(void)
{
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	TCHAR str[256];

	wsprintf(str, _T("FPS:%d\n"), g_nCountFPS);

	// テキスト描画 
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