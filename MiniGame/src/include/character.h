#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include "object.h"

#define MAX_NAME (20)

enum {
	CHARACTER_ID_PLAYER = 0,
	CHARACTER_ID_MAX,
};

typedef struct {
	unsigned char charaId;	//�L�������ʔԍ�
	D3DXVECTOR3 worldPos;	//���[���h���W

	
	int nLife;	//�̗�
	bool bJump;	//�W�����v�t���O
	bool bUnder; //���i�~��
	int nDirOld;
	int nDir;
}CHARACTER_STATUS;

//���̃N���X�̌p����:C_POLYGON_2D, C_OBJECT
//�T�v:�L�����N�^�[�̊�{�N���X
class C_CHARACTER  : public C_OBJECT{
private:
	CHARACTER_STATUS m_status;	//�L�������
public:
	void SetStatus(CHARACTER_STATUS *status) { this->m_status = *status; }

	CHARACTER_STATUS GetStatus() { return this->m_status; }
};


#endif // !_PLAYER_H_