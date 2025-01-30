#pragma once
#include <string>
#include <sstream>

struct Tigr;
class Vec2;

namespace PitudoEngine {

	class Engine{
	private:
		Tigr* m_screen;

		bool m_bIsRunning = false;

		float m_deltaTime;
		float fps = 60; //FPS: MOTOR

		void Input();
		void Update();
		void Render();

		float Wait(float ms);
		void RenderDebug();

	public:
		bool Init();
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

		void printText(const std::string& text,Vec2 pos);

		static void logme(const std::string& text);
	};

}