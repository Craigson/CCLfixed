#pragma once

#include "cinder/gl/gl.h"
#include "cinder/Vector.h"

class PhysicsJoint{
public:
    
    PhysicsJoint( const glm::vec3& position, float radius, float mass, float drag );
    
    void update();
    void draw();
    
    glm::vec3 position, prevPosition, anchor;
    glm::vec3 forces;
    float radius;
    float mass;
    float drag;
};