#pragma once

#include "Graphics.h"
#include "Board.h"

struct Enemy
{
	int y;
	int x;
	int vy;
	int vx;
	Enemy()
	{
		x = 300;
		y = 300;
		vx = 4;
		vy = 4;
	}
	void Move(Board::Type(&grid)[30][40], int tileSize);
	void Draw(Graphics& gfx, int size) const;
};