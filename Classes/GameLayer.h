//
//  GameLayer.h
//  BallMan
//
//  Created by Richard Wei on 4/4/14.
//
//

#ifndef __BallMan__GameScene__
#define __BallMan__GameScene__

#include "cocos2d.h"
#include "Box2D.h"
#include "ContactListener.h"
#include "Tank.h"

//#define DEBUG_DRAW_STATE 1 // 0-Off 1-On

//#if DEBUG_DRAW_STATE && DEBUG
//#define DEBUG_DRAW
//#endif

typedef enum {
    GameLayerTagInvalid = 0,
    GameLayerTagTank,
    GameLayerTagGround,
    GameLayerTagCannonball,
    GameLayerTagLabelRed,
    GameLayerTagLabelGreen
} GameLayerTag;

typedef enum {
    GameTurnPlayerRed,
    GameTurnPlayerGreen,
} GameTurn;

class GameLayer : public cocos2d::CCLayer
{
    
    long scoreRed, scoreGreen;
    
private:
    b2World *world;
#ifdef DEBUG_DRAW
	GLESDebugDraw *m_debugDraw;
    BOOL isDebugDrawEnabled;
#endif
    ContactListener *contactListener;
    
    Tank *tankRed, *tankGreen;
    GameTurn turn;
    
public:
    
    virtual bool init();
    
    static cocos2d::CCScene* scene();
    
    CREATE_FUNC(GameLayer);
    
    virtual ~GameLayer();
    
    virtual void draw();
    
    void reload();
    
    void tick(float dt);
};

#endif /* defined(__BallMan__GameScene__) */
