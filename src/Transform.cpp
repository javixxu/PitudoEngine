#include "Transform.h"
namespace PitudoEngine {
	Transform::Transform(const Vec2& pos, const Vec2& sc, float rot) :
		position(pos), scale(sc), rotation(rot) {
	}

	void Transform::ReadData(const std::unordered_map<std::string, std::string>& values, Entity e) {
		
		position.x = std::stof(values.at("pos_x"));
		position.y = std::stof(values.at("pos_y"));
		scale.x = std::stof(values.at("scale_x"));
		scale.y = std::stof(values.at("scale_y"));
		rotation = std::stof(values.at("rotation"));

		printf("Transform Read, %d\n", e);
	}
}