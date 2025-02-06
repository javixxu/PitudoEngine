#include "Sprite.h"
#include <fstream>
#include <tigr/tigr.h>
#include <pugixml/pugixml.hpp>

#include "Vec2.h"

//Texture::Texture(int w, int h){
//}
//
//Texture::Texture(const std::string& fileName){
//}
//
//Texture::~Texture(){
//}
//
//void Texture::Draw(Tigr* window,Vec2 pos){
//	Tigr* temp = tigrBitmap(width, height);
//	if (temp) {
//		memccpy(temp->pix, pixels.data(),0,
//			width * height * channels);
//
//		int dx = 0, dy = 0;
//		int sx = 0, sy = 0;
//
//		tigrBlit(window, temp, dx, dy, sx, sy, width, height);
//
//		tigrFree(temp);
//	}
//}
//
//bool Texture::Save(std::string& fileName, const Texture& tex){
//	pugi::xml_document doc;
//	pugi::xml_node node = doc.child("texture");
//
//	node.attribute("width").set_value(tex.width);
//	node.attribute("height").set_value(tex.height);
//	node.attribute("channels").set_value(tex.channels);
//	node.attribute("pixels").set_value(tex.pixels.data());
//
//	try {
//		//TO DO::
//		std::stringstream ss;
//		doc.save(ss);
//		std::string out = ss.str();
//
//		return true;
//	}
//	catch (...) {
//		return false;
//	}
//}

Sprite::Sprite(): position(), texture_file("")
{
}

Sprite::Sprite(const std::string& fileName):Sprite(){
	texture_file = fileName;
}

Sprite::~Sprite(){
	tigrFree(image);
}

void Sprite::ChangeTexture(){
	if(image)tigrFree(image);
	image = tigrLoadImage(texture_file.c_str());
}

void Sprite::setPosition(Vec2 pos){
	position = pos;
}

Vec2 Sprite::getPosition() const{
	return position;
}

void Sprite::Draw(Tigr* window) const{
	int sx = 0, sy = 0;

	tigrBlit(window, image, position.x, position.y, sx, sy, image->w, image->h);
}

bool Sprite::Save(std::string& fileName, const Sprite& tex){
	pugi::xml_document doc;
	pugi::xml_node node = doc.append_child("Sprite");

	node.append_attribute("x").set_value(tex.position.x);
	node.append_attribute("y").set_value(tex.position.y);
	node.append_attribute("texture_file").set_value(tex.texture_file.c_str());

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

bool Sprite::Load(std::string& fileName, Sprite& obj){
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(fileName.c_str());

	if (!result) {
		return false; 
	}

	pugi::xml_node node = doc.child("Sprite");
	if (!node) {
		return false; 
	}

	obj.position.x= node.attribute("x").as_float();
	obj.position.y = node.attribute("y").as_float();
	obj.texture_file = node.attribute("texture_file").as_string();

	obj.ChangeTexture();
	
	return true;
}
