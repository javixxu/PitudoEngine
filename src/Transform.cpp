#include "Transform.h"

Transform::Transform(const Vec2& pos, const Vec2& sc, float rot) :
	position(pos), scale(sc), rotation(rot) {
}

void Transform::SetParent(Transform* newParent){
    if (parent)
        parent->RemoveChild(this);

    parent = newParent;
    if (parent)
        parent->children.push_back(this);
}

void Transform::RemoveChild(Transform* child){
    children.erase(std::remove(children.begin(), children.end(), child), children.end());
}
