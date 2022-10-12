#pragma once
#include "Input.h"
#include "Vector2.h"

class Player
{
private:
	Vector2 pos;
	float dis;	//	�v���C���[�ƒ��S�̋���
	float angle;
	float spd;
	float maxSpd;
	bool hAttack;	//	���U���t���O

	//	�_���[�W
	bool damage;

	//	�X�^��

	//	KnockBack
	bool knockBack;
	int kbTime;
	Vector2 backSpd;	//	x:spd,y:dis
public:
	Player();
	void Init();
	void Update(Input& input);
	void Draw();
	void KnockBack(Vector2& e_spd);
	float Damage();
};

