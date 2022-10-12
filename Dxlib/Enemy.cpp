#include "Enemy.h"
#include "DxLib.h"
#include "main.h"
#include <random>

int GetRandom(int min, int max)
{
	std::random_device rd;
	std::default_random_engine eng(rd());
	std::uniform_int_distribution<> distr(min, max);
	return distr(eng);
}

Enemy::Enemy() {
	Initialize();
}

void Enemy::Initialize() {

	int max = 200;

	int a = GetRandom(-max, max);

	while (a < 60 && a > -60)
	{
		a = GetRandom(-max, max);
	}

	pos.x = WIN_WIDTH / 2.0f + a;

	a = GetRandom(-max, max);

	while (a < 60 && a >-60)
	{
		a = GetRandom(-max, max);
	}

	pos.y = WIN_HEIGHT / 2.0f + a;

	dis = 16;
}


void Enemy::Draw() {
	DrawCircle(pos.x, pos.y, dis, 0x00ff00, true);
}


void Enemy::Update(Input& input) {
	if (input.GetTriggerKey(KEY_INPUT_S)) {
		Initialize();
	}

}