#pragma once
#include <string>

class Tigr;
namespace PitudoEngine {
	class Engine{
	private:
		bool m_bIsRunning = false;
		Tigr* screen;

		void Input();
		void Update();
		void Render();

	public:
		bool Init();
		void Run();
		bool Quit();
		inline bool getIsRunning() const{ return m_bIsRunning; };

		static void logme(const std::string& text);
		static void logme(const char* text);
	};
}