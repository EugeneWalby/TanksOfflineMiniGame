#ifndef HGE_LIB_H
#define HGE_LIB_H
#pragma once

#include <hge.h>
#include <cassert>
#include <hgesprite.h>
#include <hgeanim.h>
#include <hgevector.h>
#include <hgefont.h>
#include <ctime>
#include <list>
#include <algorithm>
#include <string>
#include <cmath>
#include <dos.h>
#include <stdio.h>

using namespace std;

enum State{ UP, DOWN, LEFT, RIGHT };
enum Action_Tank{ EXPLOSE_TANK, SHOT, NOTHING_TANK};
enum Action_Bullet{ EXPLOSE_BULLET, DELETE_BULLET, NOTHING_BULLET};

#define BULLET_SPEED 3
#define TANK_SPEED 50

//HGE *hge = 0;

#endif