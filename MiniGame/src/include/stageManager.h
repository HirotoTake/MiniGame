//���d�C���N���[�h�h�~
#ifndef _STAGEMGR_H_
#define _STAGEMGR_H_

//*************** �C���N���[�h ***************
#include "baseScene.h"
#include "baseStage.h"
#include "stage1.h"
#include "stage2.h"
#include "common.h"
#include "character.h"
//*************** �萔�E�}�N�� ***************
#define STARTSTAGE (STAGE_NUM_STAGE_1)

/*---------------------------------------------
�Q�[���̃X�e�[�W�ԍ�	STAGE_NUM_******
---------------------------------------------*/
typedef enum {
	STAGE_NUM_STAGE_1,	//�����j���O�}��
	STAGE_NUM_STAGE_2,
	STAGE_NUM_STAGE_3,
	STAGE_NUM_MAX,

}STAGE_NUM;

typedef struct {
	STAGE_NUM stageNum;
	STAGE_NUM stageNumNext;
}STAGE;

//��ɃX�e�[�W�Ǘ�������
class C_STAGE_MANAGER : public  C_BASE_SCENE{
private:
	C_BASE_STAGE *m_currentStage;
	C_STAGE_1 *m_stage1;
	C_STAGE_2 *m_stage2;
	STAGE m_stage;

public:
	C_STAGE_MANAGER();
	//������
	void Init() override;
	//�I������
	void Uninit() override;
	//�X�V
	void Update() override;
	//�`��

	void SetStage(STAGE_NUM num);

	void enableStageClear();

	void SetStageClear(bool);
};



#endif // !_STAGEMGR_H_