#pragma once
#include <ecs/System.h>
class Vec2;
struct Tigr;
namespace PitudoEngine {
	class RenderDebugSystem : public System
	{
		Tigr* m_Window;
	public:
		RenderDebugSystem();
		~RenderDebugSystem();

		void setContext(Tigr* screen);
		void Update(float deltaTime) override;
		void RenderDebug(float deltaTime);
	};
}
