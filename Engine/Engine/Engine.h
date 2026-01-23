#pragma once

namespace Wanted
{
	// Main Game Engine class.
	class Engine
	{
		// 데이터.
		// 
		struct KeyState
		{
			// 현재 키가 눌렀는지. 
			bool isKeyDown = false; 

			// 이전에 키가 눌렀는지
			bool wasKeyDown = false; 

			
		};

	public:
		Engine();
		~Engine(); 

		// 엔진 루프(게임 루프). 
		void Run(); 

		// 엔진 종료 함수 
		void QuitEngine(); 

		// 입력 확인 함수.
		bool GetKeyDown(int keyCode);  // 이전에 입력이 안되었는데, 현재 입력이 됐으면,
		bool GetKeyUp(int keyCode); // 이전에 입력이 됐는데, 현재 입력이 취소 됐으면,
		bool GetKey(int keyCode); // 현재 눌려있으면 반복 호출. 

	private:
		// 입력 처리 함수
		void ProcessInput(); 

		// 업데이트 함수 
		void Tick(float deltaTime); 

		// 그리기 함수 ( Draw/Render ) 
		void Draw(); 



	private:
		// 엔진 종료 플래그 
		bool isQuit = false; 

		// 키 상태 저장용 배열. 
		KeyState keyStates[255] = { }; 

	};
}




