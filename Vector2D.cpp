#include "Vector2D.hpp"

Vector2D::Vector2D() {
    x = y = 0.0f;
}

Vector2D::Vector2D(float x, float y) {
    this->x = x;
    this->y = y;
}

Vector2D& Vector2D::add(const Vector2D &vec) {
    this->x += vec.x;
    this->y += vec.y;

    return *this;
}

Vector2D &Vector2D::subtract(const Vector2D &vec) {
    this->x -= vec.x;
    this->y -= vec.y;

    return *this;
}

Vector2D &Vector2D::multiply(const Vector2D &vec) {
    this->x *= vec.x;
    this->y *= vec.y;

    return *this;
}

Vector2D &Vector2D::divide(const Vector2D &vec) {
    this->x /= vec.x;
    this->y /= vec.y;

    return *this;
}

Vector2D &operator+(Vector2D &vector_one, const Vector2D &vector_two) {
    return vector_one.add(vector_two);
}

Vector2D &operator-(Vector2D &vector_one, const Vector2D &vector_two) {
    return vector_one.subtract(vector_two);
}

Vector2D &operator*(Vector2D &vector_one, const Vector2D &vector_two) {
    return vector_one.multiply(vector_two);
}

Vector2D &operator/(Vector2D &vector_one, const Vector2D &vector_two) {
    return vector_one.divide(vector_two);
}

Vector2D& Vector2D::operator+=(const Vector2D &vec) {
    return this->add(vec);
}

Vector2D &Vector2D::operator-=(const Vector2D &vec) {
    return this->subtract(vec);
}

Vector2D &Vector2D::operator*=(const Vector2D &vec) {
    return this->multiply(vec);
}

Vector2D &Vector2D::operator/=(const Vector2D &vec) {
    return this->divide(vec);
}
 
 std::ostream& operator<<(std::ostream& stream, const Vector2D& vec) {
     stream << "(" << vec.x << "," << vec.y << ")";
     return stream;
 }