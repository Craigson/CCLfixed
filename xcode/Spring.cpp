//
//  Spring.cpp
//  MeshTest
//
//  Created by Craig Pickard on 4/15/15.
//
//

#include "Spring.h"

Spring::Spring(PhysicsJoint *PhysicsJointA, PhysicsJoint *PhysicsJointB, float rest, float strength){
    this->PhysicsJointA = PhysicsJointA;
    this->PhysicsJointB = PhysicsJointB;
    this->rest = rest;
    this->strength = strength;
}

void Spring::update(){
    glm::vec3 delta = PhysicsJointA->position - PhysicsJointB->position;
    float length = glm::length(delta);
    float invMassA = 1 / PhysicsJointA->mass;
    float invMassB = 1 / PhysicsJointB->mass;
    float normDist = (length-rest) / (length * (invMassA + invMassB)) * strength;
   PhysicsJointA->position -= delta * normDist * invMassA;
    //particleB->position -= delta * normDist * invMassB;
}

void Spring::draw(){
    
    ci::gl::enableAlphaBlending();
    ci::gl::color( ci::ColorA(1.f,1.f,1.f, 0.05f) );
    ci::gl::drawLine(PhysicsJointA->position, PhysicsJointB->position);
}