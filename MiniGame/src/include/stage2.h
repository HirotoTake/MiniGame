//���d�C���N���[�h�h�~
#ifndef _STAGE2_H_
#define _STAGE2_H_

#include "baseStage.h"
#include "object.h"
#include "player.h"


class C_STAGE_2 : public C_BASE_STAGE {
	C_PLAYER *m_player;	//�v���C���[�I�u�W�F�N�g
	
public:

	void Init() override;

	void Uninit() override;

	void Update() override;

	void enableStageClear() override;
};



#endif // !_STAGE1_H_
