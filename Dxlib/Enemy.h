#pragma once
#include "Vector2.h"
#include "Input.h"


class Enemy {
private: 

	Vector2 pos;
	int dis = 16;	//	プレイヤーと中心の距離
	bool isDied = false;

public:
	Enemy();
	void Initialize();
	void Draw();
	void Update(Input& input);
	void SetPos(Vector2 Poa);
	void SetIsDied(bool isdied);
	Vector2 GetPos() { return pos; };

	bool GetIsDied() { return isDied; };

	void OnCollsion();

}; 