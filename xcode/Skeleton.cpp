//
//  Skeleton.cpp
//  CCL
//
//  Created by Craig Pickard on 8/29/15.
//
//

#include "Skeleton.h"

Skeleton::~Skeleton(){
    for( std::vector<PhysicsJoint*>::iterator it = PhysicsJoints.begin(); it != PhysicsJoints.end(); ++it ){
        delete *it;
    }
    PhysicsJoints.clear();
}

Skeleton::Skeleton(){}

Skeleton::Skeleton(const std::vector<glm::vec3>& jointPos)
{
    

    
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

    
    
    
    //, elbow, hand;
   // Spring upperArm, foreArm;
  //  float rUpperArm = distance(r_shoulder, r_elbow);
//    float rForeArm = distance(r_elbow, r_hand);
    
//    shoulder = Node(r_shoulder);
//    elbow = Node(r_elbow);
//    hand = Node(r_hand);
    
    //Spring(Node *from, Node *to, float restLength, float stiffness, float damping)
    
  //  upperArm = Spring(&shoulder, &elbow, rUpperArm, 1,1);
    
}


void Skeleton::draw()
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
        

        
//        shoulder.render();
//        elbow.render();
//        hand.render();
//        
//        upperArm.render();
        for( std::vector<PhysicsJoint*>::iterator it = PhysicsJoints.begin(); it != PhysicsJoints.end(); ++it ){
            (*it)->draw();
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
//    
//    shoulder.update();
//    elbow.update();
//    hand.update();
//    
//    upperArm.update();
//
    
    for( std::vector<PhysicsJoint*>::iterator it = PhysicsJoints.begin(); it != PhysicsJoints.end(); ++it ){
        (*it)->update();
    }
    for (std::vector<Spring*>::iterator it = springs.begin(); it != springs.end(); ++it){
        (*it)->update();
    }
}

void Skeleton::addPhysicsJoint( PhysicsJoint *physicsJoint ){
    PhysicsJoints.push_back( physicsJoint );
}

void Skeleton::destroyPhysicsJoint( PhysicsJoint *physicsJoint ){
    std::vector<PhysicsJoint*>::iterator it = std::find( PhysicsJoints.begin(), PhysicsJoints.end(), physicsJoint );
    delete *it;
    PhysicsJoints.erase( it );
}

void Skeleton::addSpring(Spring *spring){
    springs.push_back(spring);
}

void Skeleton::destroySpring(Spring *spring){
    std::vector<Spring*>::iterator it; std::find(springs.begin(), springs.end(), spring);
    delete *it;
    springs.erase(it);
}
