
//********** インクルード **********
#include "include\common.h"
#include "include\texturemgr.h"
#include "include\sceneMgr.h"
#include "include\stageManager.h"


//********** 定数・マクロ **********
//テクスチャが格納されているファイルパスの配列
//テクスチャ番号と対応させて配列に格納する
const TCHAR *texPathArray[TEXTURE_NUM_MAX] = 
	{ TEX_PATH_TITLE, TEX_PATH_STAGE_ICON, TEX_PATH_PLAYER,  TEX_PATH_GOAL, TEX_PATH_BLOCK,TEX_PATH_STAGE_BG,
	TEX_PATH_GAMEOVER, TEX_PATH_GIDE_SELECT,
	TEX_PATH_STAGE_CLEAR,TEX_PATH_NUMBER,TEX_PATH_GIDE_STAGE,
};

//テクスチャ番号格納配列
//先頭には必ずテクスチャ使用数, ２番目以降は使用するテクスチャ番号を格納
//!!!!!最後に必ず [-1] を格納し、終止符とする
const int texPathSceneArray[SCENE_NUM_MAX][10] = {
	{ 2, TEXTURE_NUM_TITLE, TEXTURE_NUM_STAGE_BG, -1},	//タイトル
	{ 3, TEXTURE_NUM_STAGE_ICON, TEXTURE_NUM_STAGE_BG , TEXTURE_NUM_GIDE_SELECT, -1 },//ステージ選択
	{0,-1},//ステージ
	{ 3, TEXTURE_NUM_STAGE_CLEAR, TEXTURE_NUM_STAGE_BG ,TEXTURE_NUM_TITLE, -1 },//ステージクリア
	{ 3, TEXTURE_NUM_GAMEOVER,TEXTURE_NUM_STAGE_BG,TEXTURE_NUM_TITLE, -1},//ゲームオーバー

	//{ 1, TEXTURE_NUM_GAMEOVER, -1 },
};

const int texPathStageArray[STAGE_NUM_MAX][10] = {
	{ 6, TEXTURE_NUM_PLAYER, TEXTURE_NUM_STAGE_BG,TEXTURE_NUM_GOAL, TEXTURE_NUM_BLOCK,TEXTURE_NUM_NUMBER,TEXTURE_NUM_GIDE_STAGE, -1 },
	{ 5, TEXTURE_NUM_PLAYER, TEXTURE_NUM_STAGE_BG,TEXTURE_NUM_GOAL, TEXTURE_NUM_BLOCK,TEXTURE_NUM_NUMBER, -1 },
	{ 5, TEXTURE_NUM_PLAYER, TEXTURE_NUM_STAGE_BG,TEXTURE_NUM_GOAL, TEXTURE_NUM_BLOCK,TEXTURE_NUM_NUMBER,-1 },
}; 

C_TEX_MANAGER g_textrue;


void InitTex() {
	g_textrue.Init();
}

void UninitTex() {
	g_textrue.Uninit();
}

void UpdateTex() {
	g_textrue.Update();
}

LPDIRECT3DTEXTURE9 GetTex(TEXTURE_NUM num) {
	return *g_textrue.GetTex(num);
}

C_TEX_MANAGER::~C_TEX_MANAGER()
{
	DestroyTex();
}

//テクスチャ情報破棄
void C_TEX_MANAGER::DestroyTex()
{
	if (m_pTex) {
		if (m_texNum > 1) {
			delete[] m_pTex;
		}
		else {
			delete m_pTex;
		}
		m_pTex = NULL;
	}
}


//初期化
void C_TEX_MANAGER::Init() {
	HRESULT hr = S_OK;
	SCENE work1 = GetScene();	//シーン番号取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	DestroyTex();

	//ステージ移行中はステージに応じたテクスチャ情報読み込み
	if (work1.sceneNum == SCENE_NUM_GAME) {
		STAGE work2 = GetStage();

		this->m_pTex = new LPDIRECT3DTEXTURE9[texPathStageArray[work2.stageNum][0]];
		this->m_texNum = texPathStageArray[work2.stageNum][0];
		for (int i = 1; texPathStageArray[work2.stageNum][i] != -1; i++) {
			hr = D3DXCreateTextureFromFile(pDevice, texPathArray[texPathStageArray[work2.stageNum][i]], (this->m_pTex + i - 1));
			if (FAILED(hr)) {
				this->m_pTex[i] = NULL;
				MessageBox(NULL, _T("画像読み込みエラー"), texPathArray[texPathStageArray[work2.stageNum][i]], MB_OK);
			}
		}
	}
	else {
		this->m_pTex = new LPDIRECT3DTEXTURE9[texPathSceneArray[work1.sceneNum][0]];
		this->m_texNum = texPathSceneArray[work1.sceneNum][0];
		for (int i = 1; texPathSceneArray[work1.sceneNum][i] != -1; i++) {
			hr = D3DXCreateTextureFromFile(pDevice, texPathArray[texPathSceneArray[work1.sceneNum][i]], (this->m_pTex + i - 1));
			if (FAILED(hr)) {
				this->m_pTex[i] = NULL;
				MessageBox(NULL, _T("画像読み込みエラー"), texPathArray[texPathSceneArray[work1.sceneNum][i]], MB_OK);
			}
		}
	}
}

void C_TEX_MANAGER::Uninit()
{
	if (m_pTex) {
		if (m_texNum > 1) {
			delete[] m_pTex;
		}
		else {
			delete m_pTex;
		}
		m_pTex = NULL;
	}
}

void C_TEX_MANAGER::Update()
{
	SCENE work1 = GetScene();
	STAGE work2 = GetStage();

	if (work2.stageNum != work2.stageNumNext || work1.sceneNum != work1.sceneNumNext) {
		DestroyTex();

		Init();
	}
}

LPDIRECT3DTEXTURE9 *C_TEX_MANAGER::GetTex(TEXTURE_NUM num) {
	int ans = -1;	//要求された情報が格納されている要素番号
	SCENE work1 = GetScene();
	
	//探索開始
	if (work1.sceneNum == SCENE_NUM_GAME) {
		STAGE work2 = GetStage();
		for (int i = 1; texPathStageArray[work2.stageNum][i] != -1; i++) {
			if (texPathStageArray[work2.stageNum][i] == num){
				ans = i - 1;
				break;
			}
		}
	}
	else{
		for (int i = 1; texPathSceneArray[work1.sceneNum][i] != -1; i++) {
			if (texPathSceneArray[work1.sceneNum][i] == num) {
				ans = i - 1;
				break;
			}
		}
	}

	//ans が -1のままなら要求されたテクスチャ情報が見つからない、または配列に番号が登録されていない。
	if (ans != -1) {
		return (m_pTex + ans);
	}
	else {
		return NULL;
	}
}