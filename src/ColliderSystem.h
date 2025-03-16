#pragma once
#include <ecs/System.h>
#include <unordered_map>
namespace PitudoEngine {
	class ColliderSystem :public System
	{
		std::unordered_map<std::string, std::string> m_ignoreLayers;
	public:
		ColliderSystem();
		~ColliderSystem();

		void Update(float deltaTime) override;
		void AddIgnoreLayers(std::string layer1, std::string layer2);
	};
}
