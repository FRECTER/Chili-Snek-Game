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
#include "SpriteCodex.h"

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	board(gfx),
	rng(rd()),
	snake({ board.GetWidth() / 2,board.GetHeight() / 2 }),
	goal(rng, board, snake)
{}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel() {
	const float dt = ft.Mark();
	if (!gameStarted) {
		if (wnd.kbd.KeyIsPressed(VK_RETURN))
			gameStarted = true;
	}
	else {
		if (!gameEnded) {
			if (wnd.kbd.KeyIsPressed(VK_UP) && d_loc.x != 0 && !inhibitPress) {
				d_loc = { 0,-1 };
				inhibitPress = true;
			}
			if (wnd.kbd.KeyIsPressed(VK_DOWN) && d_loc.x != 0 && !inhibitPress) {
				d_loc = { 0,1 };
				inhibitPress = true;
			}
			if (wnd.kbd.KeyIsPressed(VK_LEFT) && d_loc.y != 0 && !inhibitPress) {
				d_loc = { -1,0 };
				inhibitPress = true;
			}
			if (wnd.kbd.KeyIsPressed(VK_RIGHT) && d_loc.y != 0 && !inhibitPress) {
				d_loc = { 1,0 };
				inhibitPress = true;
			}

			timeCount += dt;
			if (timeCount >= movePeriod) {
				timeCount -= movePeriod;
				inhibitPress = false;
				if (movePeriod > min_movePeriod)
					movePeriod = in_movePeriod - (float)snake.GetLength() * speedIncreaseFactor;
				Location next = snake.NextHeadLocation(d_loc);
				if (!board.Inside(next) || snake.InTileNOHEAD(next) || board.CheckObs(next))
					gameEnded = true;
				else {
					const bool eaten = next == goal.getLocation();
					if (eaten) {
						snake.Grow();
						eatenNum++;
						board.SpawnObs(rng, snake, goal);
					}
					snake.MoveBy(d_loc);
					if (eaten)
						goal.Respawn(rng, board, snake);
				}
			}
		}
	}
}

void Game::ComposeFrame() {
	if (!gameStarted)
		SpriteCodex::DrawTitle(300, 225, gfx);
	else {
		for (int i = 0; i < board.GetWidth() * board.GetDim(); i++) {
			gfx.PutPixel(i + (Graphics::ScreenWidth - board.GetWidth() * board.GetDim()) / 2, (Graphics::ScreenHeight - board.GetHeight() * board.GetDim()) / 2 - 3, Colors::White);
			gfx.PutPixel(i + (Graphics::ScreenWidth - board.GetWidth() * board.GetDim()) / 2, (Graphics::ScreenHeight - board.GetHeight() * board.GetDim()) / 2 - 2, Colors::White);
			gfx.PutPixel(i + (Graphics::ScreenWidth - board.GetWidth() * board.GetDim()) / 2, (Graphics::ScreenHeight + board.GetHeight() * board.GetDim()) / 2 + 1, Colors::White);
			gfx.PutPixel(i + (Graphics::ScreenWidth - board.GetWidth() * board.GetDim()) / 2, (Graphics::ScreenHeight + board.GetHeight() * board.GetDim()) / 2 + 2, Colors::White);
			gfx.PutPixel(i + (Graphics::ScreenWidth - board.GetWidth() * board.GetDim()) / 2, (Graphics::ScreenHeight - board.GetHeight() * board.GetDim()) / 2 - 8, Colors::White);
			gfx.PutPixel(i + (Graphics::ScreenWidth - board.GetWidth() * board.GetDim()) / 2, (Graphics::ScreenHeight - board.GetHeight() * board.GetDim()) / 2 - 7, Colors::White);
			gfx.PutPixel(i + (Graphics::ScreenWidth - board.GetWidth() * board.GetDim()) / 2, (Graphics::ScreenHeight + board.GetHeight() * board.GetDim()) / 2 + 6, Colors::White);
			gfx.PutPixel(i + (Graphics::ScreenWidth - board.GetWidth() * board.GetDim()) / 2, (Graphics::ScreenHeight + board.GetHeight() * board.GetDim()) / 2 + 7, Colors::White);
		}
		for (int j = 0; j < board.GetHeight() * board.GetDim(); j++) {
			gfx.PutPixel((Graphics::ScreenWidth - board.GetWidth() * board.GetDim()) / 2 - 3, j + (Graphics::ScreenHeight - board.GetHeight() * board.GetDim()) / 2, Colors::White);
			gfx.PutPixel((Graphics::ScreenWidth - board.GetWidth() * board.GetDim()) / 2 - 2, j + (Graphics::ScreenHeight - board.GetHeight() * board.GetDim()) / 2, Colors::White);
			gfx.PutPixel((Graphics::ScreenWidth + board.GetWidth() * board.GetDim()) / 2 + 1, j + (Graphics::ScreenHeight - board.GetHeight() * board.GetDim()) / 2, Colors::White);
			gfx.PutPixel((Graphics::ScreenWidth + board.GetWidth() * board.GetDim()) / 2 + 2, j + (Graphics::ScreenHeight - board.GetHeight() * board.GetDim()) / 2, Colors::White);
			gfx.PutPixel((Graphics::ScreenWidth - board.GetWidth() * board.GetDim()) / 2 - 8, j + (Graphics::ScreenHeight - board.GetHeight() * board.GetDim()) / 2, Colors::White);
			gfx.PutPixel((Graphics::ScreenWidth - board.GetWidth() * board.GetDim()) / 2 - 7, j + (Graphics::ScreenHeight - board.GetHeight() * board.GetDim()) / 2, Colors::White);
			gfx.PutPixel((Graphics::ScreenWidth + board.GetWidth() * board.GetDim()) / 2 + 6, j + (Graphics::ScreenHeight - board.GetHeight() * board.GetDim()) / 2, Colors::White);
			gfx.PutPixel((Graphics::ScreenWidth + board.GetWidth() * board.GetDim()) / 2 + 7, j + (Graphics::ScreenHeight - board.GetHeight() * board.GetDim()) / 2, Colors::White);
		}
		snake.Draw(board);
		goal.Draw(board);
		board.DrawObs();
		if (gameEnded)
			SpriteCodex::DrawGameOver(350, 250, gfx);
	}
}
