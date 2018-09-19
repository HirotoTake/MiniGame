#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "polygon.h"
#include "character.h"



//基底クラス:C_CHARACTER, C_PLAYER_STATUS 
//概要:プレイヤークラス
class C_PLAYER :public C_CHARACTER{
private:
	
public:
	//更新用メンバ変数
	D3DXVECTOR3 m_move;	//座標更新用移動量
	D3DXVECTOR3 m_accel; //座標更新用加速度
	CHARACTER_STATUS m_status;	//ステータス更新用

	//プレイヤーステータスセット
	void Init() override;

	void Update() override;

};


#endif // !_PLAYER_H_