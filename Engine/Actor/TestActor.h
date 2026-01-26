#pragma once
#include "Actor.h"



class TestActor : public Wanted::Actor
{



//public:
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float deltatime) override; 
	virtual void Draw() override;


};

