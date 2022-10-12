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
	hAttack = false;
	maxSpd = 0.1f;
	spd = 0.0f;
	angle = 0.0f;
	dis = 300.0f;
	pos.x = WIN_WIDTH / 2.0f + cos(angle * PI * 2) * dis;
	pos.y = WIN_HEIGHT / 2.0f + sin(angle * PI * 2) * dis;

	knockBack = false;
	kbTime = 0;

	damage = false;

	stun = false;
	stunTime = 0;
}

void Player::Update(Input& input)
{
	if(input.GetTriggerKey(KEY_INPUT_Q)) {
		Vector2 e_spd(GetRand(10) - 5, GetRand(10) - 5);
		KnockBack(e_spd);
	}
	if(input.GetTriggerKey(KEY_INPUT_E)) {
		Vector2 e_spd(GetRand(10) - 5, GetRand(10) - 5);
		KnockBack(e_spd);
		backSpd.x = 0.0f;
		backSpd.y = 100.0f;
	}

#pragma region スタン
	if (stun) {
		stunTime--;
		if (stunTime <= 0) stun = false;
	}
#pragma endregion


#pragma region 加速処理
	if (!knockBack && !stun) {
		spd += 0.01f;
		if (spd > maxSpd) {
			spd = maxSpd;
		}
	}
#pragma endregion

#pragma region KnockBack
	if (knockBack) {
		if (kbTime <= 0 && spd <= maxSpd) knockBack = false;
		if (kbTime > 0) kbTime--;

		if (kbTime <= 0) backSpd.y = 0.0f;
		dis += backSpd.y;

		float maxR = 300.0f;
		if (dis > maxR) {
			dis = maxR;
			//	ダメージ
			damage = true;
			knockBack = false;
			stun = true;
			stunTime = 10;
		}
		
		if (kbTime <= 0 && spd > maxSpd) {
			spd -= backSpd.x;
			if (spd > maxSpd) {
				spd = maxSpd;
			}
		}
		else {
			spd += backSpd.x;
		}
	}
#pragma endregion

#pragma region 速度処理
	angle += spd / (float)dis * 2 * PI;
	if (angle >= 1) angle -= 1;
#pragma endregion

#pragma region heavyAttack
	if (hAttack) {
		dis += 20;
		if (dis >= 300) {
			dis = 300;
			hAttack = false;

			//	スタン処理
			spd = 0;
			stun = true;
			stunTime = 10;
		}
	}
#pragma endregion

#pragma region キー入力
	if (input.GetKey(KEY_INPUT_SPACE) && !stun) {
		float minR = 100.0f;

		if (dis > minR) {
			dis -= 3.0f;
		}
	}
	else {
		if (!hAttack) {
			float maxR = 300.0f;
			if (dis < maxR) {
				dis += 3.0f;
			}
			if (dis > maxR) {
				dis = maxR;
			}
		}
	}
	float minR = 100.0f;
	if (dis <= minR) {
		dis = minR;
		hAttack = true;
	}
#pragma endregion

#pragma region 座標更新
	pos.x = WIN_WIDTH / 2.0f + cos(angle * PI * 2) * dis;
	pos.y = WIN_HEIGHT / 2.0f + sin(angle * PI * 2) * dis;
#pragma endregion
}

void Player::Draw()
{
	Vector2 center(WIN_WIDTH / 2.0f, WIN_HEIGHT / 2.0f);

#pragma region 進行方向ベクトル
	//Vector2 lineVec(cos(angle * PI * 2), sin(angle * PI * 2));
	//Vector2 vertVec(-lineVec.y, lineVec.x);
	//vertVec *= 100;
	//DrawLine(pos.x, pos.y, pos.x + vertVec.x, pos.y + vertVec.y, 0xFF0000);
#pragma endregion
	int color = 0xFFFFFF;
	if (knockBack) color = 0xFF0000;
	//DrawFormatString(10, 10, color, "angle:%f", angle);

	DrawLine(pos.x, pos.y, center.x, center.y, 0xFF0000);
	DrawCircle(pos.x, pos.y, 10, color);
}

void Player::KnockBack(Vector2& e_spd)
{
	knockBack = true;

	Vector2 lineVec(cos(angle * PI * 2), sin(angle * PI * 2));
	Vector2 vertVec(-lineVec.y, lineVec.x);
	float knockBackSpd = vertVec.dot(e_spd);
	backSpd.x = knockBackSpd / 30.0f;
	backSpd.y = lineVec.dot(e_spd) * 50;	//	大きさ注意
	if (backSpd.x < 0) {
		backSpd.x += spd;
		spd = 0.0f;
	}
	//	速度に応じてノックバックの時間設定
	kbTime = 20;

	backSpd /= kbTime;
}

float Player::Damage()
{
	if (damage) {
		damage = false;
		return angle;
	}
	return NULL;
}
