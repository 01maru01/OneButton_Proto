#pragma once
#include "Enemy.h"
#include <vector>

class enemyManager
{
public:
	enemyManager();
	~enemyManager();

	void update();

	void draw();

	/// <summary>
	/// 敵生成
	/// </summary>
	/// <param name="posX">x座標</param>
	/// <param name="posY">y座標</param>
	void enemyPop(float posX,float posY);

	//enemyをもらう関数
	std::vector<Enemy*> getenemy();

private:
	//enemyを持っているやつ
	std::vector<Enemy*> enemys;

};

