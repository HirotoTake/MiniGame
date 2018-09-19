// �|���S������
#ifndef _FADE_H_
#define _FADE_H_

//#define FADE

#include <Windows.h>
#include "object.h"

class C_FADE:public C_OBJECT {
private:
	int m_nFade;	//�t�F�[�h�^�C��
	int m_nDir;	//�P�t���[�����̃t�F�[�h�^�C��
	bool m_isFadeIn; //�t�F�[�h�C�����t���O
	bool m_isFadeOut; //�t�F�[�h�A�E�g���t���O
	bool m_isFade; //�t�F�[�h���t���O
public:
	void Init() override;
	void Update() override;

	void StarFadeIn();
	void StarFadeOut();

	int EndFadeIn();
	int EndFadeOut();

};

// �v���g�^�C�v�錾
HRESULT InitFade();
void UpdateFade();
void UninitFade();
void DrawFade();
void StartFadeIn();
void StartFadeOut();
int  EndFadeIn();
int  EndFadeOut();
#endif
