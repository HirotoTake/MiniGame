
//********** インクルード **********
#include "include\common.h"
#include "include\logo.h"
#include "include\textureMgr.h"

//********** 定数・マクロ **********
#define TEX_DIV_U (1)	//テクスチャ画像の分割数
#define TEX_DIV_V (2)	//
#define TITLE_VTX (4)		//頂点数

//描画対象の各種定数
//タイトル

#define TITLE_WIDTH (700.0f)	//タイトル幅
#define TITLE_HEIGHT (150.0f)//タイトル高さ
#define TITLE_CENTER_X (TITLE_WIDTH/2.0f)	//タイトル中央X
#define TITLE_CENTER_Y (TITLE_HEIGHT/2.0f)	//タイトル中央Y
#define TITLE_SCALE_MIN	(0.7f)	//タイトル最小倍率	
#define TITLE_SCALE_MAX	(1.0f)	//タイトル最大倍率
#define TITLE_STEP_SCALE (1.0f) //倍率増分

//pushbutton
#define PUSHBUTTON_WIDTH (500.0f)	//タイトル幅
#define PUSHBUTTON_HEIGHT (50.0f)//タイトル高さ
#define PUSHBUTTON_CENTER_X (PUSHBUTTON_WIDTH/2.0f)	//タイトル中央X
#define PUSHBUTTON_CENTER_Y (PUSHBUTTON_HEIGHT/2.0f)	//タイトル中央Y
#define PUSHBUTTON_SCALE_MIN	(0.9f)	//タイトル最小倍率	
#define PUSHBUTTON_SCALE_MAX	(1.1f)	//タイトル最大倍率
#define PUSHBUTTON_STEP_SCALE (0.01f) //倍率増分
#define PUSHBUTTON_DISP_CNT (30) //描画カウント

#define STAGE_CLEAR_WIDTH (700.0f)

/*-----------------------------
	タイトル用アニメーション番号 TEX_NAME_******
-----------------------------*/
enum {
	TEX_NAME_TITLE = 0,
	TEX_NAME_PUSHBUTTON,
	TEX_NAME_MAX,
};


//**********グローバル宣言**********

void C_LOGO_TITLE::Init(){
	this->m_texNo = TEXTURE_NUM_TITLE;
	this->m_pTex = GetTex(this->m_texNo);
	this->m_objectType = OBJECT_TYPE_LOGO_TITLE;

	this->m_polygon2D.isUseTex = true;
	this->m_polygon2D.AnimPat = 0;
	this->m_polygon2D.MaxAnimPat = 2;
	this->m_polygon2D.fRad = 0.0f;
	this->m_polygon2D.bDisp = true;
	this->m_polygon2D.fScaleCnt = 0;
	this->m_polygon2D.scale = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
	this->m_polygon2D.pos = D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f);
	this->m_polygon2D.A = 255;
	this->m_polygon2D.R = 255;
	this->m_polygon2D.G = 255;
	this->m_polygon2D.B = 255;
	this->m_polygon2D.nDispDir = 1;
	this->m_polygon2D.nDispCnt = 0;
	this->m_polygon2D.nScaleDir = 1;
	this->m_polygon2D.nDivU = TEX_DIV_U;
	this->m_polygon2D.nDivV = TEX_DIV_V;
	this->m_polygon2D.center = D3DXVECTOR3(TITLE_CENTER_X, TITLE_CENTER_Y, 0.0f);
	this->m_polygon2D.width = TITLE_WIDTH;
	this->m_polygon2D.height = TITLE_HEIGHT;

	this->SetVtx(&this->m_polygon2D);
}

void C_LOGO_TITLE::Update(){
	this->m_polygon2D.fScaleCnt += TITLE_STEP_SCALE * this->m_polygon2D.nScaleDir;
	this->m_polygon2D.scale = D3DXVECTOR3((float)cos(D3DXToRadian(this->m_polygon2D.fScaleCnt)), (float)cos(D3DXToRadian(this->m_polygon2D.fScaleCnt)), 0.0f);
	if (this->m_polygon2D.scale.x < TITLE_SCALE_MIN || this->m_polygon2D.scale.x > TITLE_SCALE_MAX) {
		this->m_polygon2D.nScaleDir *= -1;
	}
	SetVtx(&m_polygon2D);
}

void C_LOGO_TITLE_PUSHSPACE::Init(){
	this->m_texNo = TEXTURE_NUM_TITLE;
	this->m_pTex = GetTex(this->m_texNo);
	this->m_objectType = OBJECT_TYPE_LOGO_TITLE;

	this->m_polygon2D.isUseTex = true;
	this->m_polygon2D.AnimPat = 1;
	this->m_polygon2D.MaxAnimPat = 2;
	this->m_polygon2D.fRad = 0.0f;
	this->m_polygon2D.bDisp = true;
	this->m_polygon2D.fScaleCnt = 0;
	this->m_polygon2D.scale = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
	this->m_polygon2D.pos = D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y + 200.0f, 0.0f);
	this->m_polygon2D.A = 255;
	this->m_polygon2D.R = 255;
	this->m_polygon2D.G = 255;
	this->m_polygon2D.B = 255;
	this->m_polygon2D.nDispDir = 1;
	this->m_polygon2D.nDispCnt = 0;
	this->m_polygon2D.nScaleDir = 1;
	this->m_polygon2D.nDivU = TEX_DIV_U;
	this->m_polygon2D.nDivV = TEX_DIV_V;
	this->m_polygon2D.center = D3DXVECTOR3(PUSHBUTTON_CENTER_X, PUSHBUTTON_CENTER_Y, 0.0f);
	this->m_polygon2D.width = PUSHBUTTON_WIDTH;
	this->m_polygon2D.height = PUSHBUTTON_HEIGHT;

	SetVtx(&m_polygon2D);
}

void C_LOGO_TITLE_PUSHSPACE::Update(){
	this->m_polygon2D.nDispCnt += this->m_polygon2D.nDispDir;

	if (this->m_polygon2D.nDispCnt > PUSHBUTTON_DISP_CNT)//30フレーム毎に描画フラグ切り替え
	{
		this->m_polygon2D.nDispCnt = 0;
		this->m_polygon2D.bDisp ^= 1;
	}
	SetVtx(&m_polygon2D);
}

void C_LOGO_STAGE_CLEAR_1::Init() {
	m_enableUpdate = true;
	m_texNo = TEXTURE_NUM_STAGE_CLEAR;
	m_pTex = GetTex(m_texNo);

	m_polygon2D.isUseTex = true;


	m_polygon2D.A = 255;
	m_polygon2D.R = 255;
	m_polygon2D.G = 255;
	m_polygon2D.B = 255;
	m_polygon2D.AnimPat = 0;
	m_polygon2D.MaxAnimPat = 1;
	m_polygon2D.fRad = 0.0f;
	m_polygon2D.nDivU = 1;
	m_polygon2D.nDivV = 1;
	m_polygon2D.pos = D3DXVECTOR3((float)SCREEN_CENTER_X, (float)SCREEN_CENTER_Y, 0.0f);
	m_polygon2D.center  = D3DXVECTOR3((float)SCREEN_CENTER_X, (float)SCREEN_CENTER_Y, 0.0f);
	m_polygon2D.scale = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
	m_polygon2D.width = (float)SCREEN_WIDTH;
	m_polygon2D.height = (float)SCREEN_HEIGHT;

	SetVtx(&m_polygon2D);

}

void C_LOGO_STAGE_CLEAR_1::Update()
{
	SetVtx(&m_polygon2D);
}

void C_LOGO_GAME_OVER::Init()
{
	m_enableUpdate = true;
	m_texNo = TEXTURE_NUM_GAMEOVER;
	m_pTex = GetTex(m_texNo);

	m_polygon2D.isUseTex = true;


	m_polygon2D.A = 255;
	m_polygon2D.R = 255;
	m_polygon2D.G = 255;
	m_polygon2D.B = 255;
	m_polygon2D.AnimPat = 0;
	m_polygon2D.MaxAnimPat = 1;
	m_polygon2D.fRad = 0.0f;
	m_polygon2D.nDivU = 1;
	m_polygon2D.nDivV = 1;
	m_polygon2D.pos = D3DXVECTOR3((float)SCREEN_CENTER_X, (float)SCREEN_CENTER_Y, 0.0f);
	m_polygon2D.center = D3DXVECTOR3((float)SCREEN_CENTER_X, (float)SCREEN_CENTER_Y, 0.0f);
	m_polygon2D.scale = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
	m_polygon2D.width = (float)SCREEN_WIDTH;
	m_polygon2D.height = (float)SCREEN_HEIGHT;
}

void C_LOGO_GAME_OVER::Update()
{
	SetVtx(&m_polygon2D);
}
