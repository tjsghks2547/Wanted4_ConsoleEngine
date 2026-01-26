#include "Level.h"
#include "Actor/Actor.h"

namespace Wanted
{
	Level::Level()
	{

	}

	Level::~Level()
	{
		// 메모리 정리
		for(Actor*& actor : actors)
		{
			// 액터 객체 메모리 해제
			if(actor)
			{
				delete actor;
				actor = nullptr; 
			}
		}

		// 배열 초기화
		actors.clear();
	}


	void Level::BeginPlay()
	{
		// 액터에 이벤트 흘리기
		for(Actor* actor : actors)
		{
			if(actor->HasBeganPlay())
			{
				continue;
			}
			
			actor->BeginPlay();
		}

	}

	void Level::Tick(float deltaTime)
	{
		// 액터에 이벤트 흘리기
		for (Actor* actor : actors)
		{
			actor->Tick(deltaTime);
		}
	}


	void Level::Draw()
	{
		// 액터에 이벤트 흘리기
		for (Actor* actor : actors)
		{
			actor->Draw();
		}
	}

	void Level::AddNewActor(Actor* newActor)
	{
		//Todo : 나중에 프레임 처리 고려해서 따로 추가 작업 해야함.

		//actors.push_back(newActor); // l-value reference 최근에는 업데이트되서 r-value reference도 사용되기도 하지만 가끔 오래된 버전이 사용되서 문제
		actors.emplace_back(newActor); // r-value reference

	}
}