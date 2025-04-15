#pragma once
#include <ecs/System.h>
#include <functional>
#include <tigr/tigr.h>

namespace PitudoEngine {

	struct TextRenderEntry {
		std::function<std::string()> getText;
		float x, y;
		TPixel color;
	};

	class RenderSystem : public System {
		Tigr* m_Window;

		std::vector<TextRenderEntry> m_TextCallbacks;
	public:
		RenderSystem();
		~RenderSystem();

		void setContext(Tigr* screen);

		void addTextCallback(std::function<std::string()> callback, float x, float y, TPixel color);

		void Update(float deltaTime) override;

	};
}
