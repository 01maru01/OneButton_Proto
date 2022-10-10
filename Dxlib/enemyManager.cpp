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
	//‰¼‰«‚Ì’†g‚ğì‚é
	Enemy* newEnemy = new Enemy();

	//enemy‚Ìinit‚ğŒÄ‚Ô
	newEnemy->Initialize();

	//Ši”[
	enemys.push_back(newEnemy);

}

std::vector<Enemy*> enemyManager::getenemy()
{
	return enemys;
}
