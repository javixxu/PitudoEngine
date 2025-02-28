#pragma once
#include <ecs/Component.h>
#include <string>
#include <vector>

#include "Vec2.h";

struct Tigr;

struct MSprite: public Component{
	Tigr* image = NULL;
protected:
	std::string texture_file;
	Vec2 sourceCoords;
public:
	MSprite();
	MSprite(const std::string& fileName, Vec2 sourceCoords = Vec2());
	~MSprite();

	MSprite(const MSprite& other) = default;
	MSprite(MSprite&& other) = default;
	MSprite& operator=(const MSprite& other) = default;
	MSprite& operator=(MSprite&& other) = default;

	void Draw(Tigr* window, const Vec2& pos) const;
	void ChangeTexture(const std::string& fileName);

	static bool Load(std::string& fileName, MSprite& obj);
	static bool Save(std::string& fileName, const MSprite& obj);
};

