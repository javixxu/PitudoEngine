#pragma once
#include <ecs/System.h>
namespace PitudoEngine {
	class ColliderSystem :public System
	{
	public:
		ColliderSystem();
		~ColliderSystem();

		void Update(float deltaTime) override;
	};
}
