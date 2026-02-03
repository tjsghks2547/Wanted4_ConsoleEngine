#include "SokobanLevel.h"
#include "Actor/Player.h"
#include "Actor/Wall.h"
#include "Actor/Ground.h"
#include "Actor/Box.h"
#include "Actor/Target.h"
#include "Util/Util.h"
#include <iostream>


/*
 # : 벽 (Wall) 
 . : 바닥 (Ground)
 p : 플레이어 (Player)
 b : 박스(Box)
 t : 타겟(Target)

 */

// 메뉴 추가 
// 1. 같은 레벨어서 특정 액터를 모아두어 관리하는 방법
// 2. 메뉴 레벨을 별도로 두는 방법

// 2번으로 구현할시
// engine에서 게임 레벨과 메뉴 레벨을 관리 해야함.
// 게임과 밀접함 
// Engine을 확장할 수 있게.
// 현재 활성화 레벨을 상황(상태-state)에 따라 관리



SokobanLevel::SokobanLevel()
{
	// Player 액터를 레벨에 추가.
	//AddNewActor(new Player());
	//LoadMap("Map.txt");
	LoadMap("Stage1.txt");
}

void SokobanLevel::Draw()
{
	super::Draw();

	// 게임 클리어인 경우. 메시지 출력.
	if(isGameClear)
	{
		// 콘솔 위치/색상 설정.
		Util::SetConsolePosition(Vector2(30, 0));
		Util::SetConsoleTextColor(Color::White);

		// 게임 클리어 메세지 출력.
		std::cout << "Game Clear!";
	}

}

void SokobanLevel::LoadMap(const char* filename)
{
	// 파일로드 
	// 최종 파일 경로 만들기 ("../Assets/filename")

	char path[2048] = {}; 
	sprintf_s(path, 2048, "../Assets/%s", filename);

	// 파일 열기.
	FILE* file = nullptr; 
	fopen_s(&file, path, "rt"); // 열기 실패하면 file에 nullptr가 들어감


	// 예외 처리 
	if(!file)
	{
		// 표준 오류 콘솔 활용
		std::cerr << "Failed to opent map file";
		
		// 디버스 모드에서 중단점으로 중단해주는 기능
		__debugbreak();
	}
	
	// 맵 읽기 
	
	// 맵 크기 파악 : File Position 포인터를 파일의 끝으로 이동 
	fseek(file, 0, SEEK_END);

	// 이 위치 읽기. 
	size_t fileSize = ftell(file);

	// File Position 처음으로 되돌리기.
	rewind(file);

	// 파일에서 데이터를 읽어올 버퍼 생성.
	char* data = new char[fileSize + 1]; // null 문자 때문에 +1


	// 데이터 읽기. 
	size_t readSize = fread(data, sizeof(char), fileSize, file);


	// Test: 읽어온 데이터 임시로 출력.  
	//std::cout << data; 

	
	// 읽어온 문자열을 분석(파싱-parcing)해서 출력.
	// 인덱스를 사용해 한문자씩 읽기. 

	int index = 0;
	
	// 객체를 생성할 위치 값
	Wanted::Vector2 position; 



	while(true)
	{
		// 종료조건
		if(index >= fileSize)
		{
			break; 
		}

		// 캐릭터 읽기
		char mapCharacter = data[index];
		++index;

		// 개행 문자 처리
		if(mapCharacter == '\n')
		{
			//std::cout << "\n"
			// y좌표는 하나 늘리고 , x 좌표 초기화
			++position.y;
			position.x = 0; 
			continue;
		}

		/*
		 # : 벽 (Wall)
		 . : 바닥 (Ground)
		 p : 플레이어 (Player)
		 b : 박스(Box)
		 t : 타겟(Target)

		 */

		// 한 문자씩 처리
		switch (mapCharacter)
		{
		case '#':
		case '1':
			//std::cout << "#";
			AddNewActor(new Wall(position));
			break;

		case '.':
			//std::cout << " ";
			AddNewActor(new Ground(position));
			break;

		case 'p':
			//std::cout << "P";
			//플레이어도 이동가능함.
			//플레이어도 옮겨졌을 때 그 밑에 땅이 있어야함.

			AddNewActor(new Player(position));
			AddNewActor(new Ground(position));
			break;

		case 'b':
			//std::cout << "B";
			// 박스는 이동 가능함. 
			// 박스가 옮겨졌을 때 그 밑에 땅이 있어야함.
			AddNewActor(new Box(position));
			AddNewActor(new Ground(position));
			break;

		case 't':
			//std::cout << "T";
			AddNewActor(new Target(position));
			//AddNewActor(new Ground(position));
			targetScore++;	
			break;

		default:
			break;
		}

		// x 좌표 증가 처리
		++position.x;
	}


	// 사용한 버퍼 해제.
	delete[] data;


	// 파일이 정상적으로 열렸으면 닫기. 
	fclose(file);


}

bool SokobanLevel::CanMove(
	const Wanted::Vector2& playerPosition, 
	const Wanted::Vector2& nextPosition)
{
	// 레벨에 있는 박스 액터 모으기
	// 박스는 플레이어가 밀기 등 추가적으로 처리해야하기 때문.
	std::vector<Actor*> boxes; 
	
	
	// 레벨에 배치된 전체 액터를 순회하면서 박스 찾기.
	for(Actor* const actor : actors)
	{
		// 액터가 박스 타입인지 확인, 
		if (actor->isTypeOf<Box>())	
		{
			boxes.emplace_back(actor);	
			continue;
		}
	}


	// 이동하려는 위치에 박스가 있는지 확인. 
	Actor* boxActor = nullptr; 
	for (Actor* const box : boxes)
	{
		// 위치 비교.
		if (box->GetPosition() == nextPosition)
		{
			boxActor = box; 
			break;
		}	
	}

	// 경우의 수 처리. 
	// 이동하려는 곳에 박스가 있는 경우. 
	if(boxActor)
	{
		//#1: 박스를 이동시키려는 위치에 다른 박스가 또 있는지 확인 .
		// 두 위치 사이에서 이동 방향 구하기 ( 벡터의 뺄셈 활용)
		//이동 로직에서 두 벡터를 더한다는 것은
		//둘 중 하나는 위치(Location)이고 다른 하나는 벡터(Vector)
		
		Vector2 direction = nextPosition - playerPosition; 
		Vector2 newPosition = boxActor->GetPosition() + direction;


		// 검색.
		for(Actor* const otherBox : boxes)
		{
			// 앞에 검색한 박스와 같다면 건너뛰기
			if(otherBox == boxActor)
			{
				continue;
			}

			// 다른 박스가 있는지 확인.
			if(otherBox->GetPosition() == newPosition)
			{
				// 두 개의 박스가 겹쳐진 방향으로는 이동 못함
				return false; 
			}
		}


		// 검색. 
		for (Actor* const actor : actors)
		{
			 
			if (actor->GetPosition() == newPosition)
			{
				// #2 : 벽이면 이동 불가.
				if(actor->isTypeOf<Wall>())
				{
					return false; 
				}

				// #3 : 그라운드 또는 타겟이면 이동 가능
				if(actor->isTypeOf<Ground>()
					|| actor->isTypeOf<Target>())
				{
					// 박스 이동 처리
					boxActor->SetPosition(newPosition);

					// Todo: 게임 점수 확인. 
					isGameClear = CheckGameClear();
					

					// 플레이어 이동 가능
					return true;
				}
			}


		}
	}
	
	// 이동하려는 곳에 박스가 없는 경우.
	// -> 이동하려는 곳에 있는 액터가 벽이 아니면 이동 가능.
	for(Actor* const actor : actors)
	{
		if(actor->GetPosition() == nextPosition)
		{
			// 이 액터가 벽인지 확인
			if(actor->isTypeOf<Wall>())
			{
				return false; 

			}

			// 그라운드 또는 타겟 
			return true; 

		}
	}


	return false;

}

bool SokobanLevel::CheckGameClear()
{
	// 타겟 위에 있는 박스의 수 검증. 
	int currentScore = 0;

	// 벡터에 박스 및 타겟 저장.
	std::vector<Actor*> boxes;
	std::vector<Actor*> targets;

	// 레벨에 배치된 배열 순회하면서 두 액터 필터링.
	for (Actor* const actor : actors)
	{
		// 박스인 경우 박스 배열에 추가
		if(actor-> isTypeOf<Box>())
		{
			boxes.emplace_back(actor);
			continue; 
		}

		// 타겟의 경우 타겟 배열에 추가.
		if (actor->isTypeOf<Target>())
		{
			targets.emplace_back(actor);
		}
		
	}

	// 점수 확인 (박스의 위치가 타겟의 위치와 같은지 비교)
	for (Actor* const box : boxes)
	{
		for(Actor* const target : targets)
		{
			// 두 액터의 위치가 같은면 점수 +.
			if(box->GetPosition() == target->GetPosition())
			{
				currentScore += 1;
			}
	
		}
	}


	// 목표 점수에 도달했는지 확인.
	return currentScore == targetScore;	
}
