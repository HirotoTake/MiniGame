

//********** インクルード **********
#include "include\stageManager.h"
#include "include\sceneMgr.h"
#include "include\common.h"
#include "include\fade.h"
#include "include\background.h"
#include "include\stage1.h"
//********** 定数・マクロ **********


C_STAGE_MANAGER::C_STAGE_MANAGER() {
	m_stage = GetStage();

	m_currentStage = NULL;
	m_stage1 = NULL;
	m_stage2 = NULL;
}

void C_STAGE_MANAGER::Init() {

	InitTex();
	InitBG();
	//void (*func[])() = {InitTex, InitBG, InitBlock, NULL};
	//for (int i = 0; i != NULL; i++) func[i]();

	m_stage = GetStage();
	switch (m_stage.stageNum) {
		case STAGE_NUM_STAGE_1:
			m_currentStage = m_stage1 = new C_STAGE_1;
			break;
		case STAGE_NUM_STAGE_2:
			m_currentStage = m_stage2 = new C_STAGE_2;
			break;
		case STAGE_NUM_STAGE_3:
			m_currentStage = m_stage2 = new C_STAGE_2;
			break;
	}
	m_currentStage->Init();

#ifdef USE_WIN_SOUND
	PlaySound(SOUND_LABEL_STAGE);
#endif // USE_WIN_SOUND
	
}

void C_STAGE_MANAGER::Uninit() {
	m_currentStage->Uninit();

	switch (m_stage.stageNum) {
	case STAGE_NUM_STAGE_1:
		delete m_stage1;
		break;
	case STAGE_NUM_STAGE_2:
		delete m_stage1;
		break;
	case STAGE_NUM_STAGE_3:
		delete m_stage1;
		break;
	}

#ifdef USE_WIN_SOUND
	StopSound();
#endif // USE_WIN_SOUND	
}

void C_STAGE_MANAGER::Update() {
	m_currentStage->Update();

	if (m_stage.stageNum != m_stage.stageNumNext){
		m_currentStage->Uninit();

		m_stage.stageNum = m_stage.stageNumNext;

		m_currentStage->Init();
	}
}

void C_STAGE_MANAGER::SetStage(STAGE_NUM num) {
	m_stage.stageNumNext = num;
}

void C_STAGE_MANAGER::enableStageClear()
{
	m_currentStage->enableStageClear();
}

void C_STAGE_MANAGER::SetStageClear(bool flag)
{
	m_currentStage->SetStageClear(flag);
}