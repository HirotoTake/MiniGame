//多重インクルード防止
#ifndef _SCENEMGR_H_
#define _SCENEMGR_H_

//*************** インクルード ***************
#include "baseScene.h"
#include "sceneStageSelect.h"
#include "sceneTitle.h"
#include "sceneStageClear.h"
#include "sceneGameOver.h"
#include "stageManager.h"

//*************** 定数・マクロ ***************

/*---------------------------------------------
ゲームのシーン番号	SCENE_NUM_******
---------------------------------------------*/
typedef enum {
	//------------------------------------------
	SCENE_NUM_TITLE,			//タイトル
	SCENE_NUM_STAGE_SELECT,	//ステージ選択
	//------------------------------------------
	SCENE_NUM_GAME,			//ゲーム中
	SCENE_NUM_STAGECLEAR,
	SCENE_NUM_GAMEOVER,
	//------------------------------------------
	SCENE_NUM_MAX,

}SCENE_NUM;

//ｼｰﾝ番号格納用構造体
typedef struct {
	SCENE_NUM sceneNum;
	SCENE_NUM sceneNumNext;
}SCENE;

class C_SCENE_MANAGER {
private:
	
	C_SCENE_TITLE		*m_TitleObject;	//タイトルオブジェクトポインタ
	C_SCENE_STAGESELECT *m_StageselectObject; //ステージセレクト画面オブジェクトポインタ
	C_STAGE_MANAGER		*m_StageObject; //ゲームメインオブジェクトポインタ
	C_SCENE_STAGE_CLEAR *m_StageclearObject;//ステージクリア
	C_SCENE_GAME_OVER	*m_GameoverObject;	//ゲームオーバー

	C_BASE_SCENE		*m_CurrentSceneObject;	//シーン管理用抽象ポインタ
	SCENE				m_Scene;				//シーン番号格納
	STAGE				m_Stage;				//ステージ番号格納
	
public:
	C_SCENE_MANAGER();
	//初期化
	void Init();
	//終了処理
	void Uninit();
	//更新
	void Update();
	//描画
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