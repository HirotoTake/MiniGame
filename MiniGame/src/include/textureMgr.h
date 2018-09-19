#ifndef _TEXMGR_H_
#define _TEXMGR_H_

#include "main.h"

#define MAX_TEXTURE (3)

//タイトル
#define TEX_PATH_TITLE _T("data/texture/title/title.png")

//ステージ選択
#define TEX_PATH_STAGE_ICON _T("data/texture/stageselect/stageselect.png")
#define TEX_PATH_STAGE_1_ICON _T("data/texture/stage/stage1/stage1.png")

#define TEX_PATH_PLAYER _T("data/texture/character/player/player1.png")
#define TEX_PATH_GOAL _T("data/texture/map/goal.png")
#define TEX_PATH_BLOCK _T("data/texture/map/block.png")
#define TEX_PATH_STAGE_BG _T("data/texture/map/stage_bg.png")
#define TEX_PATH_GAMEOVER _T("data/texture/gameover/gameover.png")
#define TEX_PATH_GIDE_SELECT _T("data/texture/gide/gide_select.png")
#define TEX_PATH_STAGE_CLEAR _T("data/texture/stageclear/stageclear.png")
#define TEX_PATH_NUMBER _T("data/texture/font/number.png")
#define TEX_PATH_GIDE_STAGE _T("data/texture/gide/gide.png")


//テクスチャ番号
//※新規に追加する場合はCPP内にあるファイルパスの添え字番号と対応させること
typedef enum {
	TEXTURE_NUM_TITLE,
	TEXTURE_NUM_STAGE_ICON,
	TEXTURE_NUM_PLAYER,
	TEXTURE_NUM_GOAL,
	TEXTURE_NUM_BLOCK,
	TEXTURE_NUM_STAGE_BG,
	TEXTURE_NUM_GAMEOVER,
	TEXTURE_NUM_GIDE_SELECT,
	TEXTURE_NUM_STAGE_CLEAR,
	TEXTURE_NUM_NUMBER,
	TEXTURE_NUM_GIDE_STAGE,
	TEXTURE_NUM_MAX,
}TEXTURE_NUM;

//テクスチャ管理クラス
//ゲーム全体に使用するテクスチャを管理
class C_TEX_MANAGER {
private:
	LPDIRECT3DTEXTURE9 *m_pTex;
	int m_texNum;	//現在使用しているテクスチャの枚数
public:
	C_TEX_MANAGER() { m_pTex = NULL; }
	//メモリ開放
	virtual ~C_TEX_MANAGER();

	//初期化時のシーン番号、ステージ番号に対応したテクスチャをロードする
	void Init();
	
	//シーン番号更新時に対応し番号のテクスチャをロード
	void Update();

	//メモリ開放
	void Uninit();

	//現在読み込まれているテクスチャ情報破棄
	//終了時に呼ぶかこの関数の直後にInitTex
	void DestroyTex();

	LPDIRECT3DTEXTURE9 *GetTex(TEXTURE_NUM num);

};


void InitTex();

void UninitTex();

void UpdateTex();

LPDIRECT3DTEXTURE9 GetTex(TEXTURE_NUM num);
#endif