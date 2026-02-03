#include <iostream>
#include "Engine/Engine.h"
#include "Game/Game.h"
#include "Level/SokobanLevel.h"


using namespace Wanted;


int main()
{


	// 창하나에 콘솔 아웃풋을 2개를 두고 하는것
	// CreateConsoleScreenBuffer()
	// SetConsoleActiveScreenBuffer()


	//Wanted::Engine engine;
	//engine.SetNewLevel(new SokobanLevel());
	//engine.Run();

	Game game;	 
	game.Run();	
																																											

	// 문자 배열을 한번에 콘솔로 넘겨서 그릴 때 사용하는 함수 
	//WriteConsoleOutputA();

	//std::cin.get(); 
}