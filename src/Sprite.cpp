#include "Sprite.h"
#include <cassert>
#include <fstream>
#include <tigr/tigr.h>
#include <pugixml/pugixml.hpp>
#include <iostream>

#include "Vec2.h"

Sprite::Sprite():image(nullptr), sourceCoords(){
}

Sprite::Sprite(const std::string& fileName, Vec2 sourceCoords):image(nullptr), sourceCoords(){
	ChangeTexture(fileName);
}

Sprite::~Sprite(){
	if(image)
		tigrFree(image);
	std::cout << "DESTRUCTORTA MSPRITE COMPONENT \n";
}

Sprite::Sprite(const Sprite& other)
{
	*this = other;
}

Sprite::Sprite(Sprite&& other)
{
	*this = std::move(other);
}

Sprite& Sprite::operator=(const Sprite& other)
{
	this->sourceCoords = other.sourceCoords;
	this->ChangeTexture(other.texture_file);

	return *this;
}

Sprite& Sprite::operator=(Sprite&& other)
{
	this->image = other.image;
	other.image = nullptr;

	this->texture_file = other.texture_file;
	this->sourceCoords = other.sourceCoords;

	return *this;
}

void Sprite::Draw(Tigr* window,const Vec2& pos) const{
	assert(image && "MSprite::Draw - Texture is nullptr!");
	tigrBlit(window, image, pos.x, pos.y, sourceCoords.x, sourceCoords.y, image->w, image->h);
}

void Sprite::ChangeTexture(const std::string& fileName){
	texture_file = fileName;
	if(image)
		tigrFree(image);

	image = tigrLoadImage(texture_file.c_str());
}

bool Sprite::Load(std::string& fileName, Sprite& obj)
{
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(fileName.c_str());

	if (!result) {
		return false;
	}

	pugi::xml_node node = doc.child("Sprite");
	if (!node) {
		return false;
	}

	obj.sourceCoords.x = node.attribute("source_x").as_float();
	obj.sourceCoords.y = node.attribute("source_y").as_float();

	obj.ChangeTexture(node.attribute("texture_file").as_string());

	return true;
}

bool Sprite::Save(std::string& fileName, const Sprite& obj)
{
	pugi::xml_document doc;
	pugi::xml_node node = doc.append_child("Sprite");

	node.append_attribute("source_x").set_value(obj.sourceCoords.x);
	node.append_attribute("source_y").set_value(obj.sourceCoords.y);
	node.append_attribute("texture_file").set_value(obj.texture_file.c_str());

	try {
		std::ofstream file(fileName);
		if (!file.is_open()) {
			return false;
		}

		doc.save(file);
		file.close();

		return true;
	}
	catch (...) {
		return false;
	}
}
