#include "PLAYER_TANK.h"

// Getters
	float Player_tank::get_tank_speed() const { return Tank::get_tank_speed(); }
	float Player_tank::get_health() const { return Tank::get_health(); }
	float Player_tank::get_X() const { return Tank::get_X(); }
	float Player_tank::get_Y() const { return Tank::get_Y(); }
	float Player_tank::get_dX() const { return Tank::get_dX(); }
	float Player_tank::get_dY() const { return Tank::get_dY(); }
	State Player_tank::get_state() const { return Tank::get_state(); }
	Action_Tank Player_tank::get_AT()const{ return Tank::get_AT(); }
// Setters
	void Player_tank::set_tank_speed(const float &t_s) { Tank::set_tank_speed(t_s); }
	void Player_tank::set_health(const float &h) { Tank::set_health(h); }
	void Player_tank::set_X(const float &x) { Tank::set_X(x); }
	void Player_tank::set_Y(const float &y) { Tank::set_Y(y); }
	void Player_tank::set_dX(const float &dx) { Tank::set_X(dx); }
	void Player_tank::set_dY(const float &dy) { Tank::set_Y(dy); }
	void Player_tank::set_state(const State &st) { Tank::set_state(st); }
	void Player_tank::set_AT(const Action_Tank &at){ Tank::set_AT(at); }
	void Player_tank::set_Texture(HTEXTURE &Texture)
	{

	}
	void Player_tank::control1(){
		const float friction=0.75f;   // Скольжение
		float dt;

		dt=hge->Timer_GetDelta(); // Узнаем, сколько прошло времени с последнего вызова ф-ции кадра.

		if (hge->Input_GetKeyState(HGEK_W)){
			Tank::set_dY(Tank::get_dY()-Tank::get_tank_speed()*dt);
			Tank::set_state(UP);
		}
		else if (hge->Input_GetKeyState(HGEK_S)){
			Tank::set_dY(Tank::get_dY()+Tank::get_tank_speed()*dt);
			Tank::set_state(DOWN);
		}
		else if (hge->Input_GetKeyState(HGEK_A)){
			Tank::set_dX(Tank::get_dX()-Tank::get_tank_speed()*dt);
			Tank::set_state(LEFT);
		}
		else if (hge->Input_GetKeyState(HGEK_D)){
			Tank::set_dX(Tank::get_dX()+Tank::get_tank_speed()*dt);
			Tank::set_state(RIGHT);
		}

		//if (hge->Input_GetKeyState(HGEK_SPACE)){
		//	//Sleep(1);
		//	Tank::set_AT(EXPLOSE_TANK);
		//}

	}
	void Player_tank::control2(){
		const float friction=0.75f;   // Скольжение
		float dt;

		dt=hge->Timer_GetDelta(); // Узнаем, сколько прошло времени с последнего вызова ф-ции кадра.

		if (hge->Input_GetKeyState(HGEK_UP)){
			Tank::set_dY(Tank::get_dY()-Tank::get_tank_speed()*dt);
			Tank::set_state(UP);
		}
		else if (hge->Input_GetKeyState(HGEK_DOWN)){
			Tank::set_dY(Tank::get_dY()+Tank::get_tank_speed()*dt);
			Tank::set_state(DOWN);
		}
		else if (hge->Input_GetKeyState(HGEK_LEFT)){
			Tank::set_dX(Tank::get_dX()-Tank::get_tank_speed()*dt);
			Tank::set_state(LEFT);
		}
		else if (hge->Input_GetKeyState(HGEK_RIGHT)){
			Tank::set_dX(Tank::get_dX()+Tank::get_tank_speed()*dt);
			Tank::set_state(RIGHT);
		}
	}

// Update
	Action_Tank Player_tank::update(){
		return Tank::update();
	}
	bool Player_tank::fire() 
	{
		return false;
	}
	void Player_tank::render()
	{
		Tank::render();
		/*sTex->Render(get_X(), get_Y());
		assert(get_X() == 0.0f && get_Y() == 0.0f);*/
	}