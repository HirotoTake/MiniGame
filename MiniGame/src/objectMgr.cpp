#include "include\objectMgr.h"
#include "include\C_BASE_OBJECT_MANAGER.h"

//�I�u�W�F�N�g
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

//�I�u�W�F�N�g�ǉ�
void AddObject(C_OBJECT *objectData) {
	g_object.AddObject(objectData);
}


//������
void C_OBJECT_MANAGER::Init()
{ 
	for (auto itr = m_object.begin(); itr != m_object.end(); itr++) {
		(*itr)->Init();
	}
}
//�I�u�W�F�N�g�I������
void C_OBJECT_MANAGER::Uninit() {
	for (auto itr = m_object.begin(); itr != m_object.end(); itr++) {
		(*itr)->Uninit();	//�������J��
	}

}
//�I�u�W�F�N�g���
void C_OBJECT_MANAGER::Release()
{
	for (auto itr = m_object.begin(); itr != m_object.end(); itr++) {
		(*itr)->Release();
	}
	m_object.clear();	//�T�C�Y��0�ɂ���
}
//�X�V
void C_OBJECT_MANAGER::Update() { 
	for (auto itr = m_object.begin(); itr != m_object.end(); itr++) {	
		(*itr)->Update();
	}
}
//�`��
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
