#include "Box.h"

Box::Box(const Vector2& newPoisiton)
	:super("B",newPoisiton, Color::Blue)
{
	//strcpy_s(image, sizeof(char), 'B');
	// 그리기 우선순위 설정.
	sortingOrder = 5; 
}

Box::~Box()
{

}
