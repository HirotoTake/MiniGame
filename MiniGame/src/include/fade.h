// ポリゴン処理
#ifndef _FADE_H_
#define _FADE_H_

//#define FADE

#include <Windows.h>
#include "object.h"

class C_FADE:public C_OBJECT {
private:
	int m_nFade;	//フェードタイム
	int m_nDir;	//１フレーム分のフェードタイム
	bool m_isFadeIn; //フェードイン中フラグ
	bool m_isFadeOut; //フェードアウト中フラグ
	bool m_isFade; //フェード中フラグ
public:
	void Init() override;
	void Update() override;

	void StarFadeIn();
	void StarFadeOut();

	int EndFadeIn();
	int EndFadeOut();

};

// プロトタイプ宣言
HRESULT InitFade();
void UpdateFade();
void UninitFade();
void DrawFade();
void StartFadeIn();
void StartFadeOut();
int  EndFadeIn();
int  EndFadeOut();
#endif
