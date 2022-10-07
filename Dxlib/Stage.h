#pragma once

class Stage
{
private:
	int x;
	int y;
	int maxR;
	int minR;
public:
	Stage();
	void Init();
	void Update();
	void Draw();
};

