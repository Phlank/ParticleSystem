#include "Particle.h"

Particle::Particle() {
    
}

Particle::Particle(Point position_) {
    position = position_;
}

Particle::Particle(Point position_, Point velocity_) {
    position = position_;
    velocity = velocity_;
}

Particle::Particle(Point position_, Point velocity_, Point acceleration_) {
    position = position_;
    velocity = velocity_;
    acceleration = acceleration_;
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
    long double initialAccelerationX = acceleration.getX();
    long double initialAccelerationY = acceleration.getY();
    long double initialVelocityX = velocity.getX();
    long double initialVelocityY = velocity.getY();
    acceleration.setX(initialAccelerationX+jerk.getX());
    acceleration.setY(initialAccelerationY+jerk.getY());
    velocity.setX(initialVelocityX+(initialAccelerationX+acceleration.getX())/2);
    velocity.setY(initialVelocityY+(initialAccelerationY+acceleration.getY())/2);
    position.setX(position.getX()+(initialVelocityX+velocity.getX())/2);
    position.setY(position.getY()+(initialVelocityY+velocity.getY())/2);
}

