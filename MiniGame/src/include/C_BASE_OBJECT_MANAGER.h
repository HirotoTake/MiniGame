#ifndef _BASE_OBJECT_MANAGER_
#define _BASE_OBJECT_MANAGER_


//オブジェクト群を管理するクラスのベース
class C_BASE_OBJECT_MANAGER {
public:
	virtual void Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
};


#endif // !_BASE_OBJECT_MANAGER_
