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

class Ground : public cocos2d::CCSprite {
public:
    Ground();
    virtual ~Ground();

    CREATE_FUNC(Ground);
    
    virtual void draw();
};

#endif /* defined(__BallMan__Ground__) */
