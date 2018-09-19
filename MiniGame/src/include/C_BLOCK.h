#ifndef _C_BLOCK_H_
#define _C_BLOCK_H_

#include "object.h"
#include "C_BASE_OBJECT_MANAGER.h"

#define BLOCK_SIZE (20.0f)
#define BLOCK_NUM_0 ((int)(SCREEN_WIDTH / BLOCK_SIZE) + 1) 
#define BLOCK_NUM_1 ((int)(SCREEN_WIDTH / BLOCK_SIZE) + 1) //1ラインのブロック数
#define BLOCK_NUM_2 (14)
#define BLOCK_LINE_NUM (3)

//プロトタイプ
void InitBlock();
ST_POLYGON_2D *GetBlock();

//クラス宣言

class C_BLOCK : public C_OBJECT{
private:

public:
	void Init() override {}

	void Uninit() override {}

	void Update() override {}
};

class C_BLOCK_MANAGER :public C_BASE_OBJECT_MANAGER {
private:
	C_BLOCK *m_block0;
	C_BLOCK *m_Block1;
	C_BLOCK *m_block2;
	int m_blockNum0;
	int m_blockNum1;
	int m_blockNum2;
public:

	void Init() override;

	void Uninit() override;

	void Update() override;

	void Draw() override;

	ST_POLYGON_2D *GetBlock();
};

#endif // !_C_BLOCK_H_
