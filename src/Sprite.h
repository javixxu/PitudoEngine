#pragma once
#include <ecs/ecsDefinitions.h>
#include <string>
#include <vector>
#include "Vec2.h"

struct Tigr;

class Sprite: public Component{
	Tigr* image= nullptr;
protected:
	std::string texture_file;
	Vec2 m_pivot;
public:
	Sprite();
	Sprite(const std::string& fileName, Vec2 pivot = Vec2(0.5f));
	~Sprite();

	Sprite(const Sprite& other) noexcept;
	Sprite(Sprite&& other) noexcept;
	Sprite& operator=(const Sprite& other) noexcept;
	Sprite& operator=(Sprite&& other) noexcept;

	void Draw(Tigr* window, const Vec2& pos, const Vec2& scale) const;
	void ChangeTexture(const std::string& fileName);

	static bool Load(std::string& fileName, Sprite& obj);
	static bool Save(std::string& fileName, const Sprite& obj);
};

