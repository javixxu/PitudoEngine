#pragma once
#include <string>
#include <sstream>

struct Tigr;
class Vec2;
class Sprite;
class ECSManager;

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

namespace PitudoEngine {

	class Engine{
	private:
		Tigr* m_screen;
		ECSManager* ecsManager;

		bool m_bIsRunning = false;

		float m_deltaTime;
		float fps = 144; //FPS: MOTOR

		Sprite* sprite;

		void Update();
		//void Render();

		float Wait(float ms);
		//void RenderDebug();

	public:
		bool Init();
		void SetUp();
		void Run();
		bool Quit();
		bool getIsRunning() const;

		template <typename ... Args>
		static std::string sstr(Args&& ... args) {
			std::ostringstream sstr;
			sstr << std::dec;
			((sstr << args), ...);
			return sstr.str();
		}

		static void printText(Tigr* screen,const std::string& text,Vec2 pos);

		static void logme(const std::string& text);

		void CreateBorders();
	};

}