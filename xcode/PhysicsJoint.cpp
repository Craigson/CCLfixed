#include "PhysicsJoint.h"

PhysicsJoint::PhysicsJoint( const glm::vec3& position, float radius, float mass, float drag ){
    this->position = position;
    this->radius = radius;
    this->mass = mass;
    this->drag = drag;
    prevPosition = position;
    anchor = position;
    forces = glm::vec3(0,0,0);
}


void PhysicsJoint::update(){
    glm::vec3 temp = position;
    glm::vec3 vel = ( position - prevPosition );// * drag;
    position += vel + forces / mass;
    prevPosition = temp;
    forces = glm::vec3(0,0,0);
}

void PhysicsJoint::draw(){
    ci::gl::drawSphere(position, 20);
}