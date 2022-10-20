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
	/// �G����
	/// </summary>
	/// <param name="WIN_WIDTH">��ʃT�C�Y��</param>
	/// <param name="WIN_HEIGHT">��ʃT�C�Y�c</param>
	void enemyPop(float WIN_WIDTH, float WIN_HEIGHT);

	//enemy�����炤�֐�
	std::vector<Enemy*> getenemy();

	std::vector<Particle*> getparticle;
private:
	//enemy�������Ă�����
	std::vector<Enemy*> enemys;

	//particle�������Ă�����
	std::vector<Particle*> particle;

	Input input;
	int enemyGraph = LoadGraph("Resources/playerTest.png");
};

