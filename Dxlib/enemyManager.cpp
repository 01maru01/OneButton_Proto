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
	//‰¼‰«‚Ì’†g‚ğì‚é
	Enemy* newEnemy = new Enemy();

	int max = 210;
	int min = 100;

	Vector2 Pos = {};

	int a = GetRandom(-max, max);
	int b = GetRandom(-max, max);

	while (a < min && a > -min && b < min && b > -min)
	{
		a = GetRandom(-max, max);
		b = GetRandom(-max, max);
	}

	Pos.x = WIN_WIDTH / 2.0f + a + (b / 10);

	Pos.y = WIN_HEIGHT / 2.0f + b + (a / 10);

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
