#ifndef POINT_H
#define	POINT_H

#include <cstdlib>

static const long double DEFAULT_X = 0.0;
static const long double DEFAULT_Y = 0.0;

class Point {
public:
    /// Creates a point with default values.
    Point();
    /// Creates a point with the specified values.
    Point(long double x_, long double y_);
    /// Creates a point as a copy of another point.
    Point(const Point& orig);
    /// Class destructor.
    virtual ~Point();
    /// \return the x value of the point
    double getX();
    /// \return the y value of the point
    double getY();
    /// Sets the x value of the point.
    void setX(long double x_);
    /// Sets the y value of the point.
    void setY(long double y_);
private:
    long double x;
    long double y;
};

#endif

