#ifndef TANK_H
#define TANK_H
#pragma once
#include "HGE_LIB.h"


// Абстрактный класс Танк
class Tank
{
public:
// designers & destructors
	Tank() : tank_speed(5), health(5), X(0), Y(0), dX(0), dY(0) 
	{
		hge = hgeCreate(HGE_VERSION);
		set_state(UP);
		AT = NOTHING_TANK;
	}
	Tank(const float &t_s, const float &h, const float &x, const float &y) : tank_speed(t_s), health(h), X(x), Y(y), dX(0), dY(0) 
	{
		hge = hgeCreate(HGE_VERSION);
		set_state(UP);
		AT = NOTHING_TANK;
	}
	~Tank() {}
// Getters
	virtual float get_tank_speed() const;
	virtual float get_health() const;
	virtual float get_X() const;
	virtual float get_Y() const ;
	virtual float get_dX() const;
	virtual float get_dY() const;
	virtual State get_state() const;
	virtual Action_Tank get_AT()const;
// Setters
	virtual void set_tank_speed(const float &t_s);
	virtual void set_health(const float &h);
	virtual void set_X(const float &x);
	virtual void set_Y(const float &y);
	virtual void set_dX(const float &dx);
	virtual void set_dY(const float &dy);
	virtual void set_state(const State &st);
	virtual void set_AT(const Action_Tank &at);
	virtual void set_Texture(HTEXTURE &Texture) = 0;
	virtual void control1() = 0;
	virtual void control2() = 0;
// Update
	virtual Action_Tank update() = 0;
	virtual bool fire() = 0;
	virtual void render();
	//HTEXTURE		Texture;
	hgeSprite*      sTex;
	static HGE *hge;
private:
	float tank_speed;
	float health;
	float X, dX;
	float Y, dY;
    State state;
	Action_Tank AT;
};

#endif