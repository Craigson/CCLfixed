#include "Node.h"

using namespace ci;
using namespace ci::app;

Node::Node(){}

Node::Node(const glm::vec3& loc){
    mLoc = loc;
    isLocked = false;
    mVel = vec3(0.,0.,0.);
    
    prevPosition = loc;
    force = vec3(0.,0.,0.);
    
    maxVel = 5.;
    damping = 1.;
    
}


void Node::repel(vec3 force)
{
  //  float dist = distance(mLoc,force);
}


void Node::update(){
    if (isLocked == false){
        vec3 temp = mLoc;
        vec3 vel = ( mLoc - prevPosition ); // * drag;
        mLoc += (vel + force);
        prevPosition = temp;
        std::cout << mLoc << std::endl;
        force *= 0;
    }
}

void Node::render(){
    gl::color(ColorA(1.,1.,1.,1.));
    gl::pointSize(2.);
    gl::vertex(mLoc);
    gl::drawSphere(mLoc, 1);
   // gl::drawSolidRect(Rectf()
}

float Node::getX(){
    return mLoc.x;
}

float Node::getY(){
    return mLoc.y;
}

float Node::getZ(){
    return mLoc.z;
}

void Node::setDamping(float _damping){
    damping = _damping;
}

void Node::lock(){
    isLocked = !isLocked;
}
