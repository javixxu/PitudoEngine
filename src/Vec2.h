#pragma	once
#include <ostream>

class Vec2
{
public:
	float x;
	float y;

	Vec2();
	Vec2(float _unique);
	Vec2(float _x, float _y);
	~Vec2();

	Vec2 operator+(const Vec2& _other) const;
	Vec2 operator+=(const Vec2& _other);
	Vec2 operator-(const Vec2& _other) const;
	Vec2 operator*(const Vec2& _other) const;
	Vec2 operator/(const Vec2& _other) const;
	bool operator==(const Vec2& _other) const;
	bool operator==(const float& _other) const;
	bool operator!=(const Vec2& _other) const;
	bool operator!=(const float& _other) const;
	friend std::ostream& operator<<(std::ostream& os, const Vec2& vec);

	Vec2 Abs() const;
	float Length() const;
	Vec2 Normalize() const;
	float Dot(const Vec2& other) const;
	float Angle(const Vec2& other) const;
	float Distance(const Vec2& other) const;

};