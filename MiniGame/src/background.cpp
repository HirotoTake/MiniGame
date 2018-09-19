//背景処理
//=================================================================
// インクルード部
//=================================================================
#include "include\common.h"
#include "include\background.h"
#include "include\object.h"
#include "include\textureMgr.h"
#include "include\sceneMgr.h"
#include "include\stageManager.h"
//================================================================
//  定数・マクロ定義
//================================================================

#define BG_CENTER_X ((float)(SCREEN_WIDTH / 2.0f));
#define BG_CENTER_Y ((float)(SCREEN_HEIGHT / 2.0f));

C_BACKGROUND *g_background;

const int sceneTexNum[SCENE_NUM_MAX + 1] = {
	TEXTURE_NUM_STAGE_BG,TEXTURE_NUM_STAGE_BG, 0,TEXTURE_NUM_STAGE_BG,TEXTURE_NUM_STAGE_BG};
const int gameMainTexNum[STAGE_NUM_MAX] = { TEXTURE_NUM_STAGE_BG, TEXTURE_NUM_STAGE_BG, TEXTURE_NUM_STAGE_BG, };


void C_BACKGROUND::Init(){
	m_objectType = OBJECT_TYPE_BACKGROUND;
	m_objectNumMax = 1;
	CreateObject();

	m_object->m_polygon2D.isUseTex = false;
	m_object->m_polygon2D.currentAnimPat = 0;
	m_object->m_polygon2D.MaxAnimPat = 1;
	m_object->m_polygon2D.center.x = BG_CENTER_X;
	m_object->m_polygon2D.center.y = BG_CENTER_Y;
	m_object->m_polygon2D.fRad = 0.0f;
	m_object->m_polygon2D.height = SCREEN_HEIGHT;
	m_object->m_polygon2D.width = SCREEN_WIDTH;
	m_object->m_polygon2D.nDivU = 1;
	m_object->m_polygon2D.nDivV = 1;
	m_object->m_polygon2D.scale = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
	m_object->m_polygon2D.pos = D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f);
	m_object->m_polygon2D.A = 255;
	m_object->m_polygon2D.R = 0;
	m_object->m_polygon2D.G = 0;
	m_object->m_polygon2D.B = 255;
	m_object->UpdateVtx();
	
	SCENE scene = GetScene();
	if (scene.sceneNum != SCENE_NUM_GAME) {
		
		m_object->SetTex((TEXTURE_NUM)sceneTexNum[scene.sceneNum]);
		if (scene.sceneNum == SCENE_NUM_STAGECLEAR || scene.sceneNum == SCENE_NUM_GAMEOVER) {
			m_object->m_polygon2D.isUseTex = false;
		}		
	}
	else {
		STAGE stage = GetStage();
		m_object->SetTex((TEXTURE_NUM)gameMainTexNum[stage.stageNum]);
	}
}


//*****************************************************************
// 初期化処理
//*****************************************************************
void InitBG(void)
{
	AddObject(g_background = new C_BACKGROUND);
}