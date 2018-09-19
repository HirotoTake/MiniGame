
//********** インクルード **********
#include "include\common.h"
#include "include\_C_GOAL_OBJ_H_.h"
#include "include\stageManager.h"
#include "include\sceneMgr.h"
#include "include\C_BLOCK.h"

//********** 定数・マクロ **********
#define WIDTH (60.0f)
#define HEIGHT (70.0f)
#define STAGE_1 D3DXVECTOR3(700.0f,SCREEN_LIMIT_UNDER - (HEIGHT / 2.0f + BLOCK_SIZE / 2.0f), 0.0f)
#define STAGE_2 D3DXVECTOR3(700.0f,SCREEN_LIMIT_UNDER - (HEIGHT / 2.0f + BLOCK_SIZE / 2.0f) - (BLOCK_SIZE * 14.0f), 0.0f)

void C_GOAL_OBJ::Init()
{
	m_enableUpdate = true;

	m_objectType = OBJECT_TYPE_GOAL;

	m_polygon2D.isUseTex = true;
	m_texNo = TEXTURE_NUM_GOAL;
	m_pTex = GetTex(m_texNo);

	m_polygon2D.A = 255;
	m_polygon2D.R = 255;
	m_polygon2D.G = 255;
	m_polygon2D.B = 255;
	m_polygon2D.AnimPat = 0;
	m_polygon2D.MaxAnimPat = 1;
	m_polygon2D.nDivU = 1;
	m_polygon2D.nDivV = 1;
	m_polygon2D.center = D3DXVECTOR3(WIDTH / 2.0f, HEIGHT / 2.0f, 0.0f);
	m_polygon2D.scale = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
	m_polygon2D.width = WIDTH;
	m_polygon2D.height = HEIGHT;
	m_polygon2D.fRad = D3DXToRadian(0.0f);
	STAGE stage = GetStage();

	switch (stage.stageNum)
	{
	case STAGE_NUM_STAGE_1:
		m_polygon2D.pos = STAGE_1;
		break;
	case STAGE_NUM_STAGE_2:
		m_polygon2D.pos = STAGE_2;
		break;
	case STAGE_NUM_STAGE_3:
		m_polygon2D.pos = STAGE_1;
		break;
	}

	SetVtx(&m_polygon2D);
	
}