#pragma once
#include "Vector2.h"
#include "Input.h"


class Enemy {
private: 
	Vector2 pos;
	int dis;	//	�v���C���[�ƒ��S�̋���
public:
	Enemy();
	void Initialize();
	void Draw();
	void Update(Input& input);
}; 