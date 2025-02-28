#pragma once
#include <ecs/System.h>
class Vec2;
struct Tigr;
namespace PitudoEngine {
	class RenderSystem : public System {
		Tigr* m_Window;
	public:
		RenderSystem();
		~RenderSystem();

		void setContext(Tigr* screen);

		void Update(float deltaTime) override;
		void RenderDebug(float deltaTime);
	};
}
