#include "Enemy.h"
#include "Player.h"
#include "DxLib.h"
#include "main.h"
#include <cmath>
#include <random>

bool Enemy::CircleCollsionE(Vector2 ene, Vector2 play) {

	Vector2 enemy = ene;

	enemy.x += 50 * cos(angle * PI * 2);
	enemy.y += 50 * sin(angle * PI * 2);

	int a = (play.x - enemy.x) * (play.x - enemy.x);
	int b = (play.y - enemy.y) * (play.y - enemy.y);

	int c = (26 + search) * (26 + search);

	DrawCircle(enemy.x, enemy.y, radias + search, color, false);

	//‚ ‚½‚è”»’è
	if (a + b < c)
	{
		return true;
	}

	return false;
}

float GetRandom(float min, float max)
{
	std::random_device rd;
	std::default_random_engine eng(rd());
	std::uniform_real_distribution<float> distr(min, max);
	return distr(eng);
}

Enemy::Enemy() {
	//Initialize();
}

void Enemy::Initialize() {
	playerPos = { 0,0 };
	maxSpd = 0.1f;
	spd = 0.04f;
	angle = GetRandom(0.0f, 1.0f);
	attackCount = 0;
}

void Enemy::Draw() {
	DrawCircle(pos.x, pos.y, radias, 0x00ff00, true);
}

void Enemy::Update(Vector2 player) {

	if (attackFlag) {
		color = 0xaaaa00;
		spd = 0.02;

		angle -= spd / (float)dis * 2 * PI;
		if (angle >= 1) angle -= 1;

		Attack();
	}
	else {
		color = 0x00aaaa;

		angle -= spd / (float)dis * 2 * PI;
		if (angle >= 1) angle -= 1;

		pos.x = WIN_WIDTH / 2.0f + cos(angle * PI * 2) * dis;
		pos.y = WIN_HEIGHT / 2.0f + sin(angle * PI * 2) * dis;

		attackCount++;

		if (attackCount > 1000) {
			SetAttack(player);
		}
	}
}

void Enemy::SetPos(Vector2 Pos)
{
	pos = Pos;
}

void Enemy::SetIsDied(bool isdied)
{
	isDied = isdied;
}

void Enemy::OnCollsion()
{
	isDied = true;
}

void Enemy::SetAttack(Vector2 player) {
	if (attackFlag != true) {
		if (CircleCollsionE(pos, player)) {
			attackFlag = true;
			playerPos = player;
		}
	}
}

void Enemy::Attack() {

	dis += 0.5f;
	if (dis > 300 || dis < -300)
	{
		isDied = true;
	}

	pos.x = WIN_WIDTH / 2.0f + cos(angle * PI * 2) * dis;
	pos.y = WIN_HEIGHT / 2.0f + sin(angle * PI * 2) * dis;
}