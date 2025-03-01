#pragma once
#include <ecs/ecsDefinitions.h>
#include <string>
#include <vector>

#include "Vec2.h";

struct Tigr;

class Sprite: public Component{
	Tigr* image= nullptr;
protected:
	std::string texture_file;
	Vec2 sourceCoords;
public:
	Sprite();
	Sprite(const std::string& fileName, Vec2 sourceCoords = Vec2());
	~Sprite();

	Sprite(const Sprite& other);
	Sprite(Sprite&& other);
	Sprite& operator=(const Sprite& other);
	Sprite& operator=(Sprite&& other);

	void Draw(Tigr* window, const Vec2& pos) const;
	void ChangeTexture(const std::string& fileName);

	static bool Load(std::string& fileName, Sprite& obj);
	static bool Save(std::string& fileName, const Sprite& obj);
};

