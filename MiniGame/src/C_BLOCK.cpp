
#include "include\C_BLOCK.h"
#include "include\sceneMgr.h"
#include "include\objectMgr.h"


static C_BLOCK_MANAGER *g_block;

void InitBlock() {
	g_block = new C_BLOCK_MANAGER;
	AddObjectManager(g_block);
}


ST_POLYGON_2D *GetBlock() {
	return g_block->GetBlock();
}

void C_BLOCK_MANAGER::Init()
{
	//全ステージ共通で３ラインブロック生成
	

	
	STAGE stage = GetStage();
	switch (stage.stageNum)
	{
	case STAGE_NUM_STAGE_1:	
		m_blockNum0 = BLOCK_NUM_0;
		m_block0 = new C_BLOCK[BLOCK_NUM_0];

		for (int i = 0; i < m_blockNum0; i++) {
			(m_block0 + i)->m_texNo = TEXTURE_NUM_BLOCK;
			(m_block0 + i)->m_pTex = GetTex((m_block0 + i)->m_texNo);
			(m_block0 + i)->m_polygon2D.bEnableUpToDown = false;
			(m_block0 + i)->m_polygon2D.isUseTex = true;
			(m_block0 + i)->m_polygon2D.AnimPat = 0;
			(m_block0 + i)->m_polygon2D.MaxAnimPat = 1;
			(m_block0 + i)->m_polygon2D.nDivU = 1;
			(m_block0 + i)->m_polygon2D.nDivV = 1;
			(m_block0 + i)->m_polygon2D.scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			(m_block0 + i)->m_polygon2D.width = BLOCK_SIZE;
			(m_block0 + i)->m_polygon2D.height = BLOCK_SIZE;
			(m_block0 + i)->m_polygon2D.center = D3DXVECTOR3((m_block0 + i)->m_polygon2D.width / 2.0f, (m_block0 + i)->m_polygon2D.height / 2.0f, 0.0f);
			(m_block0 + i)->m_polygon2D.fRad = D3DXToRadian(0.0f);
			(m_block0 + i)->m_polygon2D.pos = D3DXVECTOR3(0.0f + (float)(i * BLOCK_SIZE) , SCREEN_LIMIT_UNDER, 0.0f);
			(m_block0 + i)->m_polygon2D.A = 255;
			(m_block0 + i)->m_polygon2D.R = 255;
			(m_block0 + i)->m_polygon2D.G = 255;
			(m_block0 + i)->m_polygon2D.B = 255;
			(m_block0 + i)->SetVtx(&(m_block0 + i)->m_polygon2D);
		}
	break;

	case STAGE_NUM_STAGE_2:
		m_blockNum1 = BLOCK_NUM_1 * BLOCK_LINE_NUM;
		m_Block1 = new C_BLOCK[m_blockNum1];
		for (int i = 0; i < BLOCK_LINE_NUM; i++) {
			for (int j = 0; j < BLOCK_NUM_1; j++) {

				(m_Block1 + j + (i * BLOCK_NUM_1))->m_texNo = TEXTURE_NUM_BLOCK;
				(m_Block1 + j + (i * BLOCK_NUM_1))->m_pTex = GetTex((m_Block1 + j + (i * BLOCK_NUM_1))->m_texNo);
				(m_Block1 + j + (i * BLOCK_NUM_1))->m_polygon2D.bEnableUpToDown = true;
				(m_Block1 + j + (i * BLOCK_NUM_1))->m_polygon2D.isUseTex = true;
				(m_Block1 + j + (i * BLOCK_NUM_1))->m_polygon2D.AnimPat = 0;
				(m_Block1 + j + (i * BLOCK_NUM_1))->m_polygon2D.MaxAnimPat = 1;
				(m_Block1 + j + (i * BLOCK_NUM_1))->m_polygon2D.nDivU = 1;
				(m_Block1 + j + (i * BLOCK_NUM_1))->m_polygon2D.nDivV = 1;
				(m_Block1 + j + (i * BLOCK_NUM_1))->m_polygon2D.scale = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
				(m_Block1 + j + (i * BLOCK_NUM_1))->m_polygon2D.width = BLOCK_SIZE;
				(m_Block1 + j + (i * BLOCK_NUM_1))->m_polygon2D.height = BLOCK_SIZE;
				(m_Block1 + j + (i * BLOCK_NUM_1))->m_polygon2D.center = D3DXVECTOR3(m_Block1->m_polygon2D.width / 2.0f, m_Block1->m_polygon2D.height / 2.0f, 0.0f);
				(m_Block1 + j + (i * BLOCK_NUM_1))->m_polygon2D.fRad = D3DXToRadian(0.0f);
				(m_Block1 + j + (i * BLOCK_NUM_1))->m_polygon2D.pos = D3DXVECTOR3(0.0f + (float)(j * BLOCK_SIZE) + (float)(BLOCK_SIZE / 2.0f), SCREEN_LIMIT_UNDER - (i * (BLOCK_SIZE * 7)), 0.0f);
				(m_Block1 + j + (i * BLOCK_NUM_1))->m_polygon2D.A = 255;
				(m_Block1 + j + (i * BLOCK_NUM_1))->m_polygon2D.R = 255;
				(m_Block1 + j + (i * BLOCK_NUM_1))->m_polygon2D.G = 255;
				(m_Block1 + j + (i * BLOCK_NUM_1))->m_polygon2D.B = 255;
				(m_Block1 + j + (i * BLOCK_NUM_1))->SetVtx(&(m_Block1 + j + (i * BLOCK_NUM_1))->m_polygon2D);
			}
		}
		
		
		break;
	case STAGE_NUM_STAGE_3:
		m_blockNum1 = BLOCK_NUM_1 * BLOCK_LINE_NUM;
		m_Block1 = new C_BLOCK[m_blockNum1];
		for (int i = 0; i < BLOCK_LINE_NUM; i++) {
			for (int j = 0; j < BLOCK_NUM_1; j++) {

				(m_Block1 + j + (i * BLOCK_NUM_1))->m_texNo = TEXTURE_NUM_BLOCK;
				(m_Block1 + j + (i * BLOCK_NUM_1))->m_pTex = GetTex((m_Block1 + j + (i * BLOCK_NUM_1))->m_texNo);
				(m_Block1 + j + (i * BLOCK_NUM_1))->m_polygon2D.bEnableUpToDown = true;
				(m_Block1 + j + (i * BLOCK_NUM_1))->m_polygon2D.isUseTex = true;
				(m_Block1 + j + (i * BLOCK_NUM_1))->m_polygon2D.AnimPat = 0;
				(m_Block1 + j + (i * BLOCK_NUM_1))->m_polygon2D.MaxAnimPat = 1;
				(m_Block1 + j + (i * BLOCK_NUM_1))->m_polygon2D.nDivU = 1;
				(m_Block1 + j + (i * BLOCK_NUM_1))->m_polygon2D.nDivV = 1;
				(m_Block1 + j + (i * BLOCK_NUM_1))->m_polygon2D.scale = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
				(m_Block1 + j + (i * BLOCK_NUM_1))->m_polygon2D.width = BLOCK_SIZE;
				(m_Block1 + j + (i * BLOCK_NUM_1))->m_polygon2D.height = BLOCK_SIZE;
				(m_Block1 + j + (i * BLOCK_NUM_1))->m_polygon2D.center = D3DXVECTOR3(m_Block1->m_polygon2D.width / 2.0f, m_Block1->m_polygon2D.height / 2.0f, 0.0f);
				(m_Block1 + j + (i * BLOCK_NUM_1))->m_polygon2D.fRad = D3DXToRadian(0.0f);
				(m_Block1 + j + (i * BLOCK_NUM_1))->m_polygon2D.pos = D3DXVECTOR3(0.0f + (float)(j * BLOCK_SIZE) + (float)(BLOCK_SIZE / 2.0f), SCREEN_LIMIT_UNDER - (i * (BLOCK_SIZE * 7)), 0.0f);
				(m_Block1 + j + (i * BLOCK_NUM_1))->m_polygon2D.A = 255;
				(m_Block1 + j + (i * BLOCK_NUM_1))->m_polygon2D.R = 255;
				(m_Block1 + j + (i * BLOCK_NUM_1))->m_polygon2D.G = 255;
				(m_Block1 + j + (i * BLOCK_NUM_1))->m_polygon2D.B = 255;
				(m_Block1 + j + (i * BLOCK_NUM_1))->SetVtx(&(m_Block1 + j + (i * BLOCK_NUM_1))->m_polygon2D);
			}
		}

		m_blockNum2 = BLOCK_NUM_2;
		m_block2 = new C_BLOCK[m_blockNum2];

		for (int i = 0; i < m_blockNum2; i++) {

			(m_block2 + i)->m_enableUpdate = true;
			(m_block2 + i)->m_texNo = TEXTURE_NUM_BLOCK;
			(m_block2 + i)->m_pTex = GetTex((m_block2 + i)->m_texNo);
			(m_block2 + i)->m_polygon2D.bEnableUpToDown = false;
			(m_block2 + i)->m_polygon2D.isUseTex = true;
			(m_block2 + i)->m_polygon2D.A = 255;
			(m_block2 + i)->m_polygon2D.R = 255;
			(m_block2 + i)->m_polygon2D.G = 255;
			(m_block2 + i)->m_polygon2D.B = 255;
			(m_block2 + i)->m_polygon2D.fRad = 0.0f;
			(m_block2 + i)->m_polygon2D.scale = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
			(m_block2 + i)->m_polygon2D.center = D3DXVECTOR3(BLOCK_SIZE / 2.0f, BLOCK_SIZE / 2.0f, 0.0f);
			(m_block2 + i)->m_polygon2D.pos = D3DXVECTOR3(500.0f, SCREEN_LIMIT_UNDER - BLOCK_SIZE - (i * BLOCK_SIZE), 0.0f);
			(m_block2 + i)->m_polygon2D.AnimPat = 0;
			(m_block2 + i)->m_polygon2D.MaxAnimPat = 1;
			(m_block2 + i)->m_polygon2D.height = BLOCK_SIZE;
			(m_block2 + i)->m_polygon2D.width = BLOCK_SIZE;
			(m_block2 + i)->m_polygon2D.nDivU = 1;
			(m_block2 + i)->m_polygon2D.nDivV = 1;
			(m_block2 + i)->SetVtx(&(m_block2 + i)->m_polygon2D);
		}

		break;
	}
}

void C_BLOCK_MANAGER::Uninit()
{
	STAGE stage = GetStage();
	

	switch (stage.stageNum)
	{
	case STAGE_NUM_STAGE_1:
		for (int i = 0; i < m_blockNum0; i++) (m_block0 + i)->Uninit();
		delete[] m_block0;
		break;

	case STAGE_NUM_STAGE_2:
		for (int i = 0; i < m_blockNum1; i++) (m_Block1 + i)->Uninit();
		delete[] m_Block1;
		break;
	case STAGE_NUM_STAGE_3:
		for (int i = 0; i < m_blockNum1; i++) (m_Block1 + i)->Uninit();
		delete[] m_Block1;
		for (int i = 0; i < m_blockNum2; i++) (m_block2 + i)->Uninit();
		delete[] m_block2;
		break;
	}
	delete this;

}

void C_BLOCK_MANAGER::Update()
{

}

void C_BLOCK_MANAGER::Draw()
{
	
	STAGE work = GetStage();
	switch (work.stageNum)
	{
	case STAGE_NUM_STAGE_1:
		for (int i = 0; i < m_blockNum0; i++) (m_block0 + i)->Draw();
		break;
	case STAGE_NUM_STAGE_2:
		for (int i = 0; i < m_blockNum1; i++) (m_Block1 + i)->Draw();
		break;
	case STAGE_NUM_STAGE_3:
		for (int i = 0; i < m_blockNum1; i++) (m_Block1 + i)->Draw();
		for (int i = 0; i < m_blockNum2; i++) (m_block2 + i)->Draw();
		break;

	}
	
}

ST_POLYGON_2D *C_BLOCK_MANAGER::GetBlock()
{
	ST_POLYGON_2D *work;
	
	STAGE stage = GetStage();
	switch (stage.stageNum) {
	case STAGE_NUM_STAGE_1:
			work = new ST_POLYGON_2D[BLOCK_NUM_0];
			for (int i = 0; i < BLOCK_NUM_0; i++) {
				*(work + i) = (m_block0 + i)->m_polygon2D;
			}
			break;
	case STAGE_NUM_STAGE_2:
		work = new ST_POLYGON_2D[BLOCK_NUM_1 * BLOCK_LINE_NUM];
		for (int i = 0; i < BLOCK_NUM_1 * BLOCK_LINE_NUM; i++) *(work + i) = (m_Block1 + i)->m_polygon2D;
		break;

	case STAGE_NUM_STAGE_3:
		work = new ST_POLYGON_2D[BLOCK_NUM_1 * BLOCK_LINE_NUM + BLOCK_NUM_2];
		for (int i = 0; i < BLOCK_NUM_1 * BLOCK_LINE_NUM + BLOCK_NUM_2; i++) *(work + i) = (m_Block1 + i)->m_polygon2D;
		for(int i = 0; i < BLOCK_NUM_2; i++) *(work + i + BLOCK_NUM_1 * BLOCK_LINE_NUM) = (m_block2 + i)->m_polygon2D;
		break;
	}
	return work;	
}