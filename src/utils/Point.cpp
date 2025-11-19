#include "../../include/utils/Point.h"

Point::Point() : x(0), y(0) {}

Point::Point(float x, float y) : x(x), y(y) {}

float Point::getX() const {
    return x;
}

float Point::getY() const {
    return y;
}

void Point::setX(float x) {
    this->x = x;
}

void Point::setY(float y) {
    this->y = y;
}

float Point::distanceTo(const Point& other) const {
    float dx = x - other.x;
    float dy = y - other.y;
    return std::sqrt(dx * dx + dy * dy);
}

bool Point::isValid() const {
    return x >= 0.0f && x <= 500.0f && y >= 0.0f && y <= 500.0f;
}

bool Point::operator==(const Point& other) const {
    return std::abs(x - other.x) < 1e-6f && std::abs(y - other.y) < 1e-6f;
}

bool Point::operator!=(const Point& other) const {
    return !(*this == other);
}