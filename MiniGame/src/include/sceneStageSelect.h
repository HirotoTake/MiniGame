//���d�C���N���[�h�h�~
#ifndef _SCENE_STAGESELECT_H_
#define _SCENE_STAGESELECT_H_

//*************** �C���N���[�h ***************
#include "common.h"
#include "baseScene.h"

//*************** �萔�E�}�N�� ***************

//�X�e�[�W�Z���N�g��ʃN���X
class C_SCENE_STAGESELECT : public C_BASE_SCENE {
	
public:
	void Init() override;
	void Uninit() override;
	void Update() override;
};


#endif // !_SCENE_STAGESELECT_H_
