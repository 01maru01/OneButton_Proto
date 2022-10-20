#pragma once
#include "Enemy.h"
#include "Dxlib.h"
#include <vector>
#include "Input.h"
#include <cmath>
#include "Particle.h"

class EnemyManager
{
public:
	EnemyManager();
	~EnemyManager();

	void update(Vector2 player);

	void draw();

	/// <summary>
	/// 敵生成
	/// </summary>
	/// <param name="WIN_WIDTH">画面サイズ横</param>
	/// <param name="WIN_HEIGHT">画面サイズ縦</param>
	void enemyPop(float WIN_WIDTH, float WIN_HEIGHT);

	//enemyをもらう関数
	std::vector<Enemy*> getenemy();

	std::vector<Particle*> getparticle;
private:
	//enemyを持っているやつ
	std::vector<Enemy*> enemys;

	//particleを持っているやつ
	std::vector<Particle*> particle;

	Input input;
	int enemyGraph = LoadGraph("Resources/playerTest.png");
};

