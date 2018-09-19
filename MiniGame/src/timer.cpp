
//********** インクルード **********
#include "include\timer.h"
#include "include\textureMgr.h"
#include "include\fade.h"
#include "include\sceneMgr.h"


//********** 定数・マクロ **********
#define MAX_TIME (180)

#define TIME_WIDTH (30.0f)
#define TIME_HEIGHT (30.0f)

//**********グローバル宣言**********


void C_TIMER_MANAGER::Init()
{
	m_timer = new C_TIMER[3];
	m_time = MAX_TIME;
	int work = m_time;
	m_frameCnt = 0;	
	end = false;

	for (int i = 0; i < 3; i++) {
		(m_timer + i)->m_enableUpdate = true;
		(m_timer + i)->m_texNo = TEXTURE_NUM_NUMBER;
		(m_timer + i)->m_pTex = GetTex((m_timer + i)->m_texNo);

		(m_timer + i)->m_polygon2D.isUseTex = true;
		
		(m_timer + i)->m_polygon2D.MaxAnimPat = 10;
		(m_timer + i)->m_polygon2D.nDivU = 1;
		(m_timer + i)->m_polygon2D.nDivV = 10;

		(m_timer + i)->m_polygon2D.pos.x = 760.0f + (TIME_WIDTH * 2) - (i * TIME_WIDTH);
		(m_timer + i)->m_polygon2D.pos.y = 50.0f;
		(m_timer + i)->m_polygon2D.width = TIME_WIDTH;
		(m_timer + i)->m_polygon2D.height = TIME_HEIGHT;
		(m_timer + i)->m_polygon2D.center.x = TIME_WIDTH / 2.0f;
		(m_timer + i)->m_polygon2D.center.y = TIME_HEIGHT / 2.0f;
		(m_timer + i)->m_polygon2D.scale.x = 1.0f;
		(m_timer + i)->m_polygon2D.scale.y = 1.0f;
		(m_timer + i)->m_polygon2D.fRad = 0.0f;
		(m_timer + i)->m_polygon2D.A = 255;
		(m_timer + i)->m_polygon2D.R = 255;
		(m_timer + i)->m_polygon2D.G = 255;
		(m_timer + i)->m_polygon2D.B = 255;

		(m_timer + i)->m_polygon2D.AnimPat = work % 10;

		work /= 10;

		(m_timer + i)->SetVtx(&(m_timer + i)->m_polygon2D);
	}
}

void C_TIMER_MANAGER::Uninit()
{
	delete[] m_timer;

	m_timer = NULL;
}

void C_TIMER_MANAGER::Update()
{
	if (end) return;
	m_frameCnt++;
	if (m_frameCnt >= 60) {
		m_frameCnt = 0;
		m_time--;

		int work = m_time;

		for (int i = 0; i < 3; i++) {
			(m_timer + i)->m_polygon2D.AnimPat = work % 10;
			work /= 10;
			(m_timer + i)->SetVtx(&(m_timer + i)->m_polygon2D);
		}
	}
	if (m_time <= 0) {
		StartFadeOut();
		SetStageClear(false);
		end = true;
	}
}

void C_TIMER_MANAGER::Draw()
{
	for (int i = 0; i < 3; i++) {
		(m_timer + i)->Draw();
	}
}