//���d�C���N���[�h�h�~
#ifndef _MAIN_H_
#define _MAIN_H_
/*------------------------------------------------------------------------------------------------------/

[�t�@�C����	:main.h]
	�����	:AT12B171 �|�R�L�l
	�T�v	:

-------------------------------------------------------------------------------------------------------*/

//*************** �C���N���[�h ***************
#include "common.h"

#ifdef WIN_

//���C�u����
#if 1 // [������"0"�ɂ����ꍇ�A"�\���v���p�e�B" -> "�����J" -> "����" -> "�ǉ��̈ˑ��t�@�C�� "�ɑΏۃ��C�u������ݒ肷��] 
#pragma comment (lib, "d3d9.lib") 
#pragma comment (lib, "d3dx9.lib") 
#pragma comment (lib, "dxguid.lib") 
#pragma comment (lib,"dsound.lib")
#pragma comment (lib, "winmm.lib") 
#endif 

//*************** �萔�E�}�N�� ***************
#define CLASS_NAME  _T("AppClass")			// �E�C���h�E�̃N���X��
#define WINDOW_NAME  _T("MyGame")	// �E�C���h�E�̃L���v�V����

//*************** �v���g�^�C�v ***************
LPDIRECT3DDEVICE9 GetDevice(void);

#endif // WIN_


#endif // !_MAIN_H_
