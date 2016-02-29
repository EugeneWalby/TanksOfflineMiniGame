#ifndef PLAYER_TANK_H
#define PLAYER_TANK_H
#pragma once

#include "TANK.h"
#include "HGE_LIB.h"


// Танк игрока
class Player_tank : public Tank
{
public:
// designers & destructors
	Player_tank() : Tank()
	{ hge = hgeCreate(HGE_VERSION); /*set_Texture();*/}
	Player_tank(const float &t_s, const float &h, const float &x, const float &y, HTEXTURE &Texture) : Tank(TANK_SPEED, h, x, y)
	{
		hge = hgeCreate(HGE_VERSION); /*set_Texture(Texture)*/;
		sTex = new hgeSprite(Texture, 0, 0, 50, 50);
	}
	~Player_tank() {}
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
	void control1();
	void control2();
//Update
	Action_Tank update();
	bool fire();
	virtual void render();

};

#endif