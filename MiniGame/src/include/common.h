//多重インクルード防止
#ifndef _COMMON_H_
#define _COMMON_H_

#define WIN_ //Windows用

#ifdef WIN_

//*************** インクルード ***************
#include <windows.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <tchar.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "input.h"
#include "sound.h"
#endif // WIN_



//*************** 定数・マクロ ***************
//スクリーン用
#ifdef WIN_
#define SCREEN_WIDTH (854)						// ウインドウの幅 
#define SCREEN_HEIGHT (480)						// ウインドウの高さ
#endif // WIN_


#define SCREEN_CENTER_X (SCREEN_WIDTH / 2)		// ウインドウの中心Ｘ座標 
#define SCREEN_CENTER_Y (SCREEN_HEIGHT / 2)		// ウインドウの中心Ｙ座標 

#define SCREEN_LIMIT_UNDER (SCREEN_HEIGHT  - 10.0f)
#define SCREEN_LIMIT_LEFT	(20.0f)
#define SCREEN_LIMIT_RIGHT (SCREEN_WIDTH - SCREEN_LIMIT_LEFT)

#define ARRAY_LENGTH(ary) (sizeof(ary) / sizeof(ary[0]))	//要素数を返す

//*************** 構造体 ***************

//*************** 列挙型 ***************



//*************** プロトタイプ ***************

#endif // !_COMMON_H_
