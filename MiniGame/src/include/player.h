#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "polygon.h"
#include "character.h"



//���N���X:C_CHARACTER, C_PLAYER_STATUS 
//�T�v:�v���C���[�N���X
class C_PLAYER :public C_CHARACTER{
private:
	
public:
	//�X�V�p�����o�ϐ�
	D3DXVECTOR3 m_move;	//���W�X�V�p�ړ���
	D3DXVECTOR3 m_accel; //���W�X�V�p�����x
	CHARACTER_STATUS m_status;	//�X�e�[�^�X�X�V�p

	//�v���C���[�X�e�[�^�X�Z�b�g
	void Init() override;

	void Update() override;

};


#endif // !_PLAYER_H_