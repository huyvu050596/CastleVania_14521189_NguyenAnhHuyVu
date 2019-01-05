#ifndef _SWEPT_AABB_H
#define _SWEPT_AABB_H

#include "Global.h"
#include <math.h>
#include <algorithm>
#include <limits>

extern bool AABBCheck(Box b1, Box b2);
extern bool AABB(Box b1, Box b2, float& moveX, float& moveY);
extern Box GetSweptBroadphaseBox(Box b);
extern float SweptAABB(Box b1, Box b2, float& normalx, float& normaly);
extern int Collide(Box &box, Box &block, float &collisiontime, float &x, float &y);
#endif