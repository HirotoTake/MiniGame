//多重インクルード防止
#ifndef _SCENE_TITLE_H_
#define _SCENE_TITLE_H_


//*************** インクルード ***************
#include "baseScene.h"
#include "common.h"


class C_SCENE_TITLE : public C_BASE_SCENE {
private:
	
public:
	void Init() override;
	void Uninit() override;
	void Update() override;
};

#endif // !_SCENE_TITLE_H_
