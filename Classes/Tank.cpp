//
//  Tank.cpp
//  BallMan
//
//  Created by Richard Wei on 4/5/14.
//
//

#include "Tank.h"

static b2BodyDef b2BodyDefMake(b2BodyType _bodyType, bool _awake, b2Vec2 _position, float32 _angle) {
    b2BodyDef retBodyDef;
    retBodyDef.type = _bodyType;
    retBodyDef.awake = _awake;
    retBodyDef.position = _position;
    retBodyDef.angle = _angle;
    return retBodyDef;
}

static b2PolygonShape b2PolygonShapeMake(const b2Vec2 *_vertices, int32 _count) {
    b2PolygonShape retShape;
    retShape.Set(_vertices, _count);
    return retShape;
}

static b2CircleShape b2CircleShapeMake(float _radius) {
    b2CircleShape retShape;
    retShape.m_radius = _radius;
    return retShape;
}

static b2FixtureDef b2FixtureDefMake(const b2Shape *_shape, float32 _density, float32 _friction, float32 _restitution) {
    b2FixtureDef retFixtureDef;
    retFixtureDef.shape = _shape;
    retFixtureDef.density = _density;
    retFixtureDef.friction = _friction;
    retFixtureDef.restitution = _restitution;
    return retFixtureDef;
}

using namespace cocos2d;

Tank::Tank()
{
    
}

Tank::~Tank()
{
    
}

bool Tank::init()
{
    if (!CCSprite::init()) {
        return false;
    }
    return true;
}

void Tank::setProperties(b2Vec2 position, b2World *world, TankPosition pos)
{

    b2BodyDef bodyDef = b2BodyDefMake(b2_dynamicBody, true, position, 0);
    body = world->CreateBody(&bodyDef);
    b2PolygonShape shape;
    shape.SetAsBox(32, 32);
    b2FixtureDef fixDef = b2FixtureDefMake(&shape, 1.0, 0.3, 0.3);
    body->CreateFixture(&fixDef);
    body->SetUserData(this);
    
    b2BodyDef cannonBodyDef = b2BodyDefMake(b2_dynamicBody, false, b2Vec2_zero, 0);
    cannonBody = world->CreateBody(&cannonBodyDef);
    b2CircleShape cannonShape = b2CircleShapeMake(4);
    b2FixtureDef cannonFixDef = b2FixtureDefMake(&cannonShape, 1.0, 0.1, 0.4);
    cannonBody->CreateFixture(&cannonFixDef);
    cannonball = CCSprite::create("cannon_ball.png");
    cannonball->setTag(TankTagCannonball);
    cannonball->setVisible(false);
    this->addChild(cannonball);
    cannonBody->SetUserData(this);
    
    this->pos = pos;
    if (pos == TankPositionLeft) {
        CCSprite *barrel = CCSprite::create("red_barrel.png");
        barrel->setContentSize(CCSizeMake(32.0f, 4.0f));
        barrel->setPosition(ccp(28.0, 42.0));
        barrel->setAnchorPoint(ccp(0.0, 0.0));
        this->addChild(barrel);
    } else if (pos == TankPositionRight) {
        CCSprite *barrel = CCSprite::create("green_barrel.png");
        barrel->setContentSize(CCSizeMake(32.0f, 4.0f));
        barrel->setPosition(ccp(36.0f, 42.0f));
        barrel->setAnchorPoint(ccp(1.0, 0.0));
        this->addChild(barrel);
    }
}

void Tank::setBarrelAngle(float angle)
{
    CCSprite *barrel = (CCSprite *)this->getChildByTag(TankTagCannonball);
    barrel->setRotation(angle);
}


void Tank::fire(float strength)
{
    // fire the ball
    cannonBody->SetAwake(true);
    cannonball->setVisible(true);
}

void Tank::reload()
{
    body->SetActive(true);
    cannonBody->SetAwake(false);
    if (pos == TankPositionRight) { //green tank down
        cannonBody->SetTransform(b2Vec2(36.0f, 42.0f), 0.0f);
    } else if (pos == TankPositionLeft) {
        cannonBody->SetTransform(b2Vec2(28.0f, 42.0f), 0.0f);
    }
}
