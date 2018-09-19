#ifndef _BASE_STAGE_H_
#define _BASE_STAGE_H_

class C_BASE_STAGE {
public:
	bool clear;
	 virtual void Init() = 0;
	 virtual void Uninit() = 0;
	 virtual void Update() = 0;
	 virtual void enableStageClear() = 0;
	 void SetStageClear(bool flag) { clear = flag; }
};

#endif // !_BASE_SCENE_H_
