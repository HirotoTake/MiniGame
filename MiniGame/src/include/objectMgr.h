#ifndef _OBJECT_MANAGER_H_
#define _OBJECT_MANAGER_H_

#include "common.h"
#include "C_BASE_OBJECT_MANAGER.h"
#include "object.h"

//�I�u�W�F�N�g�Ǘ��N���X
//�v���C�x�[�g�����o�̃I�u�W�F�N�g���I�z��ɂĂ��ׂẴI�u�W�F�N�g���ꌳ�Ǘ�����
//�e�V�[���A�X�e�[�W�ɂĐ������ꂽ�I�u�W�F�N�g�͂��̔z��ɒǉ�����A�Ǘ������B
class C_OBJECT_MANAGER {
private:
	std::vector<C_OBJECT*> m_object;
public:
	//������
	void Init();

	//���
	void Uninit();

	void Update();

	void Release();

	void Draw();

	ST_POLYGON_2D GetObjectPolygonInfo(int objectType);	//�I�u�W�F�N�g�̈ʒu���擾

	//�I�u�W�F�N�g�Ǘ��N���X�̃I�u�W�F�N�g�Ǘ��p�x�N�^�[�z��Ƀf�[�^��ǉ�����
	void AddObject(C_OBJECT *objectData) { m_object.push_back(objectData); }

};
void AddObject(C_OBJECT *objectData);

void InitObject();	//�I�u�W�F�N�g������
void UninitObject();	//�I�u�W�F�N�g�I��(���̊֐��ł̓������J���܂ł͂���Ȃ�
void UpdateObject();	//�I�u�W�F�N�g�A�b�v�f�[�g
void DrawObject();	//�I�u�W�F�N�g�`��
void ReleaseObject();	//�I�u�W�F�N�g���(�I�������܂�

//�I�u�W�F�N�g���ʔԍ��擾
ST_POLYGON_2D GetObjectPolygonInfo(int objectType);


#endif // !_OBJECT_MANAGER_H_