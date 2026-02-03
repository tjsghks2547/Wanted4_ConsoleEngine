#include "Ground.h"

Ground::Ground(const Vector2& position)
	:super(" ",position)
{
	//strcpy_s(image, sizeof(char), ' ');

	// 그리기 우선순위 설정 
	sortingOrder = 0;




}
