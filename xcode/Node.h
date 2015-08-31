//
//  Node.h
//  DigitalFabric
//
//  Created by Craig Pickard on 5/15/15.
//
//

#pragma once

#include <stdio.h>
using namespace ci;

class Node {
public:
    Node(const ci::vec3& loc);
    Node();
    
    void repel(vec3 force);
    void update();
    void render();
    float getX();
    float getY();
    float getZ();
    
    void setDamping(float _damping);
    
    void lock();
    
    ci::vec3 mLoc;
    ci::vec3 mVel;
    ci::vec3 lockPos;
    vec3 prevPosition;
    vec3 force;
    
    float maxVel;
    float damping;
    
    bool isLocked;
    
};
