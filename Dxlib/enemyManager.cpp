#include "enemyManager.h"
#include <random>
#include "DxLib.h"

bool CircleCollsionEnemy(Vector2 enemy1, Vector2 enemy2) {

	int a = (enemy1.x - enemy2.x) * (enemy1.x - enemy2.x);
	int b = (enemy1.y - enemy2.y) * (enemy1.y - enemy2.y);

	int c = 32 * 32;

	//DrawCircle(enemy1.x, enemy1.y, 16, 0xaa0000, false);
	//DrawCircle(enemy2.x, enemy2.y, 16, 0x00aa00, false);

	//Ç†ÇΩÇËîªíË
	if (a + b < c)
	{
		return true;
	}

	return false;
}

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

void EnemyManager::update(Vector2 player)
{
	input.Update();

	for (int i = 0; i < enemys.size(); i++)
	{
		enemys[i]->Update(player);

		//if (input.GetTriggerKey(KEY_INPUT_R))
		//{
		//	for (int j = 0; j < 10; j++)
		//	{
		//		//âºâ´ÇÃíÜêgÇçÏÇÈ
		//		Particle* newparticle = new Particle(enemys[i]->GetPos());
		//		//äiî[
		//		particle.push_back(newparticle);
		//	}

		//	enemys[i]->SetIsDied(true);
		//}
	}

	for (int i = 0; i < enemys.size(); i++)
	{
		if (enemys[i]->GetIsDied())
		{
			for (int j = 0; j < 10; j++)
			{
				//âºâ´ÇÃíÜêgÇçÏÇÈ
				Particle* newparticle = new Particle(enemys[i]->GetPos());
				//äiî[
				particle.push_back(newparticle);
			}

			enemys.erase(enemys.begin() + i);
		}
	}

	for (int i = 0; i < particle.size(); i++)
	{
		particle[i]->Update();

		if (particle[i]->GetIsDied())
		{
			particle.erase(particle.begin() + i);
		}
	}
}

void EnemyManager::draw()
{
	for (int i = 0; i < particle.size(); i++)
	{
		particle[i]->Draw();
	}

	for (int i = 0; i < enemys.size(); i++)
	{
		enemys[i]->Draw();
	}
}

void EnemyManager::enemyPop(float WIN_WIDTH, float WIN_HEIGHT)
{
	//âºâ´ÇÃíÜêgÇçÏÇÈ
	Enemy* newEnemy = new Enemy();

	int max = 200;
	int min = 100;

	Vector2 Pos = {};

	int a = GetRandom(-max, max);
	int b = GetRandom(-max, max);

	int count = 0;
	do
	{
		count++;

		a = GetRandom(-max, max);
		b = GetRandom(-max, max);

		Pos.x = WIN_WIDTH / 2.0f + a + (b / static_cast<float>(10));

		Pos.y = WIN_HEIGHT / 2.0f + b + (a / static_cast <float>(10));

		for (int i = 0; i < enemys.size(); i++)
		{
			if (CircleCollsionEnemy(enemys[i]->GetPos(), Pos) == true) {
				a = min - 1;
				b = min - 1;
			}
		}

		if (count > 10)
			break;

	} while (a < min && a > -min && b < min && b > -min);

	Pos.x = WIN_WIDTH / 2.0f + a + (b / static_cast<float>(10));

	Pos.y = WIN_HEIGHT / 2.0f + b + (a / static_cast <float>(10));

	//enemyÇÃinitÇåƒÇ‘
	newEnemy->Initialize(enemyGraph);
	newEnemy->SetPos(Pos);

	if (a < 0) {
		a = -a;
	}

	if (b < 0) {
		b = -b;
	}

	if (a > b) {
		newEnemy->dis = 400 - a;
	}
	else {
		newEnemy->dis = 400 - b;
	}

	//äiî[
	enemys.push_back(newEnemy);
}

std::vector<Enemy*> EnemyManager::getenemy()
{
	return enemys;
}
