//
//  GameLayer.cpp
//  BallMan
//
//  Created by Richard Wei on 4/4/14.
//
//

#include "GameLayer.h"

#include "Ground.h"

using namespace cocos2d;

#define B2VEC2_TO_CCPOINT(__VEC__) (CCPointMake(__VEC__.x, __VEC__.y))

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
    gravity.Set(0.0f, -1000.0f);
    world = new b2World(gravity);
    world->SetContinuousPhysics(true);
    world->SetContactListener(contactListener = new ContactListener());
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    // Ground definition
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(visibleSize.width/2, 15.0f);
    b2Body *groundBody = world->CreateBody(&groundBodyDef);
    b2PolygonShape groundBox;
    groundBox.SetAsBox(visibleSize.width/2, 15.0f);
    groundBody->CreateFixture(&groundBox, 0);
    Ground *ground = Ground::create();
    ground->setPosition(CCPointMake(visibleSize.width/2, 15.0f));
    ground->setContentSize(ccp(visibleSize.width, 30.0f));
    CCLOG("%f %f", visibleSize.width, visibleSize.height);
    this->addChild(ground);
    groundBody->SetUserData(ground);
    
    // Tank body definition
    b2BodyDef tankBodyDef;
    tankBodyDef.type = b2_dynamicBody;
    tankBodyDef.position.Set(100, 100);
    b2Body *leftTankBody = world->CreateBody(&tankBodyDef);
    tankBodyDef.position.Set(visibleSize.width-100, 100);
    b2Body *rightTankBody = world->CreateBody(&tankBodyDef);
    b2PolygonShape tankShape;
    tankShape.SetAsBox(32, 32);
    b2FixtureDef tankFixtureDef;
    tankFixtureDef.shape = &tankShape;
    tankFixtureDef.density = 1.0f;
    tankFixtureDef.friction = 0.3f;
    tankFixtureDef.restitution = 0.2f;
    leftTankBody->CreateFixture(&tankFixtureDef);
    rightTankBody->CreateFixture(&tankFixtureDef);

    // Left and right tank
    CCSprite *leftTank = CCSprite::create("red_tank.png");
    leftTank->setPosition(ccp(100.0f, 100.0f));
    this->addChild(leftTank);
    leftTankBody->SetUserData(leftTank);
    CCSprite *rightTank = CCSprite::create("green_tank.png");
    rightTank->setPosition(ccp(visibleSize.width-100.0f, 100.0f));
    this->addChild(rightTank);
    rightTankBody->SetUserData(rightTank);
    
    this->schedule(schedule_selector(GameLayer::tick));
    
    return true;
}

void GameLayer::tick(float dt)
{
    world->Step(dt, 8, 1);
	for (b2Body *b = world->GetBodyList(); b; b = b->GetNext()) if (b->GetUserData()) {
        CCSprite *myActor = (CCSprite *)(b->GetUserData());
        b2Vec2 pos = b->GetPosition();
        myActor->setPosition(B2VEC2_TO_CCPOINT(pos));
    }
//        myActor.position = B2VEC2_M_TO_CGPOINT_P(pos);
//        if (b != knifeBody) myActor.rotation = -CC_RADIANS_TO_DEGREES(b->GetAngle());
//            }
//    std::set<b2Body*>::iterator pos;
//    for (pos = contactListener->slicedFruits.begin();
//         pos != contactListener->slicedFruits.end(); ++pos) {
//        b2Body *body = *pos;
//        CCNode *contactNode = (CCNode *)body->GetUserData();
//        CGPoint position = contactNode.position;
//        for (int i = 0; i < 6; i++) {
//            CCNode *superNode = [self getChildByTag:GameLayerTagFruitBatch0+i];
//            if ([superNode.children containsObject:contactNode])
//                [superNode removeChild:contactNode cleanup:YES];
//        }
//        world->DestroyBody(body);
//        --fruitCount;
//        CCParticleSun *explosion = [[CCParticleSun alloc] initWithTotalParticles:200];
//        explosion.autoRemoveOnFinish = YES;
//        explosion.startSize = 10.0f;
//        explosion.speed = 70.0f;
//        explosion.anchorPoint = ccp(0.5f, 0.5f);
//        explosion.position = position;
//        explosion.duration = 1.0f;
//        [self addChild:explosion z:11];
//        [explosion release];
//    }
//    contactListener->slicedFruits.clear();
//    if (knifeCount) {
//        if (knifeBody->GetPosition().y < -.625 || (knifeBody->GetLinearVelocity() == b2Vec2_zero && knifeBody->IsAwake())) [self performSelector:@selector(knifeFell)];
//        knife.rotation += knifeBody->GetLinearVelocity().Length();
//        if (knife.rotation >= 360) knife.rotation = 0;
//            }
}

GameLayer::~GameLayer()
{
    delete world;
    world = NULL;
}
