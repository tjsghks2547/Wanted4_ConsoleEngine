#include "Game.h"
#include "Level/SokobanLevel.h"
#include "Level/MenuLevel.h"
#include <iostream>


// 정적 변수 초기화
Game* Game::instance = nullptr;


Game::Game()
{
	instance = this;

	// 두 레벨 생성 및 배열에 추가.
	Levels.emplace_back(new SokobanLevel());
	Levels.emplace_back(new MenuLevel());

	// 시작 상태(레벨) 설정. 
	state = State::GamePlay; 

	// 게임 시작 시 활성화할 레벨 설정
	mainLevel = Levels[0];	



}

Game::~Game()
{
	// 중복 제거 방지 
	mainLevel = nullptr; 

	// 모든 레벨 삭제.
	for(Level*& level : Levels)
	{
		delete level;
		level = nullptr; 
	}

	// 배열 정리
	Levels.clear();

}

void Game::ToggleMenu()
{
	// 화면 지우기
	// system은 콘솔 명령어 실행 함수. "cls" 명렁어 실행 
	// cls -> clear screen 
	system("cls");
	
	// 변경할 인덱스 계산. 
	// 현재 활성 레벨 인덱스가 1이면 -> 0으로. 
	// 현재 활성 레벨 인덱스가 0이면 -> 1로. 
	// 마법의 공식 - (1-x) -> OneMinus
	int stateIndex = (int)state; // static_cast 
	int nextState  = 1 - stateIndex; // one -x. 

	state = (State)nextState;

	//메인 레벨 변경 
	mainLevel = Levels[static_cast<int>(state)];


}


Game& Game::Get()
{
	// 예외 처리
	if(!instance)
	{
		std::cerr << "Game::Get() - instance is null\n";
		__debugbreak();
	}

	// 정적 변수 반환.
	return *instance;
}
