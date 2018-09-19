//���d�C���N���[�h�h�~
#ifndef _SCENEMGR_H_
#define _SCENEMGR_H_

//*************** �C���N���[�h ***************
#include "baseScene.h"
#include "sceneStageSelect.h"
#include "sceneTitle.h"
#include "sceneStageClear.h"
#include "sceneGameOver.h"
#include "stageManager.h"

//*************** �萔�E�}�N�� ***************

/*---------------------------------------------
�Q�[���̃V�[���ԍ�	SCENE_NUM_******
---------------------------------------------*/
typedef enum {
	//------------------------------------------
	SCENE_NUM_TITLE,			//�^�C�g��
	SCENE_NUM_STAGE_SELECT,	//�X�e�[�W�I��
	//------------------------------------------
	SCENE_NUM_GAME,			//�Q�[����
	SCENE_NUM_STAGECLEAR,
	SCENE_NUM_GAMEOVER,
	//------------------------------------------
	SCENE_NUM_MAX,

}SCENE_NUM;

//��ݔԍ��i�[�p�\����
typedef struct {
	SCENE_NUM sceneNum;
	SCENE_NUM sceneNumNext;
}SCENE;

class C_SCENE_MANAGER {
private:
	
	C_SCENE_TITLE		*m_TitleObject;	//�^�C�g���I�u�W�F�N�g�|�C���^
	C_SCENE_STAGESELECT *m_StageselectObject; //�X�e�[�W�Z���N�g��ʃI�u�W�F�N�g�|�C���^
	C_STAGE_MANAGER		*m_StageObject; //�Q�[�����C���I�u�W�F�N�g�|�C���^
	C_SCENE_STAGE_CLEAR *m_StageclearObject;//�X�e�[�W�N���A
	C_SCENE_GAME_OVER	*m_GameoverObject;	//�Q�[���I�[�o�[

	C_BASE_SCENE		*m_CurrentSceneObject;	//�V�[���Ǘ��p���ۃ|�C���^
	SCENE				m_Scene;				//�V�[���ԍ��i�[
	STAGE				m_Stage;				//�X�e�[�W�ԍ��i�[
	
public:
	C_SCENE_MANAGER();
	//������
	void Init();
	//�I������
	void Uninit();
	//�X�V
	void Update();
	//�`��
	void Draw();

	void RegisterCurrentSceneObject();
	void ReleaseCurrentSceneObject();

	void SetScene(SCENE_NUM num);
	SCENE GetScene();

	void SetStage(STAGE_NUM);
	STAGE GetStage();

	void enableStageClear();

	void SetStageClear(bool);
};


void InitScene();

void UninitScene();

void UpdateScene();

void DrawScene();

void SetScene(SCENE_NUM num);

SCENE GetScene(void);

void SetStage(STAGE_NUM);

STAGE GetStage();

void enableStageClear();

void SetStageClear(bool);

#endif // !_SCENEMGR_H_