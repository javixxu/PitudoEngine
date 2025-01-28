#pragma once
#include <string>
#include <sstream>

//bucle principal a 30hz (30FPS)


struct Tigr;
namespace PitudoEngine {
	class Engine{
	private:
		bool m_bIsRunning = false;
		Tigr* m_screen;

		void Input();
		void Update();
		void Render();

		float m_deltaTime;
		float fps = 30;
		float Wait(float ms);

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

		void printText(const std::string& text);

		static void logme(const std::string& text);
	};

}