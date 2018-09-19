#ifndef _LOGO_CLASS_

#define _LOGO_CLASS_

#include "polygon.h"
#include "object.h"
#include "textureMgr.h"

//ロゴ管理クラス
//継承元：C_POLYGON_2D

//タイトルロゴ管理
class C_LOGO_TITLE : public C_OBJECT {
public:
	~C_LOGO_TITLE() {};
	void Init() override;

	void Uninit() override { /*delete(this);*/ };

	void Update() override;
};

//タイトルロゴ管理
class C_LOGO_TITLE_PUSHSPACE :public C_OBJECT {
public:

	void Init() override;

	void Update() override;

	void Draw() override { if (!this->m_polygon2D.bDisp) return; else C_OBJECT::Draw(); }
};

class C_LOGO_STAGE_CLEAR_1 :public C_OBJECT{
public:
	void Init() override;

	void Update() override;

	
};

class C_LOGO_GAME_OVER :public C_OBJECT {
public:
	void Init() override;

	void Update() override;


};
#endif // !_LOGO_CLASS_

