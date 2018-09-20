#include "include\common.h"
#include "include\polygon.h"

static LPDIRECT3DDEVICE9 g_pDevice;	//デバイス情報

C_POLYGON_2D::C_POLYGON_2D() {
	m_polygon2D = { 0 };
	m_pTex = NULL;
}

void C_POLYGON_2D::UpdateVtx() {

	float s = sinf(this->m_polygon2D.fRad);
	float c = cosf(this->m_polygon2D.fRad);

	//テクスチャ使用使用時
	
	float fU, fV; //uv計算用

	fU = (this->m_polygon2D.currentAnimPat % this->m_polygon2D.nDivU) * (1.0f / this->m_polygon2D.nDivU);
	fV = (this->m_polygon2D.currentAnimPat / this->m_polygon2D.nDivU) * (1.0f / this->m_polygon2D.nDivV);

	//頂点情報更新
	for (int i = 0; i < 4; i++) {
		m_vtx[i].diffuse = D3DCOLOR_ARGB((unsigned char)this->m_polygon2D.A, this->m_polygon2D.R, this->m_polygon2D.G, this->m_polygon2D.B);
		m_vtx[i].rhw = 1.0f;

		float dx = ((i % 2) * this->m_polygon2D.width - this->m_polygon2D.center.x);
		float dy = ((i / 2) * this->m_polygon2D.height - this->m_polygon2D.center.y);

		m_vtx[i].pos.x = this->m_polygon2D.pos.x + this->m_polygon2D.scale.x * (dx * c - dy * s);
		m_vtx[i].pos.y = this->m_polygon2D.pos.y + this->m_polygon2D.scale.y * (dx * s + dy * c);
		m_vtx[i].pos.z = 0.0f;

		//アニメーションパターンを超える番号だった場合ゼロセット
		if (this->m_polygon2D.currentAnimPat >= this->m_polygon2D.MaxAnimPat || this->m_polygon2D.currentAnimPat < 0) {
			m_vtx[i].u = 0.0f;
			m_vtx[i].v = 0.0f;
		}
		else {
			m_vtx[i].u = fU + (i % 2) * (1.0f / this->m_polygon2D.nDivU);
			m_vtx[i].v = fV + (i / 2) * (1.0f / this->m_polygon2D.nDivV);
		}

	}
	
}


void C_POLYGON_2D::UpdateVtx(VERTEX_2D * vtx){

	//頂点情報設定
	for (int i = 0; i < 4; i++) {
		m_vtx[i] = *(vtx + i);
	}
}

/*
描画処理
*/
void C_POLYGON_2D::Draw(){
	g_pDevice = GetDevice();

	g_pDevice->SetFVF(FVF_VERTEX_2D);
	if(m_polygon2D.isUseTex)
		g_pDevice->SetTexture(0, m_pTex);
	else 
		g_pDevice->SetTexture(0, NULL);

	g_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, m_vtx, sizeof(VERTEX_2D));
}