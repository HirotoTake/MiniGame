#ifndef _OBJECT_H_
#define _OBJECT_H_

/*------------------------------------------------------------------------------------------------------/

[�t�@�C����	:object.h]
�����	:AT12B171 �|�R�L�l
�T�v	:

-------------------------------------------------------------------------------------------------------*/

//*************** �C���N���[�h ***************
#include "common.h"
#include "polygon.h"



//*************** �萔�E�}�N�� ***************



//*************** �v���g�^�C�v ***************


enum {
	OBJECT_TYPE_DUMMY = 0,	//�_�~�[	
	OBJECT_TYPE_PLAYER = 1,	//�v���C���[���
	OBJECT_TYPE_ENEMY,	//�G
	OBJECT_TYPE_GOAL,	//�S�[���I�u�W�F�N�g
	OBJECT_TYPE_BACKGROUND,	//�w�i
	OBJECT_TYPE_LOGO_TITLE,	//�^�C�g���Ɏg�p�����e���S
	OBJECT_TYPE_UI_STAGE_SELECT,	//�X�e�[�W�I����ʂɎg�p�����UI�Q
	OBJECT_TYPE_FADE,
};



/*
==�I�u�W�F�N�g���ۃN���X==
�g�p���@
�e�Q�[���I�u�W�F�N�g�𐶐�����Ƃ��ɁAC_OBJECT�N���X���p��������
�p����AInit�֐���Update�֐���K���I�[�o���C�h���邱��

!-�������菇-!
1-1.m_objectType�Ɏ��ʔԍ�����
1-2.m_objectNumMax�ɐ�������I�u�W�F�N�g������
1-3.CreateObject�֐����Ăׂ΁A1-2�Őݒ肵�����̔z��̃��������m�ۂ����

!-���_�ݒ���@-!
2-1.m_object�̃����o�ϐ���ST_POLYGON_2D�\���̂�m_polygon2D������A�e�ϐ��Ƀ|���S������ݒ肷��
 or
2-2.���_���z��������Ōv�Z�������Ƃ��́Am_Vtx���g�p����B

2-3.m_polygon2D��isUseTex�ŁA�e�N�X�`�����g�p���邩�ǂ�����ݒ�ł���

3.m_object�̃����o�֐�SetTex�ŁA�g�p����e�N�X�`���̔ԍ��������Ƃ��ēn���A�e�N�X�`���̐ݒ������
  ���e�N�X�`���ԍ���textureMgr.h���Q��
  ���d�v
4.�ݒ��A2-1�̏ꍇ�͈���������UpdateVtx�Ăђ��_�X�V, 2-2�̏ꍇ�͈��������UpdateVtx�Œ��_�z��̐擪�A�h���X��n���X�V����
*/
class C_OBJECT{
protected:
	C_POLYGON_2D *m_object;	//�I�u�W�F�N�g�|���S�����z��
	int m_objectNumMax;	//�I�u�W�F�N�g������(�ő吔)
	unsigned char m_objectType;	//�I�u�W�F�N�g���ʔԍ�

public:
	C_OBJECT();
	virtual ~C_OBJECT();

	virtual void Init() = 0;
	virtual void Update() = 0;

	//�I������(�����o�ϐ��̉���Ȃ�
	void Uninit();
	
	//���M�����
	void Release() { Uninit(); delete this; }
	
	//�`��
	void Draw();

	void CreateObject() { m_object = new C_POLYGON_2D[m_objectNumMax]; }
	//�I�u�W�F�N�g���ʔԍ��擾
	unsigned char GetObjectType() { return this->m_objectType; }
};

#endif