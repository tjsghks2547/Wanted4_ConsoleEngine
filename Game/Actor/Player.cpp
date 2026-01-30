#include "Player.h"
#include "Core/Input.h"
#include "Engine/Engine.h"
#include "Actor/Box.h"
#include "Level/Level.h"



#include <iostream>
#include <Windows.h>

using namespace Wanted;

Player::Player()
	:super('P', Vector2(5,5),Color::Red)
{
	sortingOrder = 10; 
}

void Player::BeginPlay()
{
	// 상위 함수 호출.
	// C++는 부모함수 가리키는 포인터가 없음.
	Actor::BeginPlay();

	//std::cout << "Player::BeginPlay().\n";
}

void Player::Tick(float deltaTime)
{
	super::Tick(deltaTime);

	// Q키 종료.
	if (Wanted::Input::Get().GetKeyDown('Q'))
	{
		// Todo: 게임 엔진 종료 요청.
		Wanted::Engine::Get().QuitEngine();
	}

	// 이동

	if (Input::Get().GetKey('W') && GetPosition().y > 0)
	{
		Vector2 newPosition = GetPosition();
		newPosition.y -= 1;
		SetPosition(newPosition);
	}

	if (Input::Get().GetKey('S') && GetPosition().y < 15)
	{
		Vector2 newPosition = GetPosition();
		newPosition.y += 1;
		SetPosition(newPosition);
	}



	if (Input::Get().GetKey('D') && GetPosition().x < 20)
	{
		Vector2 newPosition = GetPosition();
		newPosition.x += 1; 
		SetPosition(newPosition);
	}



	if (Input::Get().GetKey('A') && GetPosition().x > 0)
	{
		Vector2 newPosition = GetPosition();
		newPosition.x -= 1;
		SetPosition(newPosition);
	}


	// 스페이스로 박스 생성.
	if (Input::Get().GetKeyDown(VK_SPACE))
	{
		if(owner)
		{
			owner->AddNewActor(new Box(GetPosition()));	
		}
		// 박스 생성. 
		
	}



	//std::cout 
	//	<< "Player::Tick(). deltaTime: " << deltaTime
	//	<< ", FPS: " << (1.0f / deltaTime) << "\n";
}

void Player::Draw()
{
	Actor::Draw();


}
