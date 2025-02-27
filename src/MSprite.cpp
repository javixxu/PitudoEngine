#include "MSprite.h"
#include <cassert>
#include <fstream>
#include <tigr/tigr.h>
#include <pugixml/pugixml.hpp>

#include "Vec2.h"
#include <iostream>

MSprite::MSprite():image(nullptr), sourceCoords(){
}

MSprite::MSprite(const std::string& fileName, Vec2 sourceCoords):image(nullptr), sourceCoords(){
	ChangeTexture(fileName);
}

MSprite::~MSprite(){
	//if(image)
		//tigrFree(image);
	std::cout << "DESTRUCTORTA MSPRITE COMPONENT \n";
}

void MSprite::Draw(Tigr* window,const Vec2& pos) const{
	assert(image && "MSprite::Draw - Texture is nullptr!");
	tigrBlit(window, image, pos.x, pos.y, sourceCoords.x, sourceCoords.y, image->w, image->h);
}

void MSprite::ChangeTexture(const std::string& fileName){
	texture_file = fileName;
	if(image)tigrFree(image);
	image = tigrLoadImage(texture_file.c_str());
}

bool MSprite::Load(std::string& fileName, MSprite& obj)
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

bool MSprite::Save(std::string& fileName, const MSprite& obj)
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

