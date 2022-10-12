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
	/// �G����
	/// </summary>
	/// <param name="WIN_WIDTH">��ʃT�C�Y��</param>
	/// <param name="WIN_HEIGHT">��ʃT�C�Y�c</param>
	void enemyPop(float WIN_WIDTH,float WIN_HEIGHT);

	//enemy�����炤�֐�
	std::vector<Enemy*> getenemy();

private:
	//enemy�������Ă�����
	std::vector<Enemy*> enemys;

	Input input;

	

};

