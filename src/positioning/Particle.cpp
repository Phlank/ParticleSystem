#include "Particle.h"

Particle::Particle() {
    position;
    velocity;
    acceleration;
    jerk;
}

Particle::Particle(Point position_) {
    position = position_;
    velocity;
    acceleration;
    jerk;
}

Particle::Particle(Point position_, Point velocity_) {
    position = position_;
    velocity = velocity_;
    acceleration;
    jerk;
}

Particle::Particle(Point position_, Point velocity_, Point acceleration_) {
    position = position_;
    velocity = velocity_;
    acceleration = acceleration_;
    jerk;
}

Particle::Particle(Point position_, Point velocity_, Point acceleration_, Point jerk_) {
    position = position_;
    velocity = velocity_;
    acceleration = acceleration_;
    jerk = jerk_;
}

Particle::Particle(const Particle& orig) {
    position = orig.position;
    velocity = orig.velocity;
    acceleration = orig.acceleration;
    jerk = orig.jerk;
}

Particle::~Particle() {
    position.~Point();
    velocity.~Point();
    acceleration.~Point();
    jerk.~Point();
}

Point Particle::getPosition() {
    return position;
}

Point Particle::getVelocity() {
    return velocity;
}

Point Particle::getAcceleration() {
    return acceleration;
}

Point Particle::getJerk() {
    return jerk;
}

void Particle::setPosition(Point position_) {
    position = position_;
}

void Particle::setVelocity(Point velocity_) {
    velocity = velocity_;
}

void Particle::setAcceleration(Point acceleration_) {
    acceleration = acceleration_;
}

void Particle::setJerk(Point jerk_) {
    jerk = jerk_;
}

void Particle::runFrame() {
    long double inAccX = acceleration.getX();
    long double inAccY = acceleration.getY();
    long double inVelX = velocity.getX();
    long double inVelY = velocity.getY();
    acceleration.setX(inAccX+jerk.getX());
    acceleration.setY(inAccY+jerk.getY());
    velocity.setX(inVelX+(inAccX+acceleration.getX())/2);
    velocity.setY(inVelY+(inAccY+acceleration.getY())/2);
    position.setX(position.getX()+(inVelX+velocity.getX())/2);
    position.setY(position.getY()+(inVelY+velocity.getY())/2);
}

