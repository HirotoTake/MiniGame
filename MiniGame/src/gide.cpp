#include "include\gide.h"
#include "include\textureMgr.h"

#define JUMP_WIDTH (200.0f)
#define JUMP_HEIGHT (100.0f)

void C_GIDE_OBJ_JUMP::Init()
{
	m_enableUpdate = true;

	m_texNo = TEXTURE_NUM_GIDE_STAGE;
	m_pTex = GetTex(TEXTURE_NUM_GIDE_STAGE);

	m_polygon2D.A = 255;
	m_polygon2D.R = 255;
	m_polygon2D.G = 255;
	m_polygon2D.B = 255;
	m_polygon2D.isUseTex = true;
	m_polygon2D.AnimPat = 0;
	m_polygon2D.MaxAnimPat = 1;
	m_polygon2D.nDivU = 1;
	m_polygon2D.nDivV = 1;
	m_polygon2D.fRad = 0.0f;
	m_polygon2D.pos.x = 110.0f;
	m_polygon2D.pos.y = 50.0f;
	m_polygon2D.center.x = JUMP_WIDTH / 2.0f;
	m_polygon2D.center.y = JUMP_HEIGHT / 2.0f;
	m_polygon2D.scale.x = 1.0f;
	m_polygon2D.scale.y = 1.0f;
	m_polygon2D.width = JUMP_WIDTH;
	m_polygon2D.height = JUMP_HEIGHT;
	m_polygon2D.nAnimCnt = 0;
	SetVtx(&m_polygon2D);
}


