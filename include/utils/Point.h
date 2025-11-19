#pragma once

#include <cmath>

class Point {
private:
    float x;
    float y;

public:
    Point();
    
    Point(float x, float y);
    
    float getX() const;
    float getY() const;
    
    void setX(float x);
    void setY(float y);
    
    float distanceTo(const Point& other) const;
    
    bool isValid() const;
    
    bool operator==(const Point& other) const;
    bool operator!=(const Point& other) const;
};