
//********** �C���N���[�h **********
#include "include\common.h"
#include "include\sceneStageClear.h"
#include "include\sceneMgr.h"
#include "include\objectMgr.h"
#include "include\fade.h"
#include "include\background.h"


//********** �v���g�^�C�v **********

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
	//�e���A�b�v�f�[�g

	//�t�F�[�h�C��������
	if (EndFadeIn())
	{//�X�y�[�X�Ŏ���ʂֈڍs
		if (DIGetKeyTrigger(DIK_SPACE)) {
			StartFadeOut();
#ifdef USE_WIN_SOUND
			PlaySound(SOUND_LABEL_SE_SELECT);
#endif // USE_WIN_SOUND

		}
	}
	if (EndFadeOut())//�t�F�[�h�A�E�g�I���㎟�V�[���̔ԍ��Z�b�g�@���@������
		SetScene(SCENE_NUM_STAGE_SELECT);
}

