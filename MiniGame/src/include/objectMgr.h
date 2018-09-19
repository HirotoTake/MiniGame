#ifndef _OBJECT_MANAGER_H_
#define _OBJECT_MANAGER_H_

#include "common.h"
#include "C_BASE_OBJECT_MANAGER.h"
#include "object.h"

//オブジェクト管理クラス
//プライベートメンバのオブジェクト動的配列にてすべてのオブジェクトを一元管理する
//各シーン、ステージにて生成されたオブジェクトはこの配列に追加され、管理される。
class C_OBJECT_MANAGER {
private:
	std::vector<C_OBJECT*> m_object;
public:
	//初期化
	void Init();

	//解放
	void Uninit();

	void Update();

	void Release();

	void Draw();

	ST_POLYGON_2D GetObjectPolygonInfo(int objectType);	//オブジェクトの位置情報取得

	//オブジェクト管理クラスのオブジェクト管理用ベクター配列にデータを追加する
	void AddObject(C_OBJECT *objectData) { m_object.push_back(objectData); }

};
void AddObject(C_OBJECT *objectData);

void InitObject();	//オブジェクト初期化
void UninitObject();	//オブジェクト終了(この関数ではメモリ開放まではされない
void UpdateObject();	//オブジェクトアップデート
void DrawObject();	//オブジェクト描画
void ReleaseObject();	//オブジェクト解放(終了処理含む

//オブジェクト識別番号取得
ST_POLYGON_2D GetObjectPolygonInfo(int objectType);


#endif // !_OBJECT_MANAGER_H_