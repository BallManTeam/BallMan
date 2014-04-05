//
//  Ground.cpp
//  BallMan
//
//  Created by Richard Wei on 4/5/14.
//
//

#include "Ground.h"

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#endif
#ifdef _WIN32
#include <GL/gl.h>
#include <GL/glu.h>
#endif

using namespace cocos2d;

Ground::Ground()
{
    
}

Ground::~Ground()
{
    
}

void Ground::draw()
{
    float width = this->getContentSize().width;
    float height = this->getContentSize().height;
    CCNode::draw();
    
    CCPoint vertices[4] = {ccp(0.0f, 0.0f), ccp(0.0f, height), ccp(width, height), ccp(width, 0.0f)};
    ccDrawSolidPoly(vertices, 4, ccc4f(0.3, 1.0, 0.3, 0.9));
}
