#ifndef _SOUND_H_
#define _SOUND_H_
//#define USE_WIN_SOUND


#ifdef USE_WIN_SOUND

#include "main.h"

#include <xaudio2.h>

//*****************************************************************************
// �T�E���h�t�@�C��
//*****************************************************************************
typedef enum
{
	SOUND_LABEL_TITLE = 0,		// BGM0
	SOUND_LABEL_STAGE_SELECT,		// BGM0
	SOUND_LABEL_STAGE,			// BGM1
	SOUND_LABEL_GAMEOVER,		// BGM2
	SOUND_LABEL_STAGE_CLEAR,
	SOUND_LABEL_SE_DECIDE,		// ���艹
	SOUND_LABEL_SE_SELECT,		// �I����
	SOUND_LABEL_SE_JUMP,		// �W�����v��
	SOUND_LABEL_SE_KAIDAN,		//��k
	SOUND_LABEL_MAX,			// �o�^���̎����ݒ�
} SOUND_LABEL;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);

HRESULT PlaySound(SOUND_LABEL label);

void StopSound(SOUND_LABEL label);
void StopSound(void);



#endif // USE_WIN_SOUND

#endif
