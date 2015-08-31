#include "Joint.h"

class Bone{
public:
    float len;
    float k=5;
    Joint *a,*b;
    
    Bone();
    Bone(Joint *_a, Joint *_b, float l);
    
    void display();
    void update();
    
};


