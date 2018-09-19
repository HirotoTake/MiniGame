#ifndef _POLYGON_H_
#define _POLYGON_H_

#include "common.h"
#include "textureMgr.h"

#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define FVF_VERTEX_3D (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1)

//頂点情報構造体(2D
typedef struct{
	D3DXVECTOR3 pos;	//頂点座標
	float		rhw;	//
	D3DCOLOR	diffuse;	//色
	float		u, v;		//U, V
}VERTEX_2D;

//頂点情報構造体(3D
typedef struct {
	D3DXVECTOR3 pos;	//頂点座標
	D3DXVECTOR3 normal;
	float		u, v;		//U, V
}VERTEX_3D;

//ポリゴン情報
typedef struct {
	bool isUseTex;	//テクスチャ使用フラグ

	int nDivU;			//分割数（横 ※テクスチャ使用時は必ず指定
	int nDivV;			//分割数 (縦 ※テクスチャ使用時は必ず指定
	float width;		//横幅
	float height;		//縦幅
	float fRad;			//回転
	float fRollCnt;		//回転制御用カウント変数
	int	  nRollDir;		//回転方向
	D3DXVECTOR3 scale;	//スケール
	D3DXVECTOR3 center;	//中央
	D3DXVECTOR3 pos;	//座標
	unsigned int A;		//α
	unsigned char R;	//赤
	unsigned char G;	//緑
	unsigned char B;	//青

	int currentAnimPat;		//アニメーション番号
	int MaxAnimPat;		//アニメーション種類
	bool benableUpdateAnimation;
	
	float fScaleCnt;        //拡大縮小用カウント
	int   nScaleDir;	    //拡大縮小用カウントステップ( 1 or -1)
	int	  nDispCnt;			//描画までのカウント
	int	  nDispDir;			//カウント方向( 1 or -1)
	bool  bDisp;			//描画フラグ

	int nAnimCnt;
}ST_POLYGON_2D;

//ポリゴンの頂点情報を扱う
//頂点は4つで固定
class C_POLYGON_2D{
private:
	VERTEX_2D m_vtx[4];	//頂点情報
	LPDIRECT3DTEXTURE9 m_pTex;	//テクスチャ情報 ※テクスチャ取得関数につてはtextureMgr参照

public:
	ST_POLYGON_2D m_polygon2D;	//頂点更新用ポリゴン情報
	VERTEX_2D m_Vtx[4];			//頂点情報更新用の頂点情報配列
	bool m_enableUpdate;		//更新フラグ ※一時停止などに使用
	
	C_POLYGON_2D();
	virtual ~C_POLYGON_2D() {}

	//-- 初期化・終了メンバ関数 --
	
	
	//-- 更新・セットメンバ関数 --

	//頂点情報更新
	void UpdateVtx();

	//計算した頂点を設定したい時用
	void UpdateVtx(VERTEX_2D *vtx);

	void SetTex(TEXTURE_NUM num) { m_pTex =  GetTex(num); }

	//-- 描画メンバ関数 --
	void Draw();

};

class C_POLYGON_3D {
private:
	VERTEX_3D *m_vtx;
};
#endif // !_POLYGON_H_
