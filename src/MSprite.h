#pragma once
#include <ecs/Component.h>
#include <string>
#include <memory>
#include <vector>

#include "Vec2.h";

struct Tigr;

struct MSprite: public Component{
	Tigr* image= nullptr;
protected:
	std::string texture_file;
	Vec2 sourceCoords;
public:
	MSprite();
	MSprite(const std::string& fileName, Vec2 sourceCoords = Vec2());
	~MSprite();

	MSprite(const MSprite& other);
	MSprite(MSprite&& other);
	MSprite& operator=(const MSprite& other);
	MSprite& operator=(MSprite&& other);

	void Draw(Tigr* window, const Vec2& pos) const;
	void ChangeTexture(const std::string& fileName);

	static bool Load(std::string& fileName, MSprite& obj);
	static bool Save(std::string& fileName, const MSprite& obj);
};

