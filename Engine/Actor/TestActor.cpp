#include "TestActor.h"
#include <iostream>

void TestActor::BeginPlay()
{
	// 상위 함수 호출
	// C++는 부모함수 가리키는 포인터가 없음.
	Actor::BeginPlay(); 

	std::cout << "Test Actor::BeginPlay().\n";
}

void TestActor::Tick(float deltatime)
{
	Actor::Tick(deltatime);

	std::cout << "TestActor::Tick().deltatime :" << deltatime
		<< ", FPS " << (1.0f / deltatime) << "\n";

}

void TestActor::Draw()
{
}
