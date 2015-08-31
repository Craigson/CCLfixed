//
//  Skeleton.h
//  CCL
//
//  Created by Craig Pickard on 8/29/15.
//
//

#pragma once

#include <stdio.h>
#include "Node.h"
#include "Spring.h"

class Skeleton{
public:
    
        ~Skeleton();
    
    Skeleton();
    Skeleton(const std::vector<glm::vec3>& jointPos);

    
    void update();
    void update(const std::vector<glm::vec3>& pos);
    void draw();
    
    void addPhysicsJoint( PhysicsJoint *PhysicsJoint );
    void destroyPhysicsJoint( PhysicsJoint *PhysicsJoint );
    void addSpring(Spring *spring);
    void destroySpring(Spring *spring);
    
    std::vector<PhysicsJoint*> PhysicsJoints;
    std::vector<Spring*> springs;
    
    
    

    
    std::vector<glm::vec3>boneJoints;
    
    glm::vec3 head, r_shoulder, r_elbow, r_hand, l_shoulder, l_elbow, l_hand, spine_base, spine_top, r_hip, r_knee, r_foot, l_hip, l_knee, l_foot;
    
//    //ci::gl::VertBatchRef	mSkeletonMesh;
//    
//    void render();
//    void update(const std::vector<glm::vec3>& positions);
//    
//    ci::gl::VboRef              mSkeletonVbo;
//    
//   // ci::gl::VertBatchRef        mSkeletonMesh;
//    
//    ci::gl::VboMeshRef          mSkeletonMesh;
//
//    Spring upperArm;
    
    
    
};


