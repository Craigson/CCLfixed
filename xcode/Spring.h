
#pragma once

#include <stdio.h>
#include "PhysicsJoint.h"
#include "cinder/gl/gl.h"

class Spring {
    
public:
    
    Spring(PhysicsJoint *PhysicsJointA, PhysicsJoint *PhysicsJointB, float rest, float strength);
    
    void update();
    void draw();
    
    PhysicsJoint *PhysicsJointA;
    PhysicsJoint *PhysicsJointB;
    
    float strength, rest;
    
};
