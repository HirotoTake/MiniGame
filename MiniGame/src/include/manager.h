#ifndef _MANAGER_H_
#define _MANAGER_H_

//�Ǘ��p���N���X
class C_MANAGER {
protected:

public:
	C_MANAGER();

	virtual void Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
};

#endif // !_MANAGER_H_
