#pragma once
#include <vector>

typedef struct Line
{
	float x1;
	float y1;
	float x2;
	float y2;
	int life;
	bool isActive;
	bool flashing;
	bool shake;
	int shakeTime;
	int activeTime;
}Line;

typedef struct SmallCircle {
	int life = 10;
	bool isActive = true;
	int feaverTimer = 300;
};

class Stage
{
private:
	int x;
	int y;
	int maxR;
	int minR;
	std::vector<Line> line;

	SmallCircle circle;

	int idx = 0;
public:
	Stage();
	void Update();
	void Draw();
	bool OnCollision(float angle, bool damage);
	bool Feaver() { return !circle.isActive; }
	void DamageCircle(int damage) { circle.life -= damage; }
};

