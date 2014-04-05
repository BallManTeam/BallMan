//
//  Tank.h
//  BallMan
//
//  Created by Richard Wei on 4/5/14.
//
//

#ifndef __BallMan__Tank__
#define __BallMan__Tank__

#include "cocos2d.h"
#include "Box2D.h"

typedef enum {
    TankPositionLeft,
    TankPositionRight
} TankPosition;

typedef enum {
    TankTagInvalid = 0,
    TankTagBarrel1,
    TankTagBarrel2,
    TankTagCannonball
} TankTag;

class Tank : public cocos2d::CCSprite {
    
public:
    Tank();
    virtual ~Tank();
    CREATE_FUNC(Tank);
    virtual bool init();
    
    void setProperties(b2Vec2 position, b2World *world, TankPosition pos);
    
    TankPosition pos;
    
    CCSprite *cannonball;
    
    b2Body *body;
    b2Body *cannonBody;
    
    void setBarrelAngle(float angle); // DEGREES
    
    void fire(float strength);
    void reload();
};

#endif /* defined(__BallMan__Tank__) */
