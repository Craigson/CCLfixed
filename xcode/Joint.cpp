#include "Joint.h"

using namespace ci;

Joint::Joint(){
    velocity = vec3(0.0,0.0,0.0);
    acceleration = vec3(0.0,0.0,0.0);
    dragOffset = vec3(0.0,0.0,0.0);
}

/*
Joint::Joint(ci::vec3 loc, int d, int p, int l, int m, int r, std::string n){
    location = loc;
    degree =d; //wont need this
    parent = p;
    lchild=l;
    mchild=m;
    rchild=r;
    name=n;
    
    velocity = vec3(0.0,0.0,0.0);
    acceleration = vec3(0.0,0.0,0.0);
    dragOffset = vec3(0.0,0.0,0.0);
}

Joint::Joint(glm::vec3 loc, int p, int l, int m, int r, std::string n){
    
    location = loc;
    parent = p;
    lchild=l;
    mchild=m;
    rchild=r;
    name=n;
    
    velocity = vec3(0.0,0.0,0.0);
    acceleration = vec3(0.0,0.0,0.0);
    dragOffset = vec3(0.0,0.0,0.0);
}
 */

Joint::Joint(glm::vec3 loc){
    
    location = loc;
    
    velocity = vec3(0.0,0.0,0.0);
    acceleration = vec3(0.0,0.0,0.0);
    dragOffset = vec3(0.0,0.0,0.0);
    
    isDataDriven = true;
}

void Joint::display(){
    gl::color(0.68, 0.68, 0.68);
    gl::drawColorCube(location, vec3(m,m,m));
    
}

void Joint::update(){
    velocity+=(acceleration);
    std::cout << "acc: " << acceleration<< std::endl;
    velocity*=damp;
    location+=velocity;
    //std::cout << "velocity: " << velocity << std::endl;
    acceleration*=0;
}

void Joint::applyForce(ci::vec3 f){
    vec3 force =f;
    //std::cout << force << std:: endl;
    force/=m;
    
    acceleration+=force;
}


void Joint::update1( ci::vec3 newloc){
    
    velocity+=(acceleration);
    velocity*=damp;
    location+=velocity;
    
    acceleration*=0;
}


/*

void Joint::click(ci::vec3 po){
    
    float d = distance(po, location);
    if (d < m) {   //if less than the radius
        drag = true;
        cinder::app::console()<<"set drag true"<<drag<<std::endl;
        dragOffset.x = location.x-po.x;
        dragOffset.y = location.y-po.y;
        dragOffset.z = location.z-po.z;
    }
}



void Joint::dragged(ci::vec3 po){
    if(drag){
        location = po+ dragOffset;
    }
} 
 */










