/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd )
{
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	if (game)
	{
		const float dt = ft.Mark(); // delta time
		const int tileSize = brd.GetTileSize();

		counter += dt;
		if (counter > delay)
		{
			counter = 0;
			player.Update();
			const int y = player.GetY();
			const int x = player.GetX();

			if (brd.grid[y][x] == brd.tail)
			{
				game = false;
			}

			if (brd.grid[y][x] == brd.empty)
			{
				brd.grid[y][x] = brd.tail;
			}
		}

		player.UserInput(wnd.kbd);
		
		enemy.Move(brd.grid, tileSize);

		if (brd.grid[player.GetY() ][player.GetX()] == brd.filled)
		{
			brd.Drop(enemy.y / tileSize, enemy.x / tileSize);
			brd.Collapse();
		}
		game = brd.GameOver(enemy.y, enemy.x);
	}	
}


void Game::ComposeFrame()
{
	const int tileSize = brd.GetTileSize();
	brd.Draw(gfx);
	enemy.Draw(gfx, tileSize);
	player.Draw(gfx, tileSize);
}
