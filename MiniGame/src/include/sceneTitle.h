//���d�C���N���[�h�h�~
#ifndef _SCENE_TITLE_H_
#define _SCENE_TITLE_H_


//*************** �C���N���[�h ***************
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
