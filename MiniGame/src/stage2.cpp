
//********** �C���N���[�h **********
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
	

	//�t�F�[�h�C��������
	if (EndFadeIn())
	{//�X�y�[�X�Ŏ���ʂֈڍs
		if (DIGetKeyTrigger(DIK_RETURN))
			StartFadeOut();

	}
	if (EndFadeOut()) {//�t�F�[�h�A�E�g�I���㎟�V�[���̔ԍ��Z�b�g�@���@������
		if (clear) SetScene(SCENE_NUM_STAGECLEAR);
		else SetScene(SCENE_NUM_GAMEOVER);
	}
}

void C_STAGE_2::enableStageClear()
{
	StartFadeOut();
}