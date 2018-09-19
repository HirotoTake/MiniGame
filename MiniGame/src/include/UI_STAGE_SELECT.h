#ifndef _UI_STAGE_SELECT_H_
#define _UI_STAGE_SELECT_H_

#include "polygon.h"
#include "C_BASE_OBJECT_MANAGER.h"
#include "textureMgr.h"
#include "object.h"

//ステージアイコン５つ同時に処理したいのでC_UI_STAGE_SELECT_ICONで管理
class C_STAGE_UI:public C_OBJECT {
public:
	void Init() override {}

	void Uninit() override {}

	void Update() override {}
};

class C_STAGE_SELECT_UI_GIDE_SELECT:public C_OBJECT{
public:
	void Init() override;

	void Update() override;

	void Uninit() override {}

};

//ステージアイコンオブジェクト管理
class C_UI_STAGE_SELECT_ICON{
private:
	C_STAGE_UI *m_stageIcon;
public:
	void Init();

	void Uninit() ;

	void Update() ;

	void Draw() {
		for (int i =0; i < 5; i++) { (m_stageIcon + i)->Draw(); }
	}

};



class C_OBJECT_MANAGER_UI_STAGE_SELECT:public C_BASE_OBJECT_MANAGER {
	C_UI_STAGE_SELECT_ICON *m_UI_stageIcon;
	C_STAGE_SELECT_UI_GIDE_SELECT *m_gide_select;

public:

	void Init() override;

	void Uninit() override;

	void Update() override;

	void Draw() override;

};

#endif // !

