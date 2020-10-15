#ifndef Vector2D_hpp
#define Vector2D_hpp

#include <iostream>

class Vector2D {
public:
    float x, y;

    Vector2D();
    Vector2D(float x, float y);

    Vector2D& add(const Vector2D& vec);
    Vector2D &subtract(const Vector2D &vec);
    Vector2D &multiply(const Vector2D &vec);
    Vector2D &divide(const Vector2D &vec);

    friend Vector2D& operator+(Vector2D& vector_one, const Vector2D& vector_two);
    friend Vector2D &operator-(Vector2D &vector_one, const Vector2D &vector_two);
    friend Vector2D &operator*(Vector2D &vector_one, const Vector2D &vector_two);
    friend Vector2D &operator/(Vector2D &vector_one, const Vector2D &vector_two);

    Vector2D& operator+=(const Vector2D& vec);
    Vector2D &operator-=(const Vector2D &vec);
    Vector2D &operator*=(const Vector2D &vec);
    Vector2D &operator/=(const Vector2D &vec);

    Vector2D& operator*(const int& i);
    Vector2D& zero();

    friend std::ostream& operator<<(std::ostream& stream, const Vector2D& vec);

};

#endif