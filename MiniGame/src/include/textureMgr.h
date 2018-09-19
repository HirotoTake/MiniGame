#ifndef _TEXMGR_H_
#define _TEXMGR_H_

#include "main.h"

#define MAX_TEXTURE (3)

//�^�C�g��
#define TEX_PATH_TITLE _T("data/texture/title/title.png")

//�X�e�[�W�I��
#define TEX_PATH_STAGE_ICON _T("data/texture/stageselect/stageselect.png")
#define TEX_PATH_STAGE_1_ICON _T("data/texture/stage/stage1/stage1.png")

#define TEX_PATH_PLAYER _T("data/texture/character/player/player1.png")
#define TEX_PATH_GOAL _T("data/texture/map/goal.png")
#define TEX_PATH_BLOCK _T("data/texture/map/block.png")
#define TEX_PATH_STAGE_BG _T("data/texture/map/stage_bg.png")
#define TEX_PATH_GAMEOVER _T("data/texture/gameover/gameover.png")
#define TEX_PATH_GIDE_SELECT _T("data/texture/gide/gide_select.png")
#define TEX_PATH_STAGE_CLEAR _T("data/texture/stageclear/stageclear.png")
#define TEX_PATH_NUMBER _T("data/texture/font/number.png")
#define TEX_PATH_GIDE_STAGE _T("data/texture/gide/gide.png")


//�e�N�X�`���ԍ�
//���V�K�ɒǉ�����ꍇ��CPP���ɂ���t�@�C���p�X�̓Y�����ԍ��ƑΉ������邱��
typedef enum {
	TEXTURE_NUM_TITLE,
	TEXTURE_NUM_STAGE_ICON,
	TEXTURE_NUM_PLAYER,
	TEXTURE_NUM_GOAL,
	TEXTURE_NUM_BLOCK,
	TEXTURE_NUM_STAGE_BG,
	TEXTURE_NUM_GAMEOVER,
	TEXTURE_NUM_GIDE_SELECT,
	TEXTURE_NUM_STAGE_CLEAR,
	TEXTURE_NUM_NUMBER,
	TEXTURE_NUM_GIDE_STAGE,
	TEXTURE_NUM_MAX,
}TEXTURE_NUM;

//�e�N�X�`���Ǘ��N���X
//�Q�[���S�̂Ɏg�p����e�N�X�`�����Ǘ�
class C_TEX_MANAGER {
private:
	LPDIRECT3DTEXTURE9 *m_pTex;
	int m_texNum;	//���ݎg�p���Ă���e�N�X�`���̖���
public:
	C_TEX_MANAGER() { m_pTex = NULL; }
	//�������J��
	virtual ~C_TEX_MANAGER();

	//���������̃V�[���ԍ��A�X�e�[�W�ԍ��ɑΉ������e�N�X�`�������[�h����
	void Init();
	
	//�V�[���ԍ��X�V���ɑΉ����ԍ��̃e�N�X�`�������[�h
	void Update();

	//�������J��
	void Uninit();

	//���ݓǂݍ��܂�Ă���e�N�X�`�����j��
	//�I�����ɌĂԂ����̊֐��̒����InitTex
	void DestroyTex();

	LPDIRECT3DTEXTURE9 *GetTex(TEXTURE_NUM num);

};


void InitTex();

void UninitTex();

void UpdateTex();

LPDIRECT3DTEXTURE9 GetTex(TEXTURE_NUM num);
#endif