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
	/// “G¶¬
	/// </summary>
	/// <param name="posX">xÀ•W</param>
	/// <param name="posY">yÀ•W</param>
	void enemyPop(float posX,float posY);

	//enemy‚ğ‚à‚ç‚¤ŠÖ”
	std::vector<Enemy*> getenemy();

private:
	//enemy‚ğ‚Á‚Ä‚¢‚é‚â‚Â
	std::vector<Enemy*> enemys;

};

