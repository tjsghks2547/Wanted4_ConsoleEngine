#pragma once

#include "Common/Common.h"

namespace Wanted
{
	class WANTED_API Actor  //__declspec(dllexport) 외부에서 접근가능하게 만드는 키워드
	{
	public:
		Actor();
		virtual ~Actor(); 


		// 게임 플레이 이벤트
		virtual void BeginPlay();
		virtual void Tick(float deltaTime);
		virtual void Draw();

		// Getter. 
		inline bool HasBeganPlay() const { return hasBeganPlay; }
		bool IsActive() const 
		{
			return isActive && !destoryRequested; 
		}

	protected:
		// 이미 BeginPlay 이벤트를 받았는지 여부 
		bool hasBeganPlay = false; 

		// 활성화 상태 여부 
		bool isActive = true; 

		// 현재 프레임에 삭제 요청 받았는지 여부.
		bool destoryRequested = false; 



	};



}


