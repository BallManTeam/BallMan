//
//  wip.h
//  BallMan
//
//  Created by Richard Wei on 4/5/14.
//
//

#ifndef BallMan_wip_h
#define BallMan_wip_h

#include "Box2D.h"

struct shape
{
    b2Vec2 *vertices;
    int vertexCount;
};

int earthen(struct shape *&shape_pt);

#endif
