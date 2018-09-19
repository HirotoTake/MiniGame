#ifndef _SOUND_H_
#define _SOUND_H_
//#define USE_WIN_SOUND


#ifdef USE_WIN_SOUND

#include "main.h"

#include <xaudio2.h>

//*****************************************************************************
// サウンドファイル
//*****************************************************************************
typedef enum
{
	SOUND_LABEL_TITLE = 0,		// BGM0
	SOUND_LABEL_STAGE_SELECT,		// BGM0
	SOUND_LABEL_STAGE,			// BGM1
	SOUND_LABEL_GAMEOVER,		// BGM2
	SOUND_LABEL_STAGE_CLEAR,
	SOUND_LABEL_SE_DECIDE,		// 決定音
	SOUND_LABEL_SE_SELECT,		// 選択音
	SOUND_LABEL_SE_JUMP,		// ジャンプ音
	SOUND_LABEL_SE_KAIDAN,		//会談
	SOUND_LABEL_MAX,			// 登録数の自動設定
} SOUND_LABEL;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);

HRESULT PlaySound(SOUND_LABEL label);

void StopSound(SOUND_LABEL label);
void StopSound(void);



#endif // USE_WIN_SOUND

#endif
