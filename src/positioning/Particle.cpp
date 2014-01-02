#include "Particle.h"

Particle::Particle() {
    pos;
    vel;
    acc;
    jer;
}

Particle::Particle(Point pos_) {
    pos = pos_;
}

Particle::Particle(Point pos_, Point vel_) {
    pos = pos_;
    vel = vel_;
}

Particle::Particle(Point pos_, Point vel_, Point acc_) {
    pos = pos_;
    vel = vel_;
    acc = acc_;
}

Particle::Particle(Point pos_, Point vel_, Point acc_, Point jer_) {
    pos = pos_;
    vel = vel_;
    acc = acc_;
    jer = jer_;
}

Particle::Particle(const Particle& orig) {
    pos = orig.pos;
    vel = orig.vel;
    acc = orig.acc;
    jer = orig.jer;
}

Particle::~Particle() {
    pos.~Point();
    vel.~Point();
    acc.~Point();
    jer.~Point();
}

Point Particle::getPos() {
    return pos;
}

Point Particle::getVel() {
    return vel;
}

Point Particle::getAcc() {
    return acc;
}

Point Particle::getJer() {
    return jer;
}

void Particle::setPos(Point pos_) {
    pos = pos_;
}

void Particle::setVel(Point vel_) {
    vel = vel_;
}

void Particle::setAcc(Point acc_) {
    acc = acc_;
}

void Particle::setJer(Point jer_) {
    jer = jer_;
}

void Particle::runFrame() {
    long double inAccX = acc.getX();
    long double inAccY = acc.getY();
    long double inVelX = vel.getX();
    long double inVelY = vel.getY();
    acc.setX(inAccX+jer.getX());
    acc.setY(inAccY+jer.getY());
    vel.setX(inVelX+(inAccX+acc.getX())/2);
    vel.setY(inVelY+(inAccY+acc.getY())/2);
    pos.setX(pos.getX()+(inVelX+vel.getX())/2);
    pos.setY(pos.getY()+(inVelY+vel.getY())/2);
}

