#ifndef _POLYGON_H_
#define _POLYGON_H_

#include "common.h"
#include "textureMgr.h"

#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define FVF_VERTEX_3D (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1)

//���_���\����(2D
typedef struct{
	D3DXVECTOR3 pos;	//���_���W
	float		rhw;	//
	D3DCOLOR	diffuse;	//�F
	float		u, v;		//U, V
}VERTEX_2D;

//���_���\����(3D
typedef struct {
	D3DXVECTOR3 pos;	//���_���W
	D3DXVECTOR3 normal;
	float		u, v;		//U, V
}VERTEX_3D;

//�|���S�����
typedef struct {
	bool isUseTex;	//�e�N�X�`���g�p�t���O

	int nDivU;			//�������i�� ���e�N�X�`���g�p���͕K���w��
	int nDivV;			//������ (�c ���e�N�X�`���g�p���͕K���w��
	float width;		//����
	float height;		//�c��
	float fRad;			//��]
	float fRollCnt;		//��]����p�J�E���g�ϐ�
	int	  nRollDir;		//��]����
	D3DXVECTOR3 scale;	//�X�P�[��
	D3DXVECTOR3 center;	//����
	D3DXVECTOR3 pos;	//���W
	unsigned int A;		//��
	unsigned char R;	//��
	unsigned char G;	//��
	unsigned char B;	//��

	int currentAnimPat;		//�A�j���[�V�����ԍ�
	int MaxAnimPat;		//�A�j���[�V�������
	bool benableUpdateAnimation;
	
	float fScaleCnt;        //�g��k���p�J�E���g
	int   nScaleDir;	    //�g��k���p�J�E���g�X�e�b�v( 1 or -1)
	int	  nDispCnt;			//�`��܂ł̃J�E���g
	int	  nDispDir;			//�J�E���g����( 1 or -1)
	bool  bDisp;			//�`��t���O

	int nAnimCnt;
}ST_POLYGON_2D;

//�|���S���̒��_��������
//���_��4�ŌŒ�
class C_POLYGON_2D{
private:
	VERTEX_2D m_vtx[4];	//���_���
	LPDIRECT3DTEXTURE9 m_pTex;	//�e�N�X�`����� ���e�N�X�`���擾�֐��ɂĂ�textureMgr�Q��

public:
	ST_POLYGON_2D m_polygon2D;	//���_�X�V�p�|���S�����
	VERTEX_2D m_Vtx[4];			//���_���X�V�p�̒��_���z��
	bool m_enableUpdate;		//�X�V�t���O ���ꎞ��~�ȂǂɎg�p
	
	C_POLYGON_2D();
	virtual ~C_POLYGON_2D() {}

	//-- �������E�I�������o�֐� --
	
	
	//-- �X�V�E�Z�b�g�����o�֐� --

	//���_���X�V
	void UpdateVtx();

	//�v�Z�������_��ݒ肵�������p
	void UpdateVtx(VERTEX_2D *vtx);

	void SetTex(TEXTURE_NUM num) { m_pTex =  GetTex(num); }

	//-- �`�惁���o�֐� --
	void Draw();

};

class C_POLYGON_3D {
private:
	VERTEX_3D *m_vtx;
};
#endif // !_POLYGON_H_
