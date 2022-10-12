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
	int activeTime;
}Line;

typedef struct SmallCircle {
	int life = 50;
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
};

