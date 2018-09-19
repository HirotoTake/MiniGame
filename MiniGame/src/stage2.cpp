
//********** インクルード **********
#include "include\stage2.h"
#include "include\sceneMgr.h"
#include "include\stageManager.h"

#include "include\input.h"
#include "include\background.h"
#include "include\player.h"
#include "include\fade.h"

void C_STAGE_2::Init(){
	StartFadeIn();
	
	AddObject(m_player = new C_PLAYER);
	
	
}

void C_STAGE_2::Uninit(){
	
}

void C_STAGE_2::Update(){
	

	//フェードイン完了後
	if (EndFadeIn())
	{//スペースで次画面へ移行
		if (DIGetKeyTrigger(DIK_RETURN))
			StartFadeOut();

	}
	if (EndFadeOut()) {//フェードアウト終了後次シーンの番号セット　→　初期化
		if (clear) SetScene(SCENE_NUM_STAGECLEAR);
		else SetScene(SCENE_NUM_GAMEOVER);
	}
}

void C_STAGE_2::enableStageClear()
{
	StartFadeOut();
}