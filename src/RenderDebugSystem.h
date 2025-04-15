#pragma once
#include <ecs/System.h>
#include <functional>
#include <vector>
#include <tigr/tigr.h>

class Vec2;
namespace PitudoEngine {
	struct TextRenderEntry;

	class RenderDebugSystem : public System
	{
		Tigr* m_Window;
		std::vector<TextRenderEntry> m_TextCallbacks;
	public:
		RenderDebugSystem();
		~RenderDebugSystem();

		void setContext(Tigr* screen);
		void Update(float deltaTime) override;
		void RenderDebug(float deltaTime);
		void addTextCallback(std::function<std::string()> callback, float x, float y, TPixel color);
	};
}
