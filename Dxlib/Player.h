#pragma once
#include "Input.h"

class Player
{
private:
	float x;
	float y;
	int dis;	//	プレイヤーと中心の距離
	float angle;
	float spd;
	bool hAttack;	//	強攻撃フラグ
public:
	Player();
	void Init();
	void Update(Input& input);
	void Draw();
};

