#pragma once

#include "Math/Vector2.h"
#include "Math/color.h"

using namespace Wanted; 


// 헬퍼(Helper) 기능 제공.
namespace Util
{
	inline void SetConsolePosition(const Vector2& position)
	{
		// 콘솔 커서 위치 이동(설정)하는 함수
		//COORD coord = {};
		//coord.X = static_cast<short>(position.x);
		//coord.Y = static_cast<short>(position.y);

		SetConsoleCursorPosition(
			GetStdHandle(STD_OUTPUT_HANDLE),
			static_cast<COORD>(position));

	}


	// 콘솔 텍스트 설정 함수 
	inline void SetConsoleTextColor(Color color)
	{
		SetConsoleTextAttribute(
			GetStdHandle(STD_OUTPUT_HANDLE),
			static_cast<unsigned short>(color)
		);
	}


	// 커서 끄기. 
	inline void TurnOffCursor()
	{

		CONSOLE_CURSOR_INFO info = {};

		GetConsoleCursorInfo(
			GetStdHandle(STD_OUTPUT_HANDLE),
			&info
		);

		info.bVisible = false;
		SetConsoleCursorInfo(
			GetStdHandle(STD_OUTPUT_HANDLE),
			&info
		);

	}



	// 커서 켜기.
	inline void TurnOnCursor()
	{
		
		CONSOLE_CURSOR_INFO info = {};

		GetConsoleCursorInfo(
			GetStdHandle(STD_OUTPUT_HANDLE),
			&info
		);

		info.bVisible = true;
		SetConsoleCursorInfo(
			GetStdHandle(STD_OUTPUT_HANDLE),
			&info
		);
	}


}


// 클래스가 아닌 일반함수 구현을 헤더에 선언과 구현을 같이하면 링커 오류가 발생 ( 같은 함수가 include 된 곳에 생성되기 때문에)
// 만약 cpp로 구현하면 분류되서 오류가 나지 않음 
// 또다른 방법은 inline 방식 혹은 static 방식을 활용한다.