#include "Point.h"

Point::Point() {
    x = DEFAULT_X;
    y = DEFAULT_Y;
}

Point::Point(float x_, float y_) {
    x = x_;
    y = y_;
}

Point::Point(const Point& orig) {
    x = orig.x;
    y = orig.y;
}

Point::~Point() {
    
}

double Point::getX() {
    return x;
}

double Point::getY() {
    return y;
}

void Point::setX(float x_) {
    x = x_;
}

void Point::setY(float y_) {
    y = y_;
}
