//background.h
//�w�i����
#ifndef ___BACKGROUND_H___
#define ___BACKGROUND_H___

//===================================================
// �C���N���[�h��
//===================================================
#include "include\main.h"
#include "polygon.h"
#include "objectMgr.h"

//�w�i�N���X
//�V�[���ԍ����玩���Ńe�N�X�`�����擾
class C_BACKGROUND : public C_OBJECT {
public:
	void Init() override;
	void Update() override {};
};
//===================================================
// �v���g�^�C�v�錾
//===================================================
void InitBG();

#endif // ___BACKGROUND_H___
