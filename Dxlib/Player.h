#pragma once
#include "Input.h"
#include "Vector2.h"
#include "Stage.h"

class Player
{
private:
	bool isLive;
	Vector2 pos;
	float dis;	//	�v���C���[�ƒ��S�̋���
	float angle;
	float spd;
	float maxSpd;
	float minSpd;
	bool hAttack;	//	���U���t���O
	bool hAttackHalf;	//	feaver�p

	//	�_���[�W
	bool damage;

	//	�X�^��
	bool stun;
	int stunTime;

	//	KnockBack
	bool knockBack;
	int kbTime;
	Vector2 backSpd;	//	x:spd,y:dis

	//	combo
	int combo;
public:
	Player();
	void Init();
	void Update(Input& input, Stage& stage);
	void Draw();
	void KnockBack(Vector2& e_spd);
	bool Damage();
	Vector2 GetPos() { return pos; };
};

