#include "Enemy.h"
#include "Player.h"
#include "DxLib.h"
#include "main.h"
#include <cmath>
#include <random>

bool Enemy::CircleCollsionE(Vector2 ene, Vector2 play) {

	Vector2 enemy = ene;

	//enemy.x += 50 * cos(angle * PI * 2);
	//enemy.y += 50 * sin(angle * PI * 2);

	int a = (play.x - enemy.x) * (play.x - enemy.x);
	int b = (play.y - enemy.y) * (play.y - enemy.y);

	int c = 32 * 32;

	//DrawCircle(enemy.x, enemy.y, radias + search, color, false);

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

void Enemy::Initialize(int graph) {
	playerPos = { 0,0 };
	maxSpd = 0.1f;
	spd = 0.04f;
	angle = angle += spd / (float)dis * 2 * PI;
	//angle = GetRandom(0.0f, 1.0f);
	attackCount = 0;

	pos.x = WIN_WIDTH / 2.0f + cos(angle * PI * 2) * dis;
	pos.y = WIN_HEIGHT / 2.0f + sin(angle * PI * 2) * dis;

	enemyGraph = graph;
}

void Enemy::Draw() {
	//DrawCircle(pos.x, pos.y, radias, color, true);

	//int x = pos.x - radias;
	//int y = pos.y - radias;
	DrawGraph(pos.x - radias, pos.y - radias, enemyGraph, false);
}

void Enemy::Update(Vector2 player) {

	if (attackFlag) {
		//color = 0xaaaa00;
		spd = 0.02;
		attackCount = 765;
		/*angle += spd / (float)dis * 2 * PI;
		if (angle >= 1) angle -= 1;*/

		/*dis += 1.0f;*/

		//Attack();
	}
	else {
		//color = 0x00aaaa;

		/*angle += spd / (float)dis * 2 * PI;
		if (angle >= 1) angle -= 1;*/

		/*pos.x = WIN_WIDTH / 2.0f + cos(angle * PI * 2) * dis;
		pos.y = WIN_HEIGHT / 2.0f + sin(angle * PI * 2) * dis;*/

		attackCount++;

		if (attackCount > 764) {
			SetAttack();
			//color = 0xaaaa00;
		}
	}
	color = GetColor(attackCount / 3, 150, attackCount / 3);
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

void Enemy::SetAttack() {
	if (attackFlag != true) {
		attackFlag = true;
		//playerPos = player;
	}
}

void Enemy::Attack() {

	/*dis += 0.5f;
	if (dis > 300 || dis < -300)
	{
		isDied = true;
	}

	pos.x = WIN_WIDTH / 2.0f + cos(angle * PI * 2) * dis;
	pos.y = WIN_HEIGHT / 2.0f + sin(angle * PI * 2) * dis;*/
}

Vector2 Enemy::GetSpd(Vector2 player) {
	Vector2 speed;
	Vector2 speedReturn;

	speed = pos - player;
	speed.normalize();

	speedReturn.x = 5.0f;
	speedReturn.y = 5.0f;

	/*speedR.x = 5.0f * cos(angle * PI * 2);
	speedR.y = 5.0f * sin(angle * PI * 2);*/

	speedReturn.x *= -speed.x;
	speedReturn.y *= -speed.y;

	speedReturn.normalize();

	/*if (pos.y < WIN_HEIGHT / 2) {
		speedReturn.y = -speedReturn.y;
	}*/

	return speedReturn;
}