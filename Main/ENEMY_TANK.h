#ifndef ENEMY_TANK_H
#define ENEMY_TANK_H
#pragma once

#include "TANK.h"
#include "HGE_LIB.h"

// Танк врагов
class Enemy_tank : public Tank
{
public:
// designers & destructors
	/*Enemy_tank() : Tank()
	{set_Texture();}*/
	Enemy_tank(const float &t_s, const float &h, const float &x, const float &y, HTEXTURE &Texture) : Tank(TANK_SPEED, h, x, y) 
	{hge = hgeCreate(HGE_VERSION); set_Texture(Texture);}
	~Enemy_tank() {}
// Getters
	float get_tank_speed() const;
	float get_health() const;
	float get_X() const;
	float get_Y() const;
	float get_dX() const;
	float get_dY() const;
	State get_state() const;
	Action_Tank get_AT()const;
// Setters
	void set_tank_speed(const float &t_s);
	void set_health(const float &h);
	void set_X(const float &x);
	void set_Y(const float &y);
	void set_dX(const float &dx);
	void set_dY(const float &dy);
	void set_state(const State &st);
	void set_AT(const Action_Tank &at);
	virtual void set_Texture(HTEXTURE &Texture);
 //Update
	Action_Tank update();
	virtual bool fire();
	virtual void render();
};

#endif