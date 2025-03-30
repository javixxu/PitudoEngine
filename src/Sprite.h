#pragma once
#include <ecs/ecsDefinitions.h>
#include <string>
#include <vector>
#include "Transform.h"
#include "Vec2.h"

struct Tigr;
namespace PitudoEngine {
	class Sprite : public Component {
		Tigr* m_image = nullptr;
	protected:
		std::string m_texture_file;
		const Transform* m_transform;

		//int m_hframes;               // Numero de frames en horizontal
		//int m_vframes;               // Numero de frames en vertical

		//int m_fps;                   // Frames por segundo
		//float m_currentFrame;        // Frame actual
	public:
		Vec2 m_pivot;

		Sprite();
		Sprite(const Transform* transform, const std::string& fileName, Vec2 pivot = Vec2(0.5f));
		~Sprite();

		Sprite(const Sprite& other) noexcept;
		Sprite(Sprite&& other) noexcept;
		Sprite& operator=(const Sprite& other) noexcept;
		Sprite& operator=(Sprite&& other) noexcept;

		void Draw(Tigr* window) const;
		void ChangeTexture(const std::string& fileName);
		const Vec2 getImageSize();

		std::string getPath();

		static bool Load(std::string& fileName, Sprite& obj);
		static bool Save(std::string& fileName, const Sprite& obj);
	};
}
