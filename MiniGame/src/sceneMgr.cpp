

//********** �C���N���[�h **********
#include "include\sceneMgr.h"
#include "include\fade.h"
#include "include\stageManager.h"
#include "include\textureMgr.h"
#include "include\background.h"
#include "include\sceneTitle.h"
#include "include\sceneStageSelect.h"
#include "include\objectMgr.h"

//********** �萔�E�}�N�� **********
#define STARTSCENE (SCENE_NUM_TITLE)	//�N�����̉��


//**********�O���[�o���錾**********

C_SCENE_MANAGER g_sceneMgr;	//�V�[���Ǘ��I�u�W�F�N�g

//�V�[�������֐�
void InitScene(){
	g_sceneMgr.Init();	
}
void UninitScene() {
	g_sceneMgr.Uninit();
}
void UpdateScene() {
	g_sceneMgr.Update();
}
void DrawScene() {
	g_sceneMgr.Draw();
}

void enableStageClear()
{
	g_sceneMgr.enableStageClear();
}

C_SCENE_MANAGER::C_SCENE_MANAGER() {
	m_Scene.sceneNum = this->m_Scene.sceneNumNext = STARTSCENE;
	m_TitleObject = NULL;
	m_StageselectObject = NULL;
	m_StageObject= NULL;
	m_StageclearObject = NULL;
	m_GameoverObject = NULL;
	m_CurrentSceneObject = NULL;
}

void C_SCENE_MANAGER::Init(){
	//�V�[���I�u�W�F�N�g�C���X�^���X��
	InitTex();
	RegisterCurrentSceneObject();
	//�V�[��������(�I�u�W�F�N�g����
	this->m_CurrentSceneObject->Init();
	
	//�I�u�W�F�N�g������
	InitObject();
}

void C_SCENE_MANAGER::Uninit() {
	//�I�u�W�F�N�g�j��
	ReleaseObject();

	//�V�[���I������
	this->m_CurrentSceneObject->Uninit();

	//�V�[���I�u�W�F�N�g�j��
	ReleaseCurrentSceneObject();
	
	//���݃e�N�X�`���j��
	UninitTex();
}


void C_SCENE_MANAGER::Update() {
#ifndef FADE
	UpdateFade();
#endif // !FADE	

	//�V�[���A�b�v�f�[�g
	this->m_CurrentSceneObject->Update();
	//�I�u�W�F�N�g�A�b�v�f�[�g
	UpdateObject();
	
	if (m_Scene.sceneNum != m_Scene.sceneNumNext) {
		this->Uninit();
		m_Scene.sceneNum = m_Scene.sceneNumNext;
		this->Init();//�e�N�X�`���ēǂݍ���
	}
}

void C_SCENE_MANAGER::Draw() {
	DrawObject();
	DrawFade();
}


void C_SCENE_MANAGER::RegisterCurrentSceneObject()
{
	switch (m_Scene.sceneNum) {
	case SCENE_NUM_TITLE:
		this->m_CurrentSceneObject = this->m_TitleObject = new C_SCENE_TITLE;
		break;
	case SCENE_NUM_STAGE_SELECT:
		this->m_CurrentSceneObject = this->m_StageselectObject = new C_SCENE_STAGESELECT;
		break;
	case SCENE_NUM_GAME:
		this->m_CurrentSceneObject = this->m_StageObject = new C_STAGE_MANAGER;
		break;
	case SCENE_NUM_STAGECLEAR:
		this->m_CurrentSceneObject = this->m_StageclearObject = new C_SCENE_STAGE_CLEAR;
		break;
	case SCENE_NUM_GAMEOVER:
		this->m_CurrentSceneObject = this->m_GameoverObject = new C_SCENE_GAME_OVER;
		break;
	}
}

void C_SCENE_MANAGER::ReleaseCurrentSceneObject()
{
	switch (this->m_Scene.sceneNum) {
	case SCENE_NUM_TITLE:
		delete m_TitleObject;
		this->m_TitleObject = NULL;
		break;
	case SCENE_NUM_STAGE_SELECT:
		delete m_StageselectObject;
		this->m_StageselectObject = NULL;
		break;
	case SCENE_NUM_GAME:
		delete m_StageObject;
		this->m_StageObject = NULL;
		break;
	case SCENE_NUM_STAGECLEAR:
		delete m_StageclearObject;
		this->m_StageclearObject = NULL;
		break;
	case SCENE_NUM_GAMEOVER:
		delete m_GameoverObject;
		this->m_GameoverObject = NULL;
		break;
	}
}

void C_SCENE_MANAGER::SetScene(SCENE_NUM num) {
	m_Scene.sceneNumNext = num;
}

SCENE C_SCENE_MANAGER::GetScene(){
	return m_Scene;
}


void SetScene(SCENE_NUM num) {
	g_sceneMgr.SetScene(num);
}

SCENE GetScene(void) {
	return g_sceneMgr.GetScene();
}

void SetStage(STAGE_NUM num)
{
	g_sceneMgr.SetStage(num);
}


void C_SCENE_MANAGER::SetStage(STAGE_NUM num){
	m_Stage.stageNum = m_Stage.stageNumNext = num;

	if(m_StageObject)//�X�e�[�W�Ǘ��N���X���C���X�^���X������Ă���΂�����ɂ��i�[
		this->m_StageObject->SetStage(num);
}

STAGE C_SCENE_MANAGER::GetStage()
{
	return this->m_Stage;
}

STAGE GetStage()
{
	return g_sceneMgr.GetStage();
}

void C_SCENE_MANAGER::enableStageClear()
{
	m_StageObject->enableStageClear();
}

void SetStageClear(bool flag) {
	g_sceneMgr.SetStageClear(flag);
}

void C_SCENE_MANAGER::SetStageClear(bool flag)
{
	m_StageObject->SetStageClear(flag);
}