#ifndef POINT_H
#define	POINT_H

#include <cstdlib>

static const long double DEFAULT_X = 0.0;
static const long double DEFAULT_Y = 0.0;

class Point {
public:
    Point();
    Point(long double x_, long double y_);
    Point(const Point& orig);
    virtual ~Point();
    double getX();
    double getY();
    void setX(long double x_);
    void setY(long double y_);
private:
    long double x;
    long double y;
};

#endif

