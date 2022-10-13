#include "enemyManager.h"
#include <random>
#include "DxLib.h"

int GetRandom(int min, int max)
{
	std::random_device rd;
	std::default_random_engine eng(rd());
	std::uniform_int_distribution<> distr(min, max);
	return distr(eng);
}

EnemyManager::EnemyManager()
{

}

EnemyManager::~EnemyManager()
{
	for (int i = 0; i < enemys.size(); i++)
	{
		delete enemys[i];
	}
}

void EnemyManager::update()
{
	input.Update();

	for (int i = 0; i < enemys.size(); i++)
	{
		enemys[i]->Update();

		if (input.GetTriggerKey(KEY_INPUT_R))
		{
			enemys[i]->SetIsDied(true);
		}

		if (enemys[i]->GetIsDied())
		{
			enemys.erase(enemys.begin() + i);
		}
	}
}

void EnemyManager::draw()
{
	for (int i = 0; i < enemys.size(); i++)
	{
		enemys[i]->Draw();
	}
}

void EnemyManager::enemyPop(float WIN_WIDTH, float WIN_HEIGHT)
{
	//仮沖の中身を作る
	Enemy* newEnemy = new Enemy();

	//ここを変えるとランダムの中身が変わる
	int max = 200;
	int min = 100;

	Vector2 Pos = {};

	int a = GetRandom(-max, max);
	int b = GetRandom(-max, max);

	while (a < min && a > -min && b < min && b > -min)
	{
		a = GetRandom(-max, max);
		b = GetRandom(-max, max);
	}

	Pos.x = WIN_WIDTH / 2.0f + a + (b / static_cast<float>(10));

	Pos.y = WIN_HEIGHT / 2.0f + b + (a / static_cast <float>(10));

	//enemyのinitを呼ぶ
	newEnemy->Initialize();
	newEnemy->SetPos(Pos);

	if (a < 0) {
		a = -a;
	}

	if (b < 0) {
		b = -b;
	}

	if (a > b) {
		newEnemy->dis = 300 - a;
	}
	else {
		newEnemy->dis = 300 - b;
	}

	//格納
	enemys.push_back(newEnemy);
}

std::vector<Enemy*> EnemyManager::getenemy()
{
	return enemys;
}
