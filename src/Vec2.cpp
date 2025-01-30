#include "Vec2.h"
#include "math.h"

Vec2::Vec2():x(0),y(0){
}

Vec2::Vec2(float _unique): x(_unique),y(_unique){
}

Vec2::Vec2(float _x, float _y):x(_x),y(_y){
}

Vec2::~Vec2(){
}

Vec2 Vec2::operator+(const Vec2& _other) const
{
	return Vec2(x + _other.x,y + _other.y);
}

Vec2 Vec2::operator+=(const Vec2& _other) 
{
    this->x += _other.x;
    this->y += _other.y;
    return *this;
}

Vec2 Vec2::operator-(const Vec2& _other) const
{
	return Vec2(x - _other.x, y - _other.y);
}

Vec2 Vec2::operator*(const Vec2& _other) const
{
	return Vec2(x * _other.x, y * _other.y);
}

Vec2 Vec2::operator/(const Vec2& _other) const
{
	return Vec2(x / _other.x, y / _other.y);
}

bool Vec2::operator==(const Vec2& _other) const
{
    return this->x == _other.x && this->y == _other.y;
}

bool Vec2::operator==(const float& _other) const
{
    return this->x == _other && this->y == _other;
}

bool Vec2::operator!=(const Vec2& _other) const
{
    return !(*this==_other);
}

bool Vec2::operator!=(const float& _other) const
{
    return !(*this == _other);
}

std::ostream& operator<<(std::ostream& os, const Vec2& vec)
{
	os << "(" << vec.x << ", " << vec.y << ")";
	return os;
}

// Valor absoluto (vector con valores absolutos)
Vec2 Vec2::Abs() const{
    return Vec2(std::abs(x), std::abs(y));
}

// Longitud (magnitud)
float Vec2::Length() const {
    return std::sqrt(x * x + y * y);
}

// Vector normalizado
Vec2 Vec2::Normalize() const {
    float len = Length();
    if (len == 0.0f) {
        return Vec2(0.0f, 0.0f);
    }
    return *this / len;
}

// Producto escalar
float Vec2::Dot(const Vec2& other) const {
    return x * other.x + y * other.y;
}

// Angulo entre dos vectores (en radianes)
float Vec2::Angle(const Vec2& other) const {
    // Asegurarse de que los vectores no sean nulos.
    float dotProduct = Dot(other);
    float magnitudes = Length() * other.Length();
    if (magnitudes == 0.0f) {
        return 0.0f;
    }

    // Calcular el ángulo en radianes usando el coseno inverso
    float angle = std::acos(dotProduct / magnitudes);

    // Determinar la dirección del ángulo con el producto cruzado
    float crossProduct = this->x * other.y - this->y * other.x;

    // Si el producto cruzado es negativo, el ángulo es negativo
    if (crossProduct < 0) {
        angle = -angle;
    }

    return angle; // El ángulo estará en el rango de -π a π
}

// Distancia entre dos vectores
float Vec2::Distance(const Vec2& other) const {
    float dx = other.x - x;
    float dy = other.y - y;
    return std::sqrt(dx * dx + dy * dy);
}