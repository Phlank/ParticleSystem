#include "Point.h"

Point::Point() {
    x = DEFAULT_X;
    y = DEFAULT_Y;
}

Point::Point(long double x_, long double y_) {
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

void Point::setX(long double x_) {
    x = x_;
}

void Point::setY(long double y_) {
    y = y_;
}
