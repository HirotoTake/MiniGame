//多重インクルード防止
#ifndef _MAIN_H_
#define _MAIN_H_
/*------------------------------------------------------------------------------------------------------/

[ファイル名	:main.h]
	製作者	:AT12B171 竹山広人
	概要	:

-------------------------------------------------------------------------------------------------------*/

//*************** インクルード ***************
#include "common.h"

#ifdef WIN_

//ライブラリ
#if 1 // [ここを"0"にした場合、"構成プロパティ" -> "リンカ" -> "入力" -> "追加の依存ファイル "に対象ライブラリを設定する] 
#pragma comment (lib, "d3d9.lib") 
#pragma comment (lib, "d3dx9.lib") 
#pragma comment (lib, "dxguid.lib") 
#pragma comment (lib,"dsound.lib")
#pragma comment (lib, "winmm.lib") 
#endif 

//*************** 定数・マクロ ***************
#define CLASS_NAME  _T("AppClass")			// ウインドウのクラス名
#define WINDOW_NAME  _T("MyGame")	// ウインドウのキャプション

//*************** プロトタイプ ***************
LPDIRECT3DDEVICE9 GetDevice(void);

#endif // WIN_


#endif // !_MAIN_H_
