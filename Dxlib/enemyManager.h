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
	/// �G����
	/// </summary>
	/// <param name="posX">x���W</param>
	/// <param name="posY">y���W</param>
	void enemyPop(float posX,float posY);

	//enemy�����炤�֐�
	std::vector<Enemy*> getenemy();

private:
	//enemy�������Ă�����
	std::vector<Enemy*> enemys;

};

