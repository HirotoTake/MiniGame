#ifndef _TIMER_H_
#define _TIMER_H_

#include "object.h"
#include "objectMgr.h"

class C_TIMER: public C_OBJECT {

public:
	void Init() {}

	void Uninit() {}

	void Update() {}

};

class C_TIMER_MANAGER : public C_BASE_OBJECT_MANAGER {
private:
	C_TIMER *m_timer;
	int m_time;
	int m_frameCnt;
	bool end;
public:
	void Init();

	void Uninit();

	void Update();

	void Draw();
};


#endif