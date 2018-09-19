
//********** インクルード **********
#include "include\UI_STAGE_SELECT.h"
#include "include\sceneMgr.h"
#include "include\stageManager.h"
#include "include\objectMgr.h"
#include "include\fade.h"


//********** 定数・マクロ **********
//描画対象の各種定数
#define TEXTURE_DIV_U (3)	//テクスチャ分割数
#define TEXTURE_DIV_V (1)

//アイコン数
#define MAX_ICON (5)

//ステージアイコンの大きさや定位置
#define ICON_WIDTH (400)
#define ICON_HEIGHT (260)
#define ICON_CENTER_X (ICON_WIDTH / 2)
#define ICON_CENTER_Y (ICON_HEIGHT / 2)

#define SCROLL_TIME (60)	//scroll時間
#define SCALE_MAX (1.0f)
#define SCALE_MIN (0.7f)
#define STEP_SCALE ((SCALE_MAX - SCALE_MIN) / (float)SCROLL_TIME)

#define SCROLL_X ((float)(ICON_WIDTH / SCROLL_TIME))

#define GIDE_SELECT_WIDTH (400.0f)
#define GIDE_SELECT_HEIGHT (100.0f)


//**********グローバル宣言**********

static int nStage = STARTSTAGE;	//ステージ番号
static int g_scrollCnt;	//スクロールカウント MAX 60 (SCROLL_TIME)
static int g_scrollDir;	//スクロール方向
static bool g_bScroll;	//スクロールフラグ(現在
static bool g_bScrollOld;	//スクロールフラグ(直前

void C_UI_STAGE_SELECT_ICON::Init(){
	SetStage((STAGE_NUM)nStage);
	m_stageIcon = new C_STAGE_UI[5];

	g_scrollCnt = SCROLL_TIME;
	g_bScroll = false;
	g_bScrollOld = false;
	g_scrollDir = -1;
	
	for (int i = 0; i < MAX_ICON; i++) {
		//更新用頂点情報初期化
		(m_stageIcon + i)->m_polygon2D.isUseTex = true;
		(m_stageIcon + i)->m_polygon2D.pos.x = (float)(SCREEN_CENTER_X - (ICON_WIDTH * 2) + (ICON_WIDTH * i));
		(m_stageIcon + i)->m_polygon2D.pos.y = (float)(SCREEN_CENTER_Y);
		(m_stageIcon + i)->m_polygon2D.nDivU = TEXTURE_DIV_U;
		(m_stageIcon + i)->m_polygon2D.nDivV = TEXTURE_DIV_V;
		(m_stageIcon + i)->m_polygon2D.width = ICON_WIDTH;
		(m_stageIcon + i)->m_polygon2D.height = ICON_HEIGHT;
		(m_stageIcon + i)->m_polygon2D.center = D3DXVECTOR3(ICON_CENTER_X, ICON_CENTER_Y, 0.0f);
		if (i == 2) (m_stageIcon + i)->m_polygon2D.scale = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
		else        (m_stageIcon + i)->m_polygon2D.scale = D3DXVECTOR3(SCALE_MIN, SCALE_MIN, 0.0f);
		(m_stageIcon + i)->m_polygon2D.A = 255;
		(m_stageIcon + i)->m_polygon2D.R = 255;
		(m_stageIcon + i)->m_polygon2D.G = 255;
		(m_stageIcon + i)->m_polygon2D.B = 255;
		(m_stageIcon + i)->m_polygon2D.AnimPat = -2 + i + nStage;
		(m_stageIcon + i)->m_polygon2D.bDisp = true;
		(m_stageIcon + i)->m_polygon2D.fRad = D3DXToRadian(0.0f);
		(m_stageIcon + i)->m_polygon2D.fRollCnt = 0.0f;
		(m_stageIcon + i)->m_polygon2D.nRollDir = 1;
		(m_stageIcon + i)->m_polygon2D.fScaleCnt = 0.0f;
		(m_stageIcon + i)->m_polygon2D.nDispCnt = 0;
		(m_stageIcon + i)->m_polygon2D.nDispDir = 1;
		(m_stageIcon + i)->m_polygon2D.nScaleDir = 1;
		(m_stageIcon + i)->m_polygon2D.MaxAnimPat = STAGE_NUM_MAX;

		(m_stageIcon + i)->m_objectType = OBJECT_TYPE_UI_STAGE_SELECT;
		(m_stageIcon + i)->m_texNo = TEXTURE_NUM_STAGE_ICON;
		(m_stageIcon + i)->m_pTex = GetTex((m_stageIcon + i)->m_texNo);
	}

}

void C_UI_STAGE_SELECT_ICON::Uninit()
{
	SetStage((STAGE_NUM)nStage);
	delete[] m_stageIcon;
	m_stageIcon = NULL;
	//nStage = 0;
}

void C_UI_STAGE_SELECT_ICON::Update()
{
	
		//左右でステージ選択
		//フェードアウト中は選択不可
		if (EndFadeIn() && !g_bScroll)
		{
			if (DIGetKeyTrigger(DIK_LEFT))
			{
				nStage--;
				if (nStage < 0)
					nStage = 0;
				else
				{
					g_bScroll = true;
					g_scrollDir = -1;
				}
			}
			if (DIGetKeyTrigger(DIK_RIGHT))
			{
				nStage++;
				if (nStage >= STAGE_NUM_MAX)
					nStage = STAGE_NUM_MAX - 1;
				else
				{
					g_bScroll = true;
					g_scrollDir = 1;
				}
			}
			if (EndFadeIn())
			{//スペースで次画面へ移行
				if (DIGetKeyTrigger(DIK_SPACE)) {
					StartFadeOut();
#ifdef USE_WIN_SOUND
					PlaySound(SOUND_LABEL_SE_DECIDE);
#endif // USE_WIN_SOUND
				}
			}
			
		}

		//scrollカウント
		if (g_bScroll)		g_scrollCnt--;
		if (g_scrollCnt < 0)
		{
			g_bScroll = false;
			g_scrollCnt = SCROLL_TIME;
		}

		//座標更新
		for (int i = 0; i < MAX_ICON; i++)
		{	//中央アイコン(選択中アイコン
			if (i == 2) {
				(m_stageIcon + i)->m_polygon2D.scale += D3DXVECTOR3(0.01f, 0.01f, 0.0f) * (float)(m_stageIcon + i)->m_polygon2D.nScaleDir;
				if ((m_stageIcon + i)->m_polygon2D.scale.x > 1.2f || (m_stageIcon + i)->m_polygon2D.scale.x < 0.8f) (m_stageIcon + i)->m_polygon2D.nScaleDir *= -1;
			}
			else {//両最後のアイコン(非選択アイコン
				(m_stageIcon + i)->m_polygon2D.fRollCnt += 0.1f * (m_stageIcon + i)->m_polygon2D.nRollDir;
				(m_stageIcon + i)->m_polygon2D.fRad = D3DXToRadian((m_stageIcon + i)->m_polygon2D.fRollCnt);
				if ((m_stageIcon + i)->m_polygon2D.fRad > D3DXToRadian(10.0f) || (m_stageIcon + i)->m_polygon2D.fRad < D3DXToRadian(-10.0f)) (m_stageIcon + i)->m_polygon2D.nRollDir *= -1;
			}

			//スクロール移動
			if (g_bScroll || g_bScrollOld)
			{
				(m_stageIcon + i)->m_polygon2D.pos.x += SCROLL_X * g_scrollDir * -1;
				if (i == 1 && g_scrollDir == 1) {
					(m_stageIcon + i)->m_polygon2D.scale += D3DXVECTOR3(STEP_SCALE, STEP_SCALE, 0.0f);
				}
				if (i == 3 && g_scrollDir == -1) {
					(m_stageIcon + i)->m_polygon2D.scale += D3DXVECTOR3(STEP_SCALE, STEP_SCALE, 0.0f);
				}
				if (i == 2) {
					(m_stageIcon + i)->m_polygon2D.scale -= D3DXVECTOR3(STEP_SCALE, STEP_SCALE, 0.0f);
				}

			}

			//アイコンスクロール終了時
			if (!g_bScroll && g_bScrollOld)
			{
				
				(m_stageIcon + i)->m_polygon2D.AnimPat += g_scrollDir;
				if ((m_stageIcon + i)->m_polygon2D.AnimPat >= STAGE_NUM_MAX) {
					(m_stageIcon + i)->m_polygon2D.A = 0;
				}
				else {
					(m_stageIcon + i)->m_polygon2D.A = 255;
				}
				(m_stageIcon + i)->m_polygon2D.pos.x = (float)(SCREEN_CENTER_X - (ICON_WIDTH * 2) + (ICON_WIDTH * i));

				if (i == 2) (m_stageIcon + i)->m_polygon2D.scale = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
				else (m_stageIcon + i)->m_polygon2D.scale = D3DXVECTOR3(SCALE_MIN, SCALE_MIN, 0.0f);
				(m_stageIcon + i)->m_polygon2D.fRad = D3DXToRadian(0.0f);
				(m_stageIcon + i)->m_polygon2D.nRollDir = 1;
				(m_stageIcon + i)->m_polygon2D.fRollCnt = 1.0f;
				(m_stageIcon + i)->m_polygon2D.fScaleCnt = 0.0f;
				(m_stageIcon + i)->m_polygon2D.nScaleDir = 1;
			}

			//頂点情報セット
			(m_stageIcon + i)->SetVtx(&(m_stageIcon + i)->m_polygon2D);
		}
		//フラグ更新
		g_bScrollOld = g_bScroll;
}


void C_OBJECT_MANAGER_UI_STAGE_SELECT::Init(){
	m_UI_stageIcon = new C_UI_STAGE_SELECT_ICON;

	m_UI_stageIcon->Init();

	m_gide_select = new C_STAGE_SELECT_UI_GIDE_SELECT;

	m_gide_select->Init();
}

void C_OBJECT_MANAGER_UI_STAGE_SELECT::Uninit()
{
	m_UI_stageIcon->Uninit();
	delete m_UI_stageIcon;
	m_UI_stageIcon = NULL;

	m_gide_select->Uninit();
	delete m_gide_select;
	m_gide_select = NULL;

}

void C_OBJECT_MANAGER_UI_STAGE_SELECT::Update()
{
	m_UI_stageIcon->Update();
	m_gide_select->Update();
}


void C_OBJECT_MANAGER_UI_STAGE_SELECT::Draw()
{
	m_UI_stageIcon->Draw();
	m_gide_select->Draw();
}


void C_STAGE_SELECT_UI_GIDE_SELECT::Init()
{
	m_enableUpdate = true;
	m_objectType = OBJECT_TYPE_UI_STAGE_SELECT;
	m_texNo = TEXTURE_NUM_GIDE_SELECT;
	m_pTex = GetTex(m_texNo);

	m_polygon2D.isUseTex = true;
	m_polygon2D.A = 255;
	m_polygon2D.R = 255;
	m_polygon2D.G = 255;
	m_polygon2D.B = 255;
	m_polygon2D.AnimPat = 0;
	m_polygon2D.MaxAnimPat = 2;
	m_polygon2D.nAnimCnt = 0;
	m_polygon2D.nDivU = 1;
	m_polygon2D.nDivV = 2;
	m_polygon2D.fRad = D3DXToRadian(0.0f);
	m_polygon2D.pos = D3DXVECTOR3((float)SCREEN_WIDTH / 2.0f, 400.0f, 0.0f);
	m_polygon2D.width = GIDE_SELECT_WIDTH;
	m_polygon2D.height = GIDE_SELECT_HEIGHT;
	m_polygon2D.center = D3DXVECTOR3(GIDE_SELECT_WIDTH / 2.0f, GIDE_SELECT_HEIGHT / 2.0f, 0.0f);
	m_polygon2D.scale = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
	m_polygon2D.nAnimCnt = 0;

	SetVtx(&m_polygon2D);

}

void C_STAGE_SELECT_UI_GIDE_SELECT::Update()
{
	m_polygon2D.nAnimCnt++;
	if (m_polygon2D.nAnimCnt >= 30) {
		m_polygon2D.nAnimCnt = 0;
		m_polygon2D.AnimPat ^= 1;
	}
	SetVtx(&m_polygon2D);
}