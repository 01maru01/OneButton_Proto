#include "Player.h"
#include "DxLib.h"
#include "main.h"
#include <cmath>

static const float PI = 3.141592f;

Player::Player()
{
	Init();
}

void Player::Init()
{
	r = 10;
	isLive = true;
	hAttack = false;
	maxSpd = 0.1f;
	minSpd = 0.05f;
	angle = 0.0f;
	dis = 300.0f;

	knockBack = false;
	kbTime = 0;

	damage = false;

	stun = false;
	stunTime = 0;

	combo = 0;
}

void Player::Update(Input& input, Stage& stage)
{
	float minR = 100.0f;
	float maxR = 300.0f;

#pragma region SetKcockBackSpd
	if(input.GetTriggerKey(KEY_INPUT_Q)) {
		Vector2 e_spd(GetRand(10) - 5, GetRand(10) - 5);
		KnockBack(e_spd);
	}
	if(input.GetTriggerKey(KEY_INPUT_E)&&isLive) {
		Vector2 e_spd(GetRand(10) - 5, GetRand(10) - 5);
		KnockBack(e_spd);
		backSpd.x = 0.0f;
		backSpd.y = 100.0f;
	}
#pragma endregion

#pragma region �X�^��
	if (stun) {
		stunTime--;
		if (stunTime <= 0) stun = false;
	}
#pragma endregion

#pragma region ��������
	if (!knockBack && !stun) {
		spd.x += 0.01f;

		if (dis == maxR) {
			//	�ǂ���
			if (spd.x > minSpd) {
				spd.x -= 0.015f;
			}
			if (spd.x < minSpd) {
				spd.x = minSpd;
			}
		}
		else {
			if (spd.x > maxSpd) {
				spd.x = maxSpd;
			}
		}
	}
#pragma endregion

#pragma region KnockBack
	if (knockBack) {
		if (kbTime <= 0 && spd.x <= maxSpd) knockBack = false;
		if (kbTime > 0) kbTime--;

		if (kbTime <= 0) backSpd.y = 0.0f;
		dis += backSpd.y;

		if (dis >= maxR) {
			if (stage.OnCollision(angle, Damage())) {
				dis = maxR;
				combo = 0;
			}
			else {
				isLive = false;
				dis = maxR;
			}
			//	�_���[�W
			damage = true;
			knockBack = false;
			stun = true;
			stunTime = 10;
		}
		
		if (kbTime <= 0 && spd.x > maxSpd) {
			spd.x -= backSpd.x;
			if (spd.x > maxSpd) {
				spd.x = maxSpd;
			}
		}
		else {
			spd.x += backSpd.x;
		}
	}
#pragma endregion

	if (stage.Feaver()) {
#pragma region heavyAttack
		if (hAttack) {
			if (!hAttackHalf) {
				dis -= 20;
				if (dis < 0) {
					dis = abs(dis);
					angle += 0.5f;
					if (angle >= 1) angle -= 1;
					hAttackHalf = true;
				}
			}
			else {
				dis += 20;
				if (dis >= maxR) {
					dis = maxR;
					hAttack = false;
					combo = 0;

					//	�X�^������
					spd.x = 0;
					stun = true;
					stunTime = 10;
				}
			}
		}
#pragma endregion

#pragma region �L�[����
		if (isLive) {
			if (input.GetTriggerKey(KEY_INPUT_SPACE) && !hAttack) {
				hAttack = true;
				hAttackHalf = false;
			}
		}
#pragma endregion

#pragma region ���x����
		angle += spd.x / (float)maxR * 2 * PI;
#pragma endregion
	}
	else {
#pragma region heavyAttack
		if (hAttack) {
			dis += 20;
			if (dis >= maxR) {
				dis = maxR;
				hAttack = false;
				combo = 0;

				//	�X�^������
				spd.x = 0;
				stun = true;
				stunTime = 10;
			}
		}
#pragma endregion

#pragma region �L�[����
		if (isLive) {
			if (input.GetKey(KEY_INPUT_SPACE) && !stun) {
				spd.y += 0.2f;
				if (spd.y > 5.0f) spd.y = 5.0f;
				dis -= spd.y;
			}
			else {
				spd.y -= 0.5f;
				if (spd.y < -3.0f) spd.y = -3.0f;
				if (!hAttack) {
					if (dis < maxR) {
						//dis += 3.0f;
						dis -= spd.y;
					}
				}
			}
		}
		else {
			dis += 3.0f;
		}
#pragma endregion

#pragma region Dis�͈͐���
		if (dis >= maxR && isLive) {
			if (stage.OnCollision(angle, Damage())) {
				//	�͈͊O�ɍs�����Ƃ��ύX
				dis = maxR;
				combo = 0;
			}
			else {
				isLive = false;
				dis = maxR;
			}
		}

		if (dis <= minR) {
			dis = minR;
			stage.DamageCircle(1);
			hAttack = true;
		}
#pragma endregion

#pragma region ���x����
		angle += spd.x / (float)dis * 2 * PI;
#pragma endregion
	}

	if (angle >= 1) angle -= 1;
	
#pragma region ���W�X�V
	pos.x = WIN_WIDTH / 2.0f + cos(angle * PI * 2) * dis;
	pos.y = WIN_HEIGHT / 2.0f + sin(angle * PI * 2) * dis;
#pragma endregion
}

void Player::Draw()
{
	Vector2 center(WIN_WIDTH / 2.0f, WIN_HEIGHT / 2.0f);

#pragma region �i�s�����x�N�g��
	//Vector2 lineVec(cos(angle * PI * 2), sin(angle * PI * 2));
	//Vector2 vertVec(-lineVec.y, lineVec.x);
	//vertVec *= 100;
	//DrawLine(pos.x, pos.y, pos.x + vertVec.x, pos.y + vertVec.y, 0xFF0000);
#pragma endregion
	int color = 0xFFFFFF;
	if (knockBack) color = 0xFF0000;
	DrawFormatString(10, 10, color, "spd:%f dis:%f angle:%f combo:%d", spd.x, dis, angle, combo);

	Vector2 c_center(r * cos(angle * PI * 2), r * sin(angle * PI * 2));
	DrawLine(pos.x - c_center.x, pos.y - c_center.y, center.x, center.y, 0xFF0000);
	DrawCircle(pos.x - c_center.x, pos.y - c_center.y, r, color);
}

void Player::KnockBack(Vector2& e_spd)
{
	knockBack = true;

	Vector2 lineVec(cos(angle * PI * 2), sin(angle * PI * 2));
	Vector2 vertVec(-lineVec.y, lineVec.x);

	//	�傫������
	backSpd.x = vertVec.dot(e_spd) / 30.0f;
	backSpd.y = lineVec.dot(e_spd) * 50;

	if (backSpd.x < 0) {
		backSpd.x += spd.x;
		spd.x = 0.0f;
	}
	//	���x�ɉ����ăm�b�N�o�b�N�̎��Ԑݒ�
	kbTime = 20;

	backSpd /= kbTime;
}

bool Player::Damage()
{
	if (damage) {
		damage = false;
		return true;
	}
	return false;
}
