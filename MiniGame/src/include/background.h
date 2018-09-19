//background.h
//背景処理
#ifndef ___BACKGROUND_H___
#define ___BACKGROUND_H___

//===================================================
// インクルード部
//===================================================
#include "include\main.h"
#include "polygon.h"
#include "objectMgr.h"

//背景クラス
//シーン番号から自動でテクスチャ情報取得
class C_BACKGROUND : public C_OBJECT {
public:
	void Init() override;
	void Update() override {};
};
//===================================================
// プロトタイプ宣言
//===================================================
void InitBG();

#endif // ___BACKGROUND_H___
