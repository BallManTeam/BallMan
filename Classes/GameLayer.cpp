//
//  GameLayer.cpp
//  BallMan
//
//  Created by Richard Wei on 4/4/14.
//
//

#include "GameLayer.h"

using namespace cocos2d;

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

CCScene* GameLayer::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    GameLayer *layer = GameLayer::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

bool GameLayer::init()
{
    if (!CCLayer::init())
    {
        return false;
    }
    
    b2Vec2 gravity;
    gravity.Set(0.0f, -10.0f);
    world = new b2World(gravity);
    world->SetContinuousPhysics(true);
    world->SetContactListener(contactListener = new ContactListener());
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0, 0);
    b2Body *groundBody = world->CreateBody(&groundBodyDef);
    b2PolygonShape groundBox;
    groundBox.SetAsEdge(b2Vec2(0, visibleSize.height+500), b2Vec2(0, 0));
    groundBody->CreateFixture(&groundBox, 0);
    groundBox.SetAsEdge(b2Vec2(visibleSize.width, visibleSize.height + 500), b2Vec2(visibleSize.width, 0));
    groundBody->CreateFixture(&groundBox, 0);
    
    return true;
}
