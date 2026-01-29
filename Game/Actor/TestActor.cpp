#include "TestActor.h"
#include "Core/Input.h"
#include "Engine/Engine.h"
#include <iostream>
#include <Windows.h>

using namespace Wanted;

TestActor::TestActor()
	:super('T', Vector2(2,3))
{

}

void TestActor::BeginPlay()
{
	// 상위 함수 호출.
	// C++는 부모함수 가리키는 포인터가 없음.
	Actor::BeginPlay();

	//std::cout << "TestActor::BeginPlay().\n";
}

void TestActor::Tick(float deltaTime)
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

	if (Input::Get().GetKey('S') && GetPosition().y < 20)
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





	//std::cout 
	//	<< "TestActor::Tick(). deltaTime: " << deltaTime
	//	<< ", FPS: " << (1.0f / deltaTime) << "\n";
}

void TestActor::Draw()
{
	Actor::Draw();
}
