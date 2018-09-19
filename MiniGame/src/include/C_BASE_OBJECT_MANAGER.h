#ifndef _BASE_OBJECT_MANAGER_
#define _BASE_OBJECT_MANAGER_


//�I�u�W�F�N�g�Q���Ǘ�����N���X�̃x�[�X
class C_BASE_OBJECT_MANAGER {
public:
	virtual void Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
};


#endif // !_BASE_OBJECT_MANAGER_
