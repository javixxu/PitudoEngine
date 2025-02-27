#pragma once
#include <string>
#include <vector>

#include "Vec2.h"
struct Tigr;

class Sprite {
	Tigr* image = NULL;
protected:
	//Serial
	Vec2 position;
	std::string texture_file;
public:
	Sprite();
	Sprite(const std::string& fileName);
	//Sprite(Vec2 _pos, Texture _tex);
	~Sprite();

	void ChangeTexture();

	void setPosition(Vec2 pos);
	Vec2 getPosition() const;
	void Draw(Tigr* window) const;

	static bool Load(std::string& fileName, Sprite& obj);
	static bool Save(std::string& fileName, const Sprite& obj);

};