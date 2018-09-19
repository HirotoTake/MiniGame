//多重インクルード防止
#ifndef _STAGEMGR_H_
#define _STAGEMGR_H_

//*************** インクルード ***************
#include "baseScene.h"
#include "baseStage.h"
#include "stage1.h"
#include "stage2.h"
#include "common.h"
#include "character.h"
//*************** 定数・マクロ ***************
#define STARTSTAGE (STAGE_NUM_STAGE_1)

/*---------------------------------------------
ゲームのステージ番号	STAGE_NUM_******
---------------------------------------------*/
typedef enum {
	STAGE_NUM_STAGE_1,	//ランニングマン
	STAGE_NUM_STAGE_2,
	STAGE_NUM_STAGE_3,
	STAGE_NUM_MAX,

}STAGE_NUM;

typedef struct {
	STAGE_NUM stageNum;
	STAGE_NUM stageNumNext;
}STAGE;

//主にステージ管理をする
class C_STAGE_MANAGER : public  C_BASE_SCENE{
private:
	C_BASE_STAGE *m_currentStage;
	C_STAGE_1 *m_stage1;
	C_STAGE_2 *m_stage2;
	STAGE m_stage;

public:
	C_STAGE_MANAGER();
	//初期化
	void Init() override;
	//終了処理
	void Uninit() override;
	//更新
	void Update() override;
	//描画

	void SetStage(STAGE_NUM num);

	void enableStageClear();

	void SetStageClear(bool);
};



#endif // !_STAGEMGR_H_