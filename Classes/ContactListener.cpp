//
//  ContactListener.cpp
//  BallMan
//
//  Created by Richard Wei on 4/4/14.
//
//

#include "ContactListener.h"
#include "GameLayer.h"

using namespace cocos2d;

ContactListener::ContactListener() {}
ContactListener::~ContactListener() {}

void ContactListener::BeginContact(b2Contact *contact)
{
    CCNode *node1 = (CCNode *)contact->GetFixtureA()->GetBody()->GetUserData();
    CCNode *node2 = (CCNode *)contact->GetFixtureB()->GetBody()->GetUserData();
    if (node1 && node1->getTag() == GameLayerTagTank) {
//        tanks.insert(contact->GetFixtureA()->GetBody());
        if (node2 && node2->getTag() == GameLayerTagCannonball) isCannonballContacted = true;
        return;
    }
    if (node2 && node2->getTag() == GameLayerTagTank) {
//        tanks.insert(contact->GetFixtureB()->GetBody());
        if (node1 && node1->getTag() == GameLayerTagCannonball) isCannonballContacted = true;
    }
}

void ContactListener::PreSolve(b2Contact *contact, const b2Manifold *oldManifold)
{
    
}
