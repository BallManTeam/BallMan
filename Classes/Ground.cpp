//
//  Ground.cpp
//  BallMan
//
//  Created by Richard Wei on 4/5/14.
//
//

#include "Ground.h"

#include "wip.h"

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#endif
#ifdef _WIN32
#include <GL/gl.h>
#include <GL/glu.h>
#endif

using namespace std;

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

static b2FixtureDef b2FixtureDefMake(const b2PolygonShape *_shape, float32 _density, float32 _friction, float32 _restitution) {
    b2FixtureDef retFixtureDef;
    retFixtureDef.shape = _shape;
    retFixtureDef.density = _density;
    retFixtureDef.friction = _friction;
    retFixtureDef.restitution = _restitution;
    return retFixtureDef;
}

Ground::Ground()
{
    
}

Ground::~Ground()
{
    
}

void Ground::setProperties(CCSize winSize, b2World *world)
{
//    b2BodyDef groundBodyDef;
//    groundBodyDef.position.Set(winSize.width/2, 20.0f);
//    body = world->CreateBody(&groundBodyDef);
//    b2PolygonShape groundBox;
//    groundBox.SetAsBox(winSize.width/2, 15.0f);
//    body->CreateFixture(&groundBox, 0);
////    setAnchorPoint(ccp(0.0, 0.0));
//    setPosition(ccp(winSize.width/2, 20.0f));
//    setContentSize(ccp(winSize.width, 30.0f));
//    body->SetUserData(this);

    shapes = vector<b2PolygonShape>();
    struct shape *sh;
    int shapeCnt = earthen(sh);
    CCLOG("%f", sh[0].vertices[0].x);
    for (int i = 0; i < shapeCnt; i++) {
        b2PolygonShape polyShape = b2PolygonShapeMake(sh[i].vertices, sh[i].vertexCount);
        shapes.push_back(polyShape);
//        polyShape.m_centroid = 
        free(sh[i].vertices); // free mallocated mem
    }
    free(sh); // free mallocated mem
    sh = NULL;
    
    b2BodyDef bodyDef = b2BodyDefMake(b2_staticBody, true, b2Vec2(winSize.width/2, 20.0f), 0);
    body = world->CreateBody(&
 bodyDef);
    for (vector<b2PolygonShape>::iterator i = shapes.begin(); i != shapes.end(); ++i) {
        b2FixtureDef fixDef = b2FixtureDefMake(&*i, 1.0, 0.5, 0.2);
        body->CreateFixture(&fixDef);
    }
    setAnchorPoint(ccp(0.0, 0.0));
    setPosition(ccp(0.0, 0.0));
    setContentSize(ccp(winSize.width, 30.0f));
    body->SetUserData(this);
 
}

void Ground::draw()
{
    float width = this->getContentSize().width;
    float height = this->getContentSize().height;
    CCNode::draw();
    
//    CCPoint vertices[4] = {ccp(0.0f, 0.0f), ccp(0.0f, height), ccp(width, height), ccp(width, 0.0f)};
//    ccDrawSolidPoly(vertices, 4, ccc4f(0.3, 1.0, 0.3, 0.9));
    
    for (vector<b2PolygonShape>::iterator i = shapes.begin(); i != shapes.end(); ++i) {
        ccDrawSolidPoly((CCPoint*)(*i).m_vertices, (*i).m_vertexCount, ccc4f(0.1, 0.9, 0.1, 1.0));
    }
}
