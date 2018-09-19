//多重インクルード防止
#ifndef _SCENE_STAGE_CLEAR_H_
#define _SCENE_STAGE_CLEAR_H_


//*************** インクルード ***************
#include "baseScene.h"
#include "common.h"


class C_SCENE_STAGE_CLEAR : public C_BASE_SCENE {
private:
	
public:
	void Init() override;
	void Uninit() override;
	void Update() override;
};

#endif // !_SCENE_TITLE_H_
