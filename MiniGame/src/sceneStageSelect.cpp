

//********** �C���N���[�h **********
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
	//�e���A�b�v�f�[�g
	
	if (EndFadeOut())//�t�F�[�h�A�E�g�I���㎟�V�[���̔ԍ��Z�b�g�@���@������
	{
		SetScene(SCENE_NUM_GAME);
	}
	
	
}
