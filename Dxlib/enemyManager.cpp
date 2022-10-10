#include "enemyManager.h"

enemyManager::enemyManager()
{

}

enemyManager::~enemyManager()
{

	for (int i = 0; i < enemys.size(); i++)
	{
		delete enemys[i];
	}

}

void enemyManager::update()
{
	for (int i = 0; i < enemys.size(); i++)
	{
		enemys[i]->Update();
	}
}

void enemyManager::draw()
{

	for (int i = 0; i < enemys.size(); i++)
	{
		enemys[i]->Draw();
	}

}

void enemyManager::enemyPop(float posX, float posY)
{
	//仮沖の中身を作る
	Enemy* newEnemy = new Enemy();

	//enemyのinitを呼ぶ
	newEnemy->Initialize();

	//格納
	enemys.push_back(newEnemy);

}

std::vector<Enemy*> enemyManager::getenemy()
{
	return enemys;
}
