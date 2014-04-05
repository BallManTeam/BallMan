//
//  GameLayer.cpp
//  BallMan
//
//  Created by Richard Wei on 4/4/14.
//
//

#include "GameLayer.h"

#include "Ground.h"
#include <set>
#include <vector>
#include "wip.h"

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
    Ground *ground = Ground::create();
    ground->setProperties(visibleSize, world);
    ground->setTag(GameLayerTagGround);
    this->addChild(ground);
    
//    
//    // Tank body definition
//    b2BodyDef tankBodyDef;
//    tankBodyDef.type = b2_dynamicBody;
//    tankBodyDef.position.Set(100, 100);
//    b2Body *leftTankBody = world->CreateBody(&tankBodyDef);
//    tankBodyDef.position.Set(visibleSize.width-100, 100);
//    b2Body *rightTankBody = world->CreateBody(&tankBodyDef);
//    b2PolygonShape tankShape;
//    tankShape.SetAsBox(32, 32);
//    b2FixtureDef tankFixtureDef;
//    tankFixtureDef.shape = &tankShape;
//    tankFixtureDef.density = 1.0f;
//    tankFixtureDef.friction = 0.3f;
//    tankFixtureDef.restitution = 0.2f;
//    leftTankBody->CreateFixture(&tankFixtureDef);
//    rightTankBody->CreateFixture(&tankFixtureDef);

    // Left and right tank
    Tank *leftTank = (Tank *)CCSprite::create("red_tank.png");
    leftTank->setProperties(b2Vec2(100.0f, 100.0f), world, TankPositionLeft); //create("red_tank.png", b2Vec2(100.0f, 100.0f), world, TankPositionLeft);
    leftTank->setPosition(ccp(100.0f, 100.0f));
    leftTank->setTag(GameLayerTagTank);
    this->addChild(leftTank);
    tankRed = leftTank;
    Tank *rightTank = (Tank *)CCSprite::create("green_tank.png");
    rightTank->setProperties(b2Vec2(visibleSize.width-100.0f, 100.0f), world, TankPositionRight);
    rightTank->setPosition(ccp(visibleSize.width-100.0f, 100.0f));
    rightTank->setTag(GameLayerTagTank);
    this->addChild(rightTank);
    tankGreen = rightTank;
    
    // Cannonball
    b2BodyDef cannonBodyDef = b2BodyDefMake(b2_dynamicBody, false, b2Vec2_zero, 0);
    b2Body *cannonBody = world->CreateBody(&cannonBodyDef);
    b2CircleShape cannonShape = b2CircleShapeMake(4);
    b2FixtureDef cannonFixtureDef = b2FixtureDefMake(&cannonShape, 1.0, 0.2, 0.5);
    cannonBody->CreateFixture(&cannonFixtureDef);
    CCSprite *ball = CCSprite::create("cannon_ball.png");
    ball->setVisible(false);
    this->addChild(ball);
    cannonBody->SetUserData(ball);
    
    // Score label
    CCLabelTTF *labelRed = CCLabelTTF::create("Score 0", "Arial", 20);
    labelRed->setColor(ccc3(0.0, 0.0, 0.0));
    labelRed->setAnchorPoint(ccp(0.0, 1.0));
    labelRed->setPosition(ccp(30, visibleSize.height));
    labelRed->setTag(GameLayerTagLabelRed);
    this->addChild(labelRed);
    
    CCLabelTTF *labelGreen = CCLabelTTF::create("Score 0", "Arial", 20);
    labelGreen->setColor(ccc3(0.0, 0.0, 0.0));
    labelGreen->setAnchorPoint(ccp(1.0, 1.0));
    labelGreen->setPosition(ccp(visibleSize.width-30, visibleSize.height));
    labelGreen->setTag(GameLayerTagLabelGreen);
    this->addChild(labelGreen);
    
    this->schedule(schedule_selector(GameLayer::tick));

    // For testing!!
//    contactListener->isCannonballContacted = true;
    
    // Game starts
    turn = GameTurnPlayerRed;
    
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
//    for (pos = contactListener->tanks.begin();
//         pos != contactListener->tanks.end(); ++pos) {
//        b2Body *body = *pos;
//        CCNode *contactNode = (CCNode *)body->GetUserData();
//        CCPoint position = contactNode->getPosition();
//        
    if (contactListener->isCannonballContacted) {
        contactListener->isCannonballContacted = false;
        Tank *attackingTank = turn==GameTurnPlayerRed?tankGreen:tankRed;
        Tank *attackedTank = turn==GameTurnPlayerGreen?tankGreen:tankRed;
        attackedTank->body->SetAwake(false);
        attackingTank->cannonBody->SetAwake(false);
        attackingTank->cannonball->setVisible(false);
        CCParticleSun *explosion = CCParticleSun::createWithTotalParticles(200);
        explosion->setAutoRemoveOnFinish(true);
        explosion->setStartSize(20.0f);
        explosion->setSpeed(70.0f);
        explosion->setAnchorPoint(ccp(0.5f, 0.5f));
        explosion->setPosition(attackedTank->getPosition());
        explosion->setDuration(1.0f);
        this->addChild(explosion, 11);
        if (turn == GameTurnPlayerRed) {
            CCLabelTTF *scoreLabel = (CCLabelTTF*)this->getChildByTag(GameLayerTagLabelRed);
            scoreRed += 10;
            char str[16];
            sprintf(str, "Score: %ld", scoreRed);
            scoreLabel->setString(str);
        } else if (turn == GameTurnPlayerGreen) {
            scoreGreen += 10;
            CCLabelTTF *scoreLabel = (CCLabelTTF*)this->getChildByTag(GameLayerTagLabelGreen);
            char str[16];
            sprintf(str, "Score: %ld", scoreGreen);
            scoreLabel->setString(str);
        }
//        this->removeChild(tank);
//        CCScene *currentScene = CCDirector::sharedDirector()->getRunningScene();
//        CCScene *newScene = (CCScene *)GameLayer::create();
//        CCDirector::sharedDirector()->replaceScene(newScene);
    }
//    }
//    contactListener->slicedFruits.clear();
//    if (knifeCount) {
//        if (knifeBody->GetPosition().y < -.625 || (knifeBody->GetLinearVelocity() == b2Vec2_zero && knifeBody->IsAwake())) [self performSelector:@selector(knifeFell)];
//        knife.rotation += knifeBody->GetLinearVelocity().Length();
//        if (knife.rotation >= 360) knife.rotation = 0;
//
}

void GameLayer::draw()
{
    CCLayer::draw();
    glClearColor(0.9, 0.9, 0.9, 0.9);
}

void GameLayer::reload()
{
//    if (turn == GameTurnPlayerRed) { //green tank down
//        tankGreen->cannonBody->SetTransform(b2Vec2(36.0f, 42.0f), 0.0f);
//    } else if (turn == GameTurnPlayerGreen) {
//        tankRed->cannonBody->SetTransform(b2Vec2(28.0f, 42.0f), 0.0f);
//    }
    turn = GameTurnPlayerRed;
    tankRed->reload();
    tankGreen->reload();
}

GameLayer::~GameLayer()
{
    delete world;
    world = NULL;
}
