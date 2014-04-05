//
//  Ground.h
//  BallMan
//
//  Created by Richard Wei on 4/5/14.
//
//

#ifndef __BallMan__Ground__
#define __BallMan__Ground__

#include "cocos2d.h"
#include "Box2D.h"
#include <vector>

class Ground : public cocos2d::CCSprite {
public:
    Ground();
    virtual ~Ground();

    CREATE_FUNC(Ground);
    
    virtual void draw();
    
    b2Body *body;
    
    
    vector<b2PolygonShape> shapes;
//    vector<b2Shape> shapes;
//    vector<b2Shape> shapes;
    
    void setProperties(cocos2d::CCSize winSize, b2World *world);
};

#endif /* defined(__BallMan__Ground__) */
