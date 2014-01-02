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
    Particle(Point pos_);
    /** Constructs a new Particle with the given position and one derivative. */
    Particle(Point pos_, Point vel_);
    /** Constructs a new Particle with the given position and two derivatives. */
    Particle(Point pos_, Point vel_, Point acc_);
    /** Constructs a new Particle with the given position and three derivatives. */
    Particle(Point pos_, Point vel_, Point acc_, Point jer_);
    /** Constructs a new Particle based on a given one. */
    Particle(const Particle& orig);
    /** Class destructor. */
    virtual ~Particle();
    /** Returns the position. */
    Point getPos();
    /** Returns the velocity. */
    Point getVel();
    /** Returns the acceleration. */
    Point getAcc();
    /** Returns the jerk. */
    Point getJer();
    /** Sets the position. */
    void setPos(Point pos_);
    /** Sets the velocity. */
    void setVel(Point vel_);
    /** Sets the acceleration. */
    void setAcc(Point acc_);
    /** Sets the jerk. */
    void setJer(Point jer_);
    /** Runs through a frame of activity. The position will change based on the 
     derivatives given. */
    void runFrame();
private:
    Point pos, vel, acc, jer;
};

#endif

