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
}Line;

class Stage
{
private:
	int x;
	int y;
	int maxR;
	int minR;
	std::vector<Line> line;

	int idx = 0;
public:
	Stage();
	void Init();
	void Update(float angle);
	void Draw();
};

