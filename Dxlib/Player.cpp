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
	spd = 0.1f;
	angle = 0.0f;
	dis = 300;
	x = WIN_WIDTH / 2.0f + cos(angle * PI * 2) * dis;
	y = WIN_HEIGHT / 2.0f + sin(angle * PI * 2) * dis;
}

void Player::Update(Input& input)
{
	angle += spd / (float)dis * 2 * PI;
	if (angle >= 1) angle -= 1;

	if (input.GetKey(KEY_INPUT_SPACE)) {
		int minR = 100;
		if (!hAttack) {
			if (dis > minR) {
				dis -= 3;
			}
			if (dis <= minR) {
				dis = minR;
				hAttack = true;
			}
		}
	}
	else {
		if (!hAttack) {
			int maxR = 300;
			if (dis < maxR) {
				dis += 3;
			}
			if (dis > maxR) {
				dis = maxR;
			}
		}
	}

	if (hAttack) {
		dis += 20;
		if (dis >= 300) {
			dis = 300;
			hAttack = false;
		}
	}

	x = WIN_WIDTH / 2.0f + cos(angle * PI * 2) * dis;
	y = WIN_HEIGHT / 2.0f + sin(angle * PI * 2) * dis;
}

void Player::Draw()
{
	int centerX = WIN_WIDTH / 2.0f;
	int centerY = WIN_HEIGHT / 2.0f;
	DrawLine(x, y, centerX, centerY, 0xFF0000);
	DrawCircle(x, y, 10, 0xFF0000);
}
