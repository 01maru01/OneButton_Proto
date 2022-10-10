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
}

void Player::Update(Input& input)
{
	spd += 0.001f;
	if (spd > maxSpd) {
		spd = maxSpd;
	}

#pragma region KnockBack
	Vector2 lineVec(cos(angle * PI * 2), sin(angle * PI * 2));
	Vector2 vertVec(-lineVec.y, lineVec.x);
	Vector2 backSpd;
	//if (input.GetTriggerKey(KEY_INPUT_Q)) {
	//	backSpd.x = GetRand(10) - 5;
	//	backSpd.y = GetRand(10) - 5;
	//	float knockBackSpd = vertVec.dot(backSpd);
	//	spd -= knockBackSpd;
	//	knockBack = true;
	//}

	angle += spd / (float)dis * 2 * PI;
	if (angle >= 1) angle -= 1;

	float knockBackDis = lineVec.dot(backSpd);
	dis += knockBackDis;
#pragma endregion

#pragma region heavyAttack
	if (hAttack) {
		dis += 20;
		if (dis >= 300) {
			dis = 300;
			hAttack = false;
		}
	}
#pragma endregion

#pragma region キー入力
	if (input.GetKey(KEY_INPUT_SPACE)) {
		float minR = 100.0f;
		if (!hAttack) {
			if (dis > minR) {
				dis -= 3.0f;
			}
			if (dis <= minR) {
				dis = minR;
				hAttack = true;
			}
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

	DrawFormatString(10, 10, 0xFFFFFF, "spd:%f", spd);

	DrawLine(pos.x, pos.y, center.x, center.y, 0xFF0000);
	DrawCircle(pos.x, pos.y, 10, 0xFF0000);
}
