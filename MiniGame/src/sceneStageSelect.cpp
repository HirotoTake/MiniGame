

//********** インクルード **********
#include "include\sceneMgr.h"
#include "include\stageManager.h"
#include "include\background.h"
#include "include\sceneStageSelect.h"
#include "include\fade.h"



void C_SCENE_STAGESELECT::Init()
{
	StartFadeIn();
	InitBG();
	

#ifdef USE_WIN_SOUND
	PlaySound(SOUND_LABEL_STAGE_SELECT);
#endif // USE_WIN_SOUND
}

void C_SCENE_STAGESELECT::Uninit()
{
#ifdef USE_WIN_SOUND
	StopSound(SOUND_LABEL_STAGE_SELECT);
#endif // USE_WIN_SOUND
}

void C_SCENE_STAGESELECT::Update()
{
	//各情報アップデート
	
	if (EndFadeOut())//フェードアウト終了後次シーンの番号セット　→　初期化
	{
		SetScene(SCENE_NUM_GAME);
	}
	
	
}
