#ifndef POINT_H
#define	POINT_H

#include <cstdlib>

static const float DEFAULT_X = 0.0;
static const float DEFAULT_Y = 0.0;

class Point {
public:
    /// Creates a point with default values.
    Point();
    /// Creates a point with the specified values.
    Point(float x_, float y_);
    /// Creates a point as a copy of another point.
    Point(const Point& orig);
    /// Class destructor.
    virtual ~Point();
    /// \return the x value of the point
    double getX();
    /// \return the y value of the point
    double getY();
    /// Sets the x value of the point.
    void setX(float x_);
    /// Sets the y value of the point.
    void setY(float y_);
private:
    float x;
    float y;
};

#endif

