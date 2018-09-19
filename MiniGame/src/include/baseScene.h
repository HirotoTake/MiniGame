#ifndef _BASE_SCENE_H_
#define _BASE_SCENE_H_


class C_BASE_SCENE {
	
public:
	 virtual void Init() = 0;
	 virtual void Uninit() = 0;
	 virtual void Update() = 0;
};

#endif // !_BASE_SCENE_H_
