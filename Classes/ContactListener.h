//
//  ContactListener.h
//  BallMan
//
//  Created by Richard Wei on 4/4/14.
//
//

#ifndef __BallMan__ContactListener__
#define __BallMan__ContactListener__

#include "cocos2d.h"
#include "Box2D.h"
#include <set>

class ContactListener : public b2ContactListener
{
public:
//    std::set<b2Body*> tanks;
    
    bool isCannonballContacted = false;
    
    ContactListener();
    virtual ~ContactListener();
    
    virtual void BeginContact(b2Contact *contact);
    virtual void PreSolve(b2Contact *contact, const b2Manifold *oldManifold);
};

#endif /* defined(__BallMan__ContactListener__) */
