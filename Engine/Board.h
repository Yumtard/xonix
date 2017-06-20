#pragma once

#include "Graphics.h"

class Board
{
public:
	Board();
	void Draw(Graphics& gfx) const;
	int GetTileSize() const;
	void Drop(int y, int x);
	void Collapse();
	bool GameOver(int y, int x);

private:
	static constexpr int tileSize = 20;
	static constexpr int width = 40;
	static constexpr int height = 30;
public:
	int grid[height][width] = { 0 };
};