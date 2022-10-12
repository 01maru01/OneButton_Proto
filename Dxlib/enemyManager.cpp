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
		if (enemys[i]->GetIsDied())
		{
			enemys.erase(enemys.begin() + i);
		}

		//enemys[i]->Update(input);
		if (input.GetTriggerKey(KEY_INPUT_R))
		{
			enemys[i]->SetIsDied(true);
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

	int max = 200;

	Vector2 Pos = {};

	int a = GetRandom(-max, max);

	while (a < 60 && a > -60)
	{
		a = GetRandom(-max, max);
	}

	Pos.x = WIN_WIDTH / 2.0f + a;

	a = GetRandom(-max, max);

	while (a < 60 && a >-60)
	{
		a = GetRandom(-max, max);
	}

	Pos.y = WIN_HEIGHT / 2.0f + a;

	//enemyのinitを呼ぶ
	newEnemy->Initialize();
	newEnemy->SetPos(Pos);

	//格納
	enemys.push_back(newEnemy);

}

std::vector<Enemy*> EnemyManager::getenemy()
{
	return enemys;
}
