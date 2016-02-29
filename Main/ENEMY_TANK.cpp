#include "ENEMY_TANK.h"

// Getters
	float Enemy_tank::get_tank_speed() const { return Tank::get_tank_speed(); }
	float Enemy_tank::get_health() const { return Tank::get_health(); }
	float Enemy_tank::get_X() const { return Tank::get_X(); }
	float Enemy_tank::get_Y() const { return Tank::get_Y(); }
	float Enemy_tank::get_dX() const { return Tank::get_dX(); }
	float Enemy_tank::get_dY() const { return Tank::get_dY(); }
	State Enemy_tank::get_state() const { return Tank::get_state(); }
	Action_Tank Enemy_tank::get_AT()const{ return Tank::get_AT(); }
// Setters
	void Enemy_tank::set_tank_speed(const float &t_s) { Tank::set_tank_speed(t_s); }
	void Enemy_tank::set_health(const float &h) { Tank::set_health(h); }
	void Enemy_tank::set_X(const float &x) { Tank::set_X(x); }
	void Enemy_tank::set_Y(const float &y) { Tank::set_Y(y); }
	void Enemy_tank::set_dX(const float &dx) { Tank::set_X(dx); }
	void Enemy_tank::set_dY(const float &dy) { Tank::set_Y(dy); }
	void Enemy_tank::set_state(const State &st) { Tank::set_state(st); }
	void Enemy_tank::set_AT(const Action_Tank &at){ Tank::set_AT(at); }
	void Enemy_tank::set_Texture(HTEXTURE &Texture)
	{ 
		//Texture = hge->Texture_Load(str); 
		sTex = new hgeSprite(Texture, 0, 0, 32, 32);
		sTex->SetHotSpot(3,1.5);
	}
// Update
	Action_Tank Enemy_tank::update(){
		return Tank::update();
	}
	bool Enemy_tank::fire() 
	{
		return true;
	}
	void Enemy_tank::render()
	{
		Tank::render();
	}
