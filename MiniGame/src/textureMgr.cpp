
//********** �C���N���[�h **********
#include "include\common.h"
#include "include\texturemgr.h"
#include "include\sceneMgr.h"
#include "include\stageManager.h"


//********** �萔�E�}�N�� **********
//�e�N�X�`�����i�[����Ă���t�@�C���p�X�̔z��
//�e�N�X�`���ԍ��ƑΉ������Ĕz��Ɋi�[����
const TCHAR *texPathArray[TEXTURE_NUM_MAX] = 
	{ TEX_PATH_TITLE, TEX_PATH_STAGE_ICON, TEX_PATH_PLAYER,  TEX_PATH_GOAL, TEX_PATH_BLOCK,TEX_PATH_STAGE_BG,
	TEX_PATH_GAMEOVER, TEX_PATH_GIDE_SELECT,
	TEX_PATH_STAGE_CLEAR,TEX_PATH_NUMBER,TEX_PATH_GIDE_STAGE,
};

//�e�N�X�`���ԍ��i�[�z��
//�擪�ɂ͕K���e�N�X�`���g�p��, �Q�Ԗڈȍ~�͎g�p����e�N�X�`���ԍ����i�[
//!!!!!�Ō�ɕK�� [-1] ���i�[���A�I�~���Ƃ���
const int texPathSceneArray[SCENE_NUM_MAX][10] = {
	{ 2, TEXTURE_NUM_TITLE, TEXTURE_NUM_STAGE_BG, -1},	//�^�C�g��
	{ 3, TEXTURE_NUM_STAGE_ICON, TEXTURE_NUM_STAGE_BG , TEXTURE_NUM_GIDE_SELECT, -1 },//�X�e�[�W�I��
	{0,-1},//�X�e�[�W
	{ 3, TEXTURE_NUM_STAGE_CLEAR, TEXTURE_NUM_STAGE_BG ,TEXTURE_NUM_TITLE, -1 },//�X�e�[�W�N���A
	{ 3, TEXTURE_NUM_GAMEOVER,TEXTURE_NUM_STAGE_BG,TEXTURE_NUM_TITLE, -1},//�Q�[���I�[�o�[

	//{ 1, TEXTURE_NUM_GAMEOVER, -1 },
};

const int texPathStageArray[STAGE_NUM_MAX][10] = {
	{ 6, TEXTURE_NUM_PLAYER, TEXTURE_NUM_STAGE_BG,TEXTURE_NUM_GOAL, TEXTURE_NUM_BLOCK,TEXTURE_NUM_NUMBER,TEXTURE_NUM_GIDE_STAGE, -1 },
	{ 5, TEXTURE_NUM_PLAYER, TEXTURE_NUM_STAGE_BG,TEXTURE_NUM_GOAL, TEXTURE_NUM_BLOCK,TEXTURE_NUM_NUMBER, -1 },
	{ 5, TEXTURE_NUM_PLAYER, TEXTURE_NUM_STAGE_BG,TEXTURE_NUM_GOAL, TEXTURE_NUM_BLOCK,TEXTURE_NUM_NUMBER,-1 },
}; 

C_TEX_MANAGER g_textrue;


void InitTex() {
	g_textrue.Init();
}

void UninitTex() {
	g_textrue.Uninit();
}

void UpdateTex() {
	g_textrue.Update();
}

LPDIRECT3DTEXTURE9 GetTex(TEXTURE_NUM num) {
	return *g_textrue.GetTex(num);
}

C_TEX_MANAGER::~C_TEX_MANAGER()
{
	DestroyTex();
}

//�e�N�X�`�����j��
void C_TEX_MANAGER::DestroyTex()
{
	if (m_pTex) {
		if (m_texNum > 1) {
			delete[] m_pTex;
		}
		else {
			delete m_pTex;
		}
		m_pTex = NULL;
	}
}


//������
void C_TEX_MANAGER::Init() {
	HRESULT hr = S_OK;
	SCENE work1 = GetScene();	//�V�[���ԍ��擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	DestroyTex();

	//�X�e�[�W�ڍs���̓X�e�[�W�ɉ������e�N�X�`�����ǂݍ���
	if (work1.sceneNum == SCENE_NUM_GAME) {
		STAGE work2 = GetStage();

		this->m_pTex = new LPDIRECT3DTEXTURE9[texPathStageArray[work2.stageNum][0]];
		this->m_texNum = texPathStageArray[work2.stageNum][0];
		for (int i = 1; texPathStageArray[work2.stageNum][i] != -1; i++) {
			hr = D3DXCreateTextureFromFile(pDevice, texPathArray[texPathStageArray[work2.stageNum][i]], (this->m_pTex + i - 1));
			if (FAILED(hr)) {
				this->m_pTex[i] = NULL;
				MessageBox(NULL, _T("�摜�ǂݍ��݃G���["), texPathArray[texPathStageArray[work2.stageNum][i]], MB_OK);
			}
		}
	}
	else {
		this->m_pTex = new LPDIRECT3DTEXTURE9[texPathSceneArray[work1.sceneNum][0]];
		this->m_texNum = texPathSceneArray[work1.sceneNum][0];
		for (int i = 1; texPathSceneArray[work1.sceneNum][i] != -1; i++) {
			hr = D3DXCreateTextureFromFile(pDevice, texPathArray[texPathSceneArray[work1.sceneNum][i]], (this->m_pTex + i - 1));
			if (FAILED(hr)) {
				this->m_pTex[i] = NULL;
				MessageBox(NULL, _T("�摜�ǂݍ��݃G���["), texPathArray[texPathSceneArray[work1.sceneNum][i]], MB_OK);
			}
		}
	}
}

void C_TEX_MANAGER::Uninit()
{
	if (m_pTex) {
		if (m_texNum > 1) {
			delete[] m_pTex;
		}
		else {
			delete m_pTex;
		}
		m_pTex = NULL;
	}
}

void C_TEX_MANAGER::Update()
{
	SCENE work1 = GetScene();
	STAGE work2 = GetStage();

	if (work2.stageNum != work2.stageNumNext || work1.sceneNum != work1.sceneNumNext) {
		DestroyTex();

		Init();
	}
}

LPDIRECT3DTEXTURE9 *C_TEX_MANAGER::GetTex(TEXTURE_NUM num) {
	int ans = -1;	//�v�����ꂽ��񂪊i�[����Ă���v�f�ԍ�
	SCENE work1 = GetScene();
	
	//�T���J�n
	if (work1.sceneNum == SCENE_NUM_GAME) {
		STAGE work2 = GetStage();
		for (int i = 1; texPathStageArray[work2.stageNum][i] != -1; i++) {
			if (texPathStageArray[work2.stageNum][i] == num){
				ans = i - 1;
				break;
			}
		}
	}
	else{
		for (int i = 1; texPathSceneArray[work1.sceneNum][i] != -1; i++) {
			if (texPathSceneArray[work1.sceneNum][i] == num) {
				ans = i - 1;
				break;
			}
		}
	}

	//ans �� -1�̂܂܂Ȃ�v�����ꂽ�e�N�X�`����񂪌�����Ȃ��A�܂��͔z��ɔԍ����o�^����Ă��Ȃ��B
	if (ans != -1) {
		return (m_pTex + ans);
	}
	else {
		return NULL;
	}
}