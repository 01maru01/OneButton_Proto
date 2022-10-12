#include "enemyManager.h"

#include <random>

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
	for (int i = 0; i < enemys.size(); i++)
	{
		//enemys[i]->Update(input);
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
	//‰¼‰«‚Ì’†g‚ğì‚é
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

	//enemy‚Ìinit‚ğŒÄ‚Ô
	newEnemy->Initialize();
	newEnemy->SetPos(Pos);

	//Ši”[
	enemys.push_back(newEnemy);

}

std::vector<Enemy*> EnemyManager::getenemy()
{
	return enemys;
}
