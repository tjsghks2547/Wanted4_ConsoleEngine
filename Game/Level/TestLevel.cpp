#include "TestLevel.h"
#include "Actor/Player.h"

TestLevel::TestLevel()
{
	// Player 액터를 레벨에 추가.
	AddNewActor(new Player());
}
