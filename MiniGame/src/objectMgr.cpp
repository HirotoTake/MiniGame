#include "include\objectMgr.h"
#include "include\C_BASE_OBJECT_MANAGER.h"

//オブジェクト
static C_OBJECT_MANAGER g_object;

void InitObject() {
	g_object.Init();
}
void UninitObject() {
	g_object.Uninit();
}
void UpdateObject() {
	g_object.Update();
}
void DrawObject() {
	g_object.Draw();
}
void ReleaseObject()
{
	g_object.Release();
}
ST_POLYGON_2D GetObjectPolygonInfo(int objectType)
{
	return g_object.GetObjectPolygonInfo(objectType);
}

//オブジェクト追加
void AddObject(C_OBJECT *objectData) {
	g_object.AddObject(objectData);
}


//初期化
void C_OBJECT_MANAGER::Init()
{ 
	for (auto itr = m_object.begin(); itr != m_object.end(); itr++) {
		(*itr)->Init();
	}
}
//オブジェクト終了処理
void C_OBJECT_MANAGER::Uninit() {
	for (auto itr = m_object.begin(); itr != m_object.end(); itr++) {
		(*itr)->Uninit();	//メモリ開放
	}

}
//オブジェクト解放
void C_OBJECT_MANAGER::Release()
{
	for (auto itr = m_object.begin(); itr != m_object.end(); itr++) {
		(*itr)->Release();
	}
	m_object.clear();	//サイズを0にする
}
//更新
void C_OBJECT_MANAGER::Update() { 
	for (auto itr = m_object.begin(); itr != m_object.end(); itr++) {	
		(*itr)->Update();
	}
}
//描画
void C_OBJECT_MANAGER::Draw() { 
	for (auto itr = m_object.begin(); itr != m_object.end(); itr++) {
		(*itr)->Draw();
	}
}

ST_POLYGON_2D C_OBJECT_MANAGER::GetObjectPolygonInfo(int objectType)
{
	ST_POLYGON_2D empty = { 0 };
	return empty;
}
