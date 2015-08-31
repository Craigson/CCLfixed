//
//  Trail.cpp
//  CCLfixed
//
//  Created by Craig Pickard on 8/31/15.
//
//

#include "Trail.h"

Trail::Trail(){
    
}

Trail::Trail(const glm::vec3& origin)
{
    mTrailMesh = ci::gl::VertBatch::create( GL_LINES );
    
    ci::ColorA defaultColor( 0.9f, 0.9f, 0.9f,0.1f);
    
    mTrailMesh->color( defaultColor );
    
    positions.push_back(origin);
}


void Trail::update(const glm::vec3& pos)
{
    positions.push_back(pos);
    mTrailMesh->clear();
    mTrailMesh->color( defaultColor );
    for (int i = 0; i < positions.size(); i++)
    {
        mTrailMesh->vertex(positions[i]);
    }
    std::cout << positions.size() << std::endl;
}

void Trail::render(){
    ci::gl::lineWidth(5);
    mTrailMesh->draw();
    std::cout << "i'm drawing" << std::endl;

}