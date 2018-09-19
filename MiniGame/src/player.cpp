
#include "include\common.h"
#include "include\player.h"
#include "include\textureMgr.h"
#include "include\objectMgr.h"
#include "include\sceneMgr.h"

//----------�萔�@�}�N��----------
#define PLAYER_DIV_U (3)
#define PLAYER_DIV_V (4)

#define PLAYER_WIDTH (60.0f)
#define PLAYER_HEIGHT (60.0f)

#define PLAYER_CENTER_X (PLAYER_WIDTH /2.0f)
#define PLAYER_CENTER_Y (PLAYER_HEIGHT /2.0f)

//�v���C���[�X�e�[�^�X
#define PLAYER_LIFE (200)

#define PLAYER_MOVE_SPEED_X (2.0f)
#define PLAYER_MOVE_SPEED_Y (-15.0f)

#define PLAYER_ACCEL_X (1.5f)

#define GRAVITY (0.6f);

//����
enum {
	UP,//�g��Ȃ�,
	RIGHT,
	UNDER,//�g��Ȃ�
	LEFT,
};

void C_PLAYER::Init(){

	//�A�j���[�V�����ԍ��Z�b�g
	m_objectNumMax = 1;
	m_objectType = OBJECT_TYPE_PLAYER;
	CreateObject();

	m_object->SetTex(TEXTURE_NUM_PLAYER);
	m_object->m_polygon2D.isUseTex = true;
	m_object->m_polygon2D.currentAnimPat = 0;
	m_object->m_polygon2D.MaxAnimPat = PLAYER_DIV_U * PLAYER_DIV_V;
	m_object->m_polygon2D.center = D3DXVECTOR3(PLAYER_CENTER_X, PLAYER_CENTER_Y, 0.0f);
	m_object->m_polygon2D.scale = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
	m_object->m_polygon2D.pos = D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f);
	m_object->m_polygon2D.A = 255;
	m_object->m_polygon2D.R = 255;
	m_object->m_polygon2D.G = 255;
	m_object->m_polygon2D.B = 255;	
	m_object->m_polygon2D.height = PLAYER_HEIGHT;
	m_object->m_polygon2D.width = PLAYER_WIDTH;
	m_object->m_polygon2D.nDivU = PLAYER_DIV_U;
	m_object->m_polygon2D.nDivV = PLAYER_DIV_V;
	m_object->m_polygon2D.fRad = D3DXToRadian(0.0f);

	m_object->UpdateVtx();

	//�ړ��ʏ�����
	this->m_move.x = 0.0f;
	this->m_move.y = 0.0f;

	this->m_accel.x = 1.0f;
	this->m_accel.y = 1.0f;

	//�v���C���[�X�e�[�^�X������
	this->m_status.nDir  = m_status.nDirOld = RIGHT;
	this->m_status.nLife = PLAYER_LIFE;
	this->m_status.bJump = true;
	this->m_status.bUnder = false;
	this->m_status.charaId = CHARACTER_ID_PLAYER;
	this->m_status.worldPos = D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f);

	//�v���C���[�X�e�[�^�X�Z�b�g
	this->SetStatus(&m_status);

	
}


void C_PLAYER::Update()
{
	if (!m_object->m_enableUpdate) return;
	bool bKey = false; //�ړ��L�[�������ꂽ������
	//�ߋ����W�p
	float fPosOldX = m_object->m_polygon2D.pos.x;
	float fPosOldY = m_object->m_polygon2D.pos.y;

	//�S�[������
	if (DIGetKeyTrigger(DIK_W)) {
		ST_POLYGON_2D obj = GetObjectPolygonInfo(OBJECT_TYPE_GOAL);
		if (m_object->m_polygon2D.pos.x > obj.pos.x - obj.center.x && m_object->m_polygon2D.pos.x < obj.pos.x + obj.center.x && m_object->m_polygon2D.pos.y > obj.pos.y - obj.center.y && m_object->m_polygon2D.pos.y < obj.pos.y + obj.center.y) {
			enableStageClear();
			SetStageClear(true);
#ifdef USE_WIN_SOUND

			PlaySound(SOUND_LABEL_SE_KAIDAN);
#endif // USE_WIN_SOUND

			m_object->m_enableUpdate = false;
		}
	}

	//���i�~��
	if (DIGetKeyTrigger(DIK_S)) {
		m_status.bUnder = true;
	}
	else m_status.bUnder = false;

	//�ړ��ʌv�Z
	if (DIGetKey(DIK_D) && !DIGetKey(DIK_A)) {//�E
		m_status.nDir = RIGHT;
		m_move.x = PLAYER_MOVE_SPEED_X;
		bKey = true;
		if (m_status.nDir != m_status.nDirOld) {
			m_object->m_polygon2D.nAnimCnt = 0;
			m_object->m_polygon2D.currentAnimPat = PLAYER_DIV_U * m_status.nDir;
		}
		m_object->m_polygon2D.nAnimCnt++;
	}
	else if (!DIGetKey(DIK_D) && DIGetKey(DIK_A)) {//��
		m_move.x = PLAYER_MOVE_SPEED_X * -1;
		bKey = true;
		m_status.nDir = LEFT;
		if (m_status.nDir != m_status.nDirOld) {
			m_object->m_polygon2D.nAnimCnt = 0;
			m_object->m_polygon2D.currentAnimPat = PLAYER_DIV_U * m_status.nDir;
		}
		m_object->m_polygon2D.nAnimCnt++;
	}
	else m_move.x = 0.0f;

	

	if (!m_status.bJump && DIGetKeyTrigger(DIK_SPACE)) {
		m_move.y = PLAYER_MOVE_SPEED_Y;
		m_status.bJump = true;
		bKey = true;
#ifdef USE_WIN_SOUND
		PlaySound(SOUND_LABEL_SE_JUMP);
#endif // USE_WIN_SOUND
	}
	//�����x
	if (DIGetKey(DIK_LSHIFT)) {
		m_accel.x += 0.01f;
		if (m_accel.x > PLAYER_ACCEL_X)
			m_accel.x = PLAYER_ACCEL_X;
	}
	else {
		m_accel.x -= 0.2f;
		if (m_accel.x < 1.0f)
			m_accel.x = 1.0f;
	}

	//�ړ��ʍX�V
	if(m_status.bJump) m_move.y += GRAVITY;
	m_move.x *= m_accel.x;

	//���_���W�X�V
	m_object->m_polygon2D.pos.x += m_move.x;
	m_object->m_polygon2D.pos.y += m_move.y;

	//�����蔻��
	//�u���b�N����
	//ST_POLYGON_2D *block = GetBlock();
	//STAGE stage = GetStage();
	//int blockNum;
	//switch (stage.stageNum)
	//{
	//case STAGE_NUM_STAGE_1:
	//	blockNum = BLOCK_NUM_1;
	//	break;
	//case STAGE_NUM_STAGE_2:
	//	blockNum = BLOCK_NUM_1 * BLOCK_LINE_NUM;
	//	break;
	//case STAGE_NUM_STAGE_3:
	//	blockNum = BLOCK_NUM_1 * BLOCK_LINE_NUM + BLOCK_NUM_2;
	//	break;
	//}
	//for (int i = 0; i < blockNum; i++) {
	//	
	//	//���菈��
	//	if ((block + i)->pos.x - (block + i)->center.x < m_polygon2D.pos.x + m_polygon2D.center.x && (block + i)->pos.x + (block + i)->center.x > m_polygon2D.pos.x - m_polygon2D.center.x) {
	//		//�ォ��̏�蔻��
	//		if (!m_status.bUnder && fPosOldY + m_polygon2D.center.y < (block + i)->pos.y - (block + i)->center.y && m_polygon2D.pos.y + m_polygon2D.center.y >= (block + i)->pos.y - (block + i)->center.y ||
	//			m_status.bUnder && !(block + i)->bEnableUpToDown && fPosOldY + m_polygon2D.center.y < (block + i)->pos.y - (block + i)->center.y && m_polygon2D.pos.y + m_polygon2D.center.y >= (block + i)->pos.y - (block + i)->center.y) {
	//			
	//			m_polygon2D.pos.y = (block + i)->pos.y - ((block + i)->center.y + m_polygon2D.center.y) - 1.0f;
	//			m_status.bJump = false;
	//		}
	//	}
	//	//������
	//	if ((block + i)->pos.y - (block + i)->center.y < m_polygon2D.pos.y - m_polygon2D.center.y && (block + i)->pos.y + (block + i)->center.y > m_polygon2D.pos.y - m_polygon2D.center.y || (block + i)->pos.y - (block + i)->center.y > m_polygon2D.pos.y - m_polygon2D.center.y && (block + i)->pos.y - (block + i)->center.y < m_polygon2D.pos.y + m_polygon2D.center.y ) {
	//		if (fPosOldX + m_polygon2D.center.x < (block + i)->pos.x - (block + i)->center.x && m_polygon2D.pos.x + m_polygon2D.center.x >= (block + i)->pos.x - (block + i)->center.x) {
	//			m_polygon2D.pos.x = (block + i)->pos.x - (block + i)->center.x - m_polygon2D.center.x - 1.0f;
	//		}//�E����
	//		else  if (fPosOldX - m_polygon2D.center.x > (block + i)->pos.x + (block + i)->center.x && m_polygon2D.pos.x - m_polygon2D.center.x <= (block + i)->pos.x + (block + i)->center.x) {
	//			m_polygon2D.pos.x = (block + i)->pos.x + (block + i)->center.x + m_polygon2D.center.x + 1.0f;
	//		}
	//		
	//	}
	//}

	
	

	//��ʊO����
	if (m_object->m_polygon2D.pos.y + m_object->m_polygon2D.center.y > SCREEN_LIMIT_UNDER) { //��
		m_object->m_polygon2D.pos.y = SCREEN_LIMIT_UNDER - 1.0f;
		m_status.bJump = false;
		m_move.y = 0.0f;
	}
	else if(m_object->m_polygon2D.pos.y - m_object->m_polygon2D.center.y < 0.0f) {
		m_object->m_polygon2D.pos.y = 0.0f + m_object->m_polygon2D.center.y;
		m_move.y = 0.0f;
	}
	//��
	if (m_object->m_polygon2D.pos.x - m_object->m_polygon2D.center.x <= SCREEN_LIMIT_LEFT) {
		m_object->m_polygon2D.pos.x = SCREEN_LIMIT_LEFT + m_object->m_polygon2D.center.x;
	}//�E
	else if (m_object->m_polygon2D.pos.x + m_object->m_polygon2D.center.x >= SCREEN_LIMIT_RIGHT) {
		m_object->m_polygon2D.pos.x = SCREEN_LIMIT_RIGHT - m_object->m_polygon2D.center.x;
	}
	

	if (!bKey) {
		m_object->m_polygon2D.currentAnimPat = 7;
		m_object->m_polygon2D.nAnimCnt = 0;
	}
	else {
		if (m_object->m_polygon2D.nAnimCnt >= 20) {
			m_object->m_polygon2D.nAnimCnt = 0;
			m_object->m_polygon2D.currentAnimPat++;
			if (m_object->m_polygon2D.currentAnimPat > PLAYER_DIV_U * m_status.nDir + (PLAYER_DIV_U - 1))
				m_object->m_polygon2D.currentAnimPat = PLAYER_DIV_U * m_status.nDir;
		}
		
	}
	m_status.nDirOld = m_status.nDir;
	//�v���C���[���X�V
	this->SetStatus(&m_status);
	m_object->UpdateVtx();

	
	//�X�V�㏈��
	//�ړ��ʏ�����
	
}