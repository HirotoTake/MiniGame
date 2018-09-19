
//********** インクルード **********
#include "include\common.h"
#include "include\sceneStageClear.h"
#include "include\sceneMgr.h"
#include "include\objectMgr.h"
#include "include\fade.h"
#include "include\background.h"


//********** プロトタイプ **********

void C_SCENE_STAGE_CLEAR::Init(){
	StartFadeIn();
	InitBG();

	
	
#ifdef USE_WIN_SOUND
	PlaySound(SOUND_LABEL_STAGE_CLEAR);
#endif // USE_WIN_SOUND
	}

void C_SCENE_STAGE_CLEAR::Uninit(){
#ifdef USE_WIN_SOUND
	StopSound(SOUND_LABEL_STAGE_CLEAR);
#endif // USE_WIN_SOUND
}

void C_SCENE_STAGE_CLEAR::Update()
{
	//各情報アップデート

	//フェードイン完了後
	if (EndFadeIn())
	{//スペースで次画面へ移行
		if (DIGetKeyTrigger(DIK_SPACE)) {
			StartFadeOut();
#ifdef USE_WIN_SOUND
			PlaySound(SOUND_LABEL_SE_SELECT);
#endif // USE_WIN_SOUND

		}
	}
	if (EndFadeOut())//フェードアウト終了後次シーンの番号セット　→　初期化
		SetScene(SCENE_NUM_STAGE_SELECT);
}

