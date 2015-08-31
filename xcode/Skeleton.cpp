//
//  Skeleton.cpp
//  CCL
//
//  Created by Craig Pickard on 8/29/15.
//
//

#include "Skeleton.h"

Skeleton::Skeleton(){}

Skeleton::Skeleton(const std::vector<glm::vec3>& jointPos)
{
    boneJoints = jointPos;
    
    
    head = boneJoints[0];
    r_shoulder = boneJoints[6];
    r_elbow = boneJoints[8];
    r_hand = boneJoints[9];
    l_shoulder = boneJoints[13];
    l_elbow = boneJoints[16];
    l_hand = boneJoints[17];
    spine_base = boneJoints[27];
    spine_top = boneJoints[21];
//  r_hip = boneJoints[30];
    r_hip = boneJoints[28];
    r_knee = boneJoints[34];
    r_foot = boneJoints[35];
//  l_hip = boneJoints[31];
    l_hip = boneJoints[29];
    l_knee = boneJoints[43];
    l_foot = boneJoints[44];
    
    /*
    for (int i = 0; i < boneJoints.size(); i++){
        physicsJoints[i] = Joint(boneJoints[i]);
    }
    */
    physicsJoints.push_back(Joint(r_shoulder));
    physicsJoints.push_back(Joint(r_elbow));
    physicsJoints.push_back(Joint(r_hand));
    
    float rUpperArm = distance(r_shoulder, r_elbow);
    float rForeArm = distance(r_elbow, r_hand);
    
    physicsBones.push_back(Bone(&physicsJoints[0], &physicsJoints[1], rUpperArm));
    physicsBones.push_back(Bone(&physicsJoints[1], &physicsJoints[2], rForeArm));
    
    
     }

void Skeleton::render()
    {
        ci::gl::color(1.,1.,1.);
        ci::gl::lineWidth(5);
        
        //NECK
        //ci::gl::drawLine(head,spine_top);
        
        //TORSO
        ci::gl::drawLine(r_shoulder, l_shoulder);
        ci::gl::drawLine(spine_top, spine_base);
        ci::gl::drawLine(spine_base, r_hip);
        ci::gl::drawLine(spine_base, l_hip);
        
        //RIGHT ARM
        ci::gl::drawLine(r_shoulder, r_elbow);
        ci::gl::drawLine(r_elbow, r_hand);
        
        //LEFT ARM
        ci::gl::drawLine(l_shoulder, l_elbow);
        ci::gl::drawLine(l_elbow, l_hand);
        
        //RIGHT LEG
        ci::gl::drawLine(r_hip, r_knee);
        ci::gl::drawLine(r_knee, r_foot);
        
        //LEFT LEG
        ci::gl::drawLine(l_hip, l_knee);
        ci::gl::drawLine(l_knee, l_foot);
        
        for (auto j : physicsJoints){
            j.display();
        }
        
        for (auto b : physicsBones){
            b.display();
        }

    }

void Skeleton::update(const std::vector<glm::vec3>& pos){

    boneJoints = pos;

    head = boneJoints[0];
    r_shoulder = boneJoints[6];
    r_elbow = boneJoints[8];
    r_hand = boneJoints[9];
    l_shoulder = boneJoints[13];
    l_elbow = boneJoints[16];
    l_hand = boneJoints[17];
    spine_base = boneJoints[27];
    spine_top = boneJoints[21];
    r_hip = boneJoints[28];
    r_knee = boneJoints[34];
    r_foot = boneJoints[35];
    l_hip = boneJoints[29];
    l_knee = boneJoints[43];
    l_foot = boneJoints[44];
    
   // std::cout << l_foot << std::endl;
    
    physicsJoints[0].location = r_shoulder;
//    physicsJoints[1].location = r_elbow;
//    physicsJoints[2].location = r_hand;
    
    for (auto j : physicsJoints){
        j.update();
    }
    
    for (auto b : physicsBones){
        b.update();
    }
    
    
}

