#ifndef _C_GOAL_OBJ_H_
#define _C_GOAL_OBJ_H_

#include "object.h"

//ゴールオブジェクト

class C_GOAL_OBJ :public C_OBJECT{

public:
	void Init() override;

	void Update() override {}

};

#endif // !_C_GOAL_OBJ_H_

