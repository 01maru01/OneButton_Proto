#pragma once
#include <vector>
#include "Vector2.h"

typedef struct Line
{
	Vector2 pos1;
	Vector2 pos2;
	int life;
	bool isActive;
	bool flashing;
	bool shake;
	int shakeTime;
	int activeTime;

	void Init(Vector2& _pos1, Vector2& _pos2);
}Line;

typedef struct SmallCircle {
	int life = 10;
	bool isActive = true;
	int feaverTimer = 300;
	void Init();
};

class Stage
{
private:
	int x;
	int y;
	float maxR;
	float minR;
	int clearNum;
	std::vector<Line> line;

	SmallCircle circle;

	int idx = 0;
public:
	Stage();
	void Update();
	void Draw();
	bool OnCollision(float angle, bool damage, int combo = 0);
	bool Feaver() { return !circle.isActive; }
	void EndFeaver(bool hAttack);
	void DamageCircle(int damage) { circle.life -= damage; }

	void SetDeadAngle(float& angle);
	float GetMaxR() { return maxR; }
	float GetMinR() { return minR; }
};

