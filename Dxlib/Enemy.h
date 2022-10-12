#pragma once
#include "Vector2.h"
#include "Input.h"


class Enemy {
private: 
	Vector2 pos;
	int dis;	//	プレイヤーと中心の距離
public:
	Enemy();
	void Initialize();
	void Draw();
	void Update(Input& input);
}; 