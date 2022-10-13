#pragma once
#include "Vector2.h"
#include "Input.h"

static const float PI = 3.141592f;

class Enemy {
private: 

	Vector2 pos;
	bool isDied = false;
	float angle;
	float spd;
	float maxSpd;

public:
	Enemy();
	void Initialize();
	void Draw();
	void Update();
	void SetPos(Vector2 Pos);
	void SetIsDied(bool isdied);
	Vector2 GetPos() { return pos; };

	bool GetIsDied() { return isDied; };

	void OnCollsion();

	float dis = 16;	//	プレイヤーと中心の距離
}; 