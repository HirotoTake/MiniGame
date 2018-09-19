#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include "object.h"

#define MAX_NAME (20)

enum {
	CHARACTER_ID_PLAYER = 0,
	CHARACTER_ID_MAX,
};

typedef struct {
	unsigned char charaId;	//キャラ識別番号
	D3DXVECTOR3 worldPos;	//ワールド座標

	
	int nLife;	//体力
	bool bJump;	//ジャンプフラグ
	bool bUnder; //下段降り
	int nDirOld;
	int nDir;
}CHARACTER_STATUS;

//このクラスの継承元:C_POLYGON_2D, C_OBJECT
//概要:キャラクターの基本クラス
class C_CHARACTER  : public C_OBJECT{
private:
	CHARACTER_STATUS m_status;	//キャラ情報
public:
	void SetStatus(CHARACTER_STATUS *status) { this->m_status = *status; }

	CHARACTER_STATUS GetStatus() { return this->m_status; }
};


#endif // !_PLAYER_H_