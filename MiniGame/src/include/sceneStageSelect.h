//多重インクルード防止
#ifndef _SCENE_STAGESELECT_H_
#define _SCENE_STAGESELECT_H_

//*************** インクルード ***************
#include "common.h"
#include "baseScene.h"

//*************** 定数・マクロ ***************

//ステージセレクト画面クラス
class C_SCENE_STAGESELECT : public C_BASE_SCENE {
	
public:
	void Init() override;
	void Uninit() override;
	void Update() override;
};


#endif // !_SCENE_STAGESELECT_H_
