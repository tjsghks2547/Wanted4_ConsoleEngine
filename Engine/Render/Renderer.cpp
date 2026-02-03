#include "Renderer.h"
#include "Util/Util.h"

namespace Wanted
{
	
	Renderer::Frame::Frame(int bufferCount)
	{
		// 배열 생성 및 초기화.
		charInfoArray = new CHAR_INFO[bufferCount];
		memset(charInfoArray, 0, sizeof(CHAR_INFO) * bufferCount);
		//ZeroMemory(charInfoArray, sizeof(CHAR_INFO) * bufferCount);

		sortingOrderArray = new int[bufferCount];
		memset(sortingOrderArray, 0, sizeof(int) * bufferCount);

	}

	Renderer::Frame::~Frame()
	{
		SafeDeleteArray(charInfoArray);
		SafeDeleteArray(sortingOrderArray);
	}

	void Renderer::Frame::Clear(const Vector2& screenSize)
	{
		// 2차원 배열로 다루는 1차원 배열을 순회하면서
		// 빈 문자(' ')를 설정.
		const int width  = screenSize.x;
		const int height = screenSize.y;

		for(int y=0; y < height; ++y)
		{
			for(int x=0; x<width; ++x)
			{
				// 배열 인덱스 구하기
				const int index = (y * width) + x;

				// 글자 값 및 속성 설정.
				CHAR_INFO& info = charInfoArray[index];
				info.Char.AsciiChar = ' ';
				info.Attributes = 0; 

				// 그리기 우선순위 초기화.
				sortingOrderArray[index] = -1; 
			}
		}


	}

	//------------------- Frame --------------- //


	Renderer::Renderer(const Vector2& screenSize)
	{

	}

	Renderer::~Renderer()
	{

	}

	void Renderer::Submit(const char* text, const Vector2& position, Color color, int sortingOrder)
	{

	}


	void Renderer::Present()
	{

	}

	ScreenBuffer* Renderer::GetCurrentBuffer()
	{

		return nullptr;
	}
}