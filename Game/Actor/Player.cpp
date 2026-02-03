#include "Player.h"
#include "Core/Input.h"
#include "Engine/Engine.h"

#include "Game/Game.h"

#include "Actor/Box.h"
#include "Level/Level.h"

#include "Interface/ICanPlayerMove.h"

#include <iostream>
#include <Windows.h>

using namespace Wanted;

Player::Player(const Vector2& position)
	:super("P",position, Color::Red)
{
	//strcpy_s(image, sizeof(char), 'P');

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

	// ESC키 처리.
	if (Wanted::Input::Get().GetKeyDown(VK_ESCAPE))
	{
		Game::Get().ToggleMenu();
		return;
	}

	// Q키 종료.
	if (Wanted::Input::Get().GetKeyDown('Q'))
	{
		// Todo: 게임 엔진 종료 요청.
		Wanted::Engine::Get().QuitEngine();
	}

	// 인터페이스 확인
	static ICanPlayerMove* canPlayerMoveInterface = nullptr; 

	// 오너십 확인 (null 확인)
	if( !canPlayerMoveInterface && GetOwner())
	{
		// 인터페이스로 형변환
		canPlayerMoveInterface = dynamic_cast<ICanPlayerMove*>(GetOwner());
	}


	// 이동

	if (Input::Get().GetKeyDown('W') && GetPosition().y > 0)
	{
		// 이동 가능 여부 판단.
		Vector2 newPosition(GetPosition().x, GetPosition().y-1);
		if(canPlayerMoveInterface->CanMove(GetPosition(),newPosition))
		{
			SetPosition(newPosition);
		}


		//Vector2 newPosition = GetPosition();
		//newPosition.y -= 1;
		//SetPosition(newPosition);
	}

	if (Input::Get().GetKeyDown('S') && GetPosition().y < 15)
	{
		Vector2 newPosition(GetPosition().x, GetPosition().y +1);
		if (canPlayerMoveInterface->CanMove(GetPosition(), newPosition))
		{
			SetPosition(newPosition);
		}


		//Vector2 newPosition = GetPosition();
		//newPosition.y += 1;
		//SetPosition(newPosition);
	}



	if (Input::Get().GetKeyDown('D') && GetPosition().x < 20)
	{
		Vector2 newPosition(GetPosition().x+1, GetPosition().y);
		if (canPlayerMoveInterface->CanMove(GetPosition(), newPosition))
		{
			SetPosition(newPosition);
		}

		//Vector2 newPosition = GetPosition();
		//newPosition.x += 1; 
		//SetPosition(newPosition);
	}



	if (Input::Get().GetKeyDown('A') && GetPosition().x > 0)
	{
		Vector2 newPosition(GetPosition().x-1, GetPosition().y);
		if (canPlayerMoveInterface->CanMove(GetPosition(), newPosition))
		{
			SetPosition(newPosition);
		}


		//Vector2 newPosition = GetPosition();
		//newPosition.x -= 1;
		//SetPosition(newPosition);
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
