/** This class is used to store information about an object's position and its 
 three subsequent derivatives. */

#ifndef PARTICLE_H
#define	PARTICLE_H

#include "Point.h"

class Particle {
public:
    /** Constructs a new Particle with default values. */
    Particle();
    /** Constructs a new Particle with the given position. */
    Particle(Point position_);
    /** Constructs a new Particle with the given position and one derivative. */
    Particle(Point position_, Point velocity_);
    /** Constructs a new Particle with the given position and two derivatives. */
    Particle(Point position_, Point velocity_, Point acceleration_);
    /** Constructs a new Particle with the given position and three derivatives. */
    Particle(Point position_, Point velocity_, Point acceleration_, Point jerk_);
    /** Constructs a new Particle based on a given one. */
    Particle(const Particle& orig);
    /** Class destructor. */
    virtual ~Particle();
    /** Returns the position. */
    Point getPosition();
    /** Returns the velocity. */
    Point getVelocity();
    /** Returns the acceleration. */
    Point getAcceleration();
    /** Returns the jerk. */
    Point getJerk();
    /** Sets the position. */
    void setPosition(Point position_);
    /** Sets the velocity. */
    void setVelocity(Point velocity_);
    /** Sets the acceleration. */
    void setAcceleration(Point acceleration_);
    /** Sets the jerk. */
    void setJerk(Point jerk_);
    /** Runs through a frame of activity. The position will change based on the 
     derivatives given. */
    void runFrame();
private:
    Point position, velocity, acceleration, jerk;
};

#endif

