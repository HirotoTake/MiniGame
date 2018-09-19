//���d�C���N���[�h�h�~
#ifndef _COMMON_H_
#define _COMMON_H_

#define WIN_ //Windows�p

#ifdef WIN_

//*************** �C���N���[�h ***************
#include <windows.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <tchar.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "input.h"
#include "sound.h"
#endif // WIN_



//*************** �萔�E�}�N�� ***************
//�X�N���[���p
#ifdef WIN_
#define SCREEN_WIDTH (854)						// �E�C���h�E�̕� 
#define SCREEN_HEIGHT (480)						// �E�C���h�E�̍���
#endif // WIN_


#define SCREEN_CENTER_X (SCREEN_WIDTH / 2)		// �E�C���h�E�̒��S�w���W 
#define SCREEN_CENTER_Y (SCREEN_HEIGHT / 2)		// �E�C���h�E�̒��S�x���W 

#define SCREEN_LIMIT_UNDER (SCREEN_HEIGHT  - 10.0f)
#define SCREEN_LIMIT_LEFT	(20.0f)
#define SCREEN_LIMIT_RIGHT (SCREEN_WIDTH - SCREEN_LIMIT_LEFT)

#define ARRAY_LENGTH(ary) (sizeof(ary) / sizeof(ary[0]))	//�v�f����Ԃ�

//*************** �\���� ***************

//*************** �񋓌^ ***************



//*************** �v���g�^�C�v ***************

#endif // !_COMMON_H_
