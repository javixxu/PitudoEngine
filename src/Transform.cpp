#include "Transform.h"
namespace PitudoEngine {
	Transform::Transform(const Vec2& pos, const Vec2& sc, float rot) :
		position(pos), scale(sc), rotation(rot) {
	}
}