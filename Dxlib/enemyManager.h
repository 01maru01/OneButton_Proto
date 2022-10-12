#pragma once
#include "Enemy.h"
#include <vector>
#include "Input.h"


class EnemyManager
{
public:
	EnemyManager();
	~EnemyManager();

	void update();

	void draw();

	/// <summary>
	/// 敵生成
	/// </summary>
	/// <param name="WIN_WIDTH">画面サイズ横</param>
	/// <param name="WIN_HEIGHT">画面サイズ縦</param>
	void enemyPop(float WIN_WIDTH,float WIN_HEIGHT);

	//enemyをもらう関数
	std::vector<Enemy*> getenemy();

private:
	//enemyを持っているやつ
	std::vector<Enemy*> enemys;

	Input input;

	

};

