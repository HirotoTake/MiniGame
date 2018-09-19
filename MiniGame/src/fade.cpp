
#include "include\fade.h"

#include <tchar.h>
#include "include\main.h"
#include "include\input.h"
#include "include\polygon.h"

//----- マクロ定義

#define FADE_WIDTH	(SCREEN_WIDTH)
#define FADE_HEIGHT	(SCREEN_HEIGHT)
#define FADE_TIME (60)

//----- グローバル変数-----
static C_FADE g_fade;

static int g_nFade;	//フェードタイム
static int g_nDir;	//１フレーム分のフェードタイム

// 初期化処理
HRESULT InitFade(void)
{
	g_fade.Init();

	return S_OK;
}

// 終了処理
void UninitFade()
{
	g_fade.Uninit();
}

// 更新処理
void UpdateFade()
{
	g_fade.Update();
}

// 描画処理
void DrawFade()
{
	g_fade.Draw();
}

void StartFadeIn()
{
	g_fade.StarFadeIn();
}

void StartFadeOut()
{
	g_fade.StarFadeOut();
}

int EndFadeIn()
{
	return g_fade.EndFadeIn();
}

int EndFadeOut()
{
	return g_fade.EndFadeOut();
}

void C_FADE::Init()
{
	m_nFade = FADE_TIME;
	m_nDir = 0;
	m_isFadeIn = m_isFadeOut = m_isFade =  false;

	m_objectType = OBJECT_TYPE_FADE;
	m_objectNumMax = 1;
	CreateObject();

	//ポリゴン情報セット
	m_object->m_polygon2D.isUseTex = false;
	m_object->m_polygon2D.A = 255;
	m_object->m_polygon2D.R = 0;
	m_object->m_polygon2D.G = 0;
	m_object->m_polygon2D.B = 0;
	m_object->m_polygon2D.fRad = 0.0f;
	m_object->m_polygon2D.pos = D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f);
	m_object->m_polygon2D.height = SCREEN_HEIGHT;
	m_object->m_polygon2D.width = SCREEN_WIDTH;
	m_object->m_polygon2D.center = D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f);
	m_object->m_polygon2D.scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_object->m_polygon2D.nDivU = m_object->m_polygon2D.nDivV = 1;

	m_object->UpdateVtx();
}

void C_FADE::Update()
{
	m_nFade += m_nDir;

	if (m_nFade < 0)
	{
		m_nFade = 0;
		m_isFadeIn = false;
		m_isFade = false;
	}
	else if (m_nFade > FADE_TIME)
	{
		m_nFade = FADE_TIME;
		m_isFadeOut = false;
		m_isFade = false;
	}

	int nAlpha = g_nFade * 256 / FADE_TIME;	//時間経過によるアルファ値の増減
											//アルファ値更新
	m_object->m_polygon2D.A = nAlpha;

	//頂点情報登録
	m_object->UpdateVtx();
}

void C_FADE::StarFadeIn()
{
	m_nFade = FADE_TIME;
	m_nDir = -1;
	m_isFadeIn = true;
	m_isFade = true;
}

void C_FADE::StarFadeOut()
{
	m_nFade = 0;
	m_nDir = 1;
	m_isFadeOut = true;
	m_isFade = true;
}

int C_FADE::EndFadeIn()
{
	return (m_nDir < 0 && m_nFade <= 0);
}

int C_FADE::EndFadeOut()
{
	return (m_nDir > 0 && m_nFade >= FADE_TIME);
}