#ifndef _OBJECT_H_
#define _OBJECT_H_

/*------------------------------------------------------------------------------------------------------/

[ファイル名	:object.h]
製作者	:AT12B171 竹山広人
概要	:

-------------------------------------------------------------------------------------------------------*/

//*************** インクルード ***************
#include "common.h"
#include "polygon.h"



//*************** 定数・マクロ ***************



//*************** プロトタイプ ***************


enum {
	OBJECT_TYPE_DUMMY = 0,	//ダミー	
	OBJECT_TYPE_PLAYER = 1,	//プレイヤー情報
	OBJECT_TYPE_ENEMY,	//敵
	OBJECT_TYPE_GOAL,	//ゴールオブジェクト
	OBJECT_TYPE_BACKGROUND,	//背景
	OBJECT_TYPE_LOGO_TITLE,	//タイトルに使用される各ロゴ
	OBJECT_TYPE_UI_STAGE_SELECT,	//ステージ選択画面に使用されるUI群
	OBJECT_TYPE_FADE,
};



/*
==オブジェクト抽象クラス==
使用方法
各ゲームオブジェクトを生成するときに、C_OBJECTクラスを継承させる
継承後、Init関数とUpdate関数を必ずオーバライドすること

!-初期化手順-!
1-1.m_objectTypeに識別番号を代入
1-2.m_objectNumMaxに生成するオブジェクト数を代入
1-3.CreateObject関数を呼べば、1-2で設定した分の配列のメモリが確保される

!-頂点設定方法-!
2-1.m_objectのメンバ変数にST_POLYGON_2D構造体のm_polygon2Dがあり、各変数にポリゴン情報を設定する
 or
2-2.頂点情報配列を自分で計算したいときは、m_Vtxを使用する。

2-3.m_polygon2DのisUseTexで、テクスチャを使用するかどうかを設定できる

3.m_objectのメンバ関数SetTexで、使用するテクスチャの番号を引数として渡し、テクスチャの設定をする
  ※テクスチャ番号はtextureMgr.hを参照
  ↓重要
4.設定後、2-1の場合は引数無しのUpdateVtx呼び頂点更新, 2-2の場合は引数ありのUpdateVtxで頂点配列の先頭アドレスを渡し更新する
*/
class C_OBJECT{
protected:
	C_POLYGON_2D *m_object;	//オブジェクトポリゴン情報配列
	int m_objectNumMax;	//オブジェクト生成数(最大数)
	unsigned char m_objectType;	//オブジェクト識別番号

public:
	C_OBJECT();
	virtual ~C_OBJECT();

	virtual void Init() = 0;
	virtual void Update() = 0;

	//終了処理(メンバ変数の解放など
	void Uninit();
	
	//自信を解放
	void Release() { Uninit(); delete this; }
	
	//描画
	void Draw();

	void CreateObject() { m_object = new C_POLYGON_2D[m_objectNumMax]; }
	//オブジェクト識別番号取得
	unsigned char GetObjectType() { return this->m_objectType; }
};

#endif