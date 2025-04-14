#include "Sprite.h"
#include <cassert>
#include <fstream>

#include <tigr/tigr.h>
#include <iostream>
#include <ecs/ECSManager.h>

namespace PitudoEngine {
	Sprite::Sprite() :m_image(nullptr), m_transform(nullptr), m_pivot() {
	}

	Sprite::Sprite(const Transform* transform, const std::string& fileName, Vec2 pivot) :
		m_image(nullptr), m_pivot(pivot), m_transform(transform) {
		ChangeTexture(fileName);
	}

	Sprite::~Sprite() {
		if (m_image)
			tigrFree(m_image);
	}

	void Sprite::ReadData(const std::unordered_map<std::string, std::string>& values, Entity e){

		auto itFile = values.find("texture");
		if (itFile != values.end()) {
			ChangeTexture(itFile->second);
		}

		m_pivot.x = std::stof(values.at("pivot_x"));
		m_pivot.y = std::stof(values.at("pivot_y"));
	

		auto transform = &ECSManager::getInstance().GetComponent<Transform>(e);
		assert(transform && "Transform Not Found Reading Data.");

		m_transform = transform;

		printf("Sprite Read, %d\n", e);
	}

	Sprite::Sprite(const Sprite& other) noexcept {
		*this = other;
	}

	Sprite::Sprite(Sprite&& other) noexcept {
		*this = std::move(other);
	}

	Sprite& Sprite::operator=(const Sprite& other) noexcept {
		this->m_pivot = other.m_pivot;
		this->m_transform = other.m_transform;
		this->ChangeTexture(other.m_texture_file);
		return *this;
	}

	Sprite& Sprite::operator=(Sprite&& other) noexcept {
		this->m_image = other.m_image;
		other.m_image = nullptr;

		this->m_transform = other.m_transform;
		other.m_transform = nullptr;

		this->m_texture_file = other.m_texture_file;
		this->m_pivot = other.m_pivot;
		return *this;
	}

	void Sprite::Draw(Tigr* window) const {
		assert(m_image && "MSprite::Draw - Texture is nullptr!");

		tigrBlitAlpha(window, m_image, (int)(m_transform->position.x - (m_image->w * m_pivot.x)), 
			(int)(m_transform->position.y - (m_image->h * m_pivot.y)), 0, 0, m_image->w, m_image->h,1.0f);
	}

	void Sprite::ChangeTexture(const std::string& fileName) { 
		m_texture_file = fileName;
		if (m_image)
			tigrFree(m_image);

		m_image = tigrLoadImage(m_texture_file.c_str());
	}

	const Vec2 Sprite::getImageSize()
	{
		return Vec2((float)m_image->w, (float)m_image->h);
	}

	std::string Sprite::getPath()
	{
		return m_texture_file;
	}
}