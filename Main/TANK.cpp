#include "TANK.h"

HGE* Tank::hge = 0;

// Getters
float Tank::get_tank_speed() const { return tank_speed; };
float Tank::get_health() const { return health; }
float Tank::get_X() const { return X; }
float Tank::get_Y() const { return Y; }
float Tank::get_dX() const { return dX; }
float Tank::get_dY() const { return dY; }
State Tank::get_state() const { return state; }
Action_Tank Tank::get_AT()const { return AT; }

// Setters
void Tank::set_tank_speed(const float &t_s) { tank_speed = t_s; }
void Tank::set_health(const float &h) { health = h; }
void Tank::set_X(const float &x) { X = x; }
void Tank::set_Y(const float &y) {Y = y; }
void Tank::set_dX(const float &dx) { dX = dx; }
void Tank::set_dY(const float &dy) { dY = dy; }
void Tank::set_state(const State &st) { state = st; }
void Tank::set_AT(const Action_Tank &at){ AT=at; }

// Update
Action_Tank Tank::update() {
	if(Tank::get_health() <= 0){
		Tank::set_AT(EXPLOSE_TANK);
		return Tank::get_AT();
	}

	if(Tank::get_AT() == EXPLOSE_TANK){
		Tank::set_AT(NOTHING_TANK);
		return EXPLOSE_TANK;
	}

	const float friction=0.75f;   // Скольжение
	float dt;

	dt=hge->Timer_GetDelta(); // Узнаем, сколько прошло времени с последнего вызова ф-ции кадра.


	Tank::set_dY(Tank::get_dY() * friction); 
	Tank::set_dX(Tank::get_dX() * friction);

	Tank::set_X(Tank::get_X()+Tank::get_dX());
	Tank::set_Y(Tank::get_Y()+Tank::get_dY());

	if(Tank::get_Y()>575) {  Tank::set_Y(575); Tank::set_dY(0);  }       // Проверка
	if(Tank::get_Y()<25)  {  Tank::set_Y(25); Tank::set_dY(0);   } 		 // выхода 

	if(Tank::get_X()>775) {  Tank::set_X(775); Tank::set_dX(0); }	// за границу
	if(Tank::get_X()<25)   { Tank::set_X(25); Tank::set_dX(0);   }	// карты

	return Tank::get_AT();

}

bool Tank::fire() 
{
	return false;
}
void Tank::render(){
	//sTex->Render(Tank::get_X()-25, Tank::get_Y()-25);
	if (state == UP){
		sTex->RenderEx(Tank::get_X()+20.0f, Tank::get_Y()-30.0f, 1.57f, 1.2f, 0.8f);
	}else if (state == DOWN){
		sTex->RenderEx(Tank::get_X()-20.0f, Tank::get_Y()+30.0f, -1.57f, 1.2f, 0.8f);
	}else if (state == LEFT){
		sTex->RenderEx(Tank::get_X()-25.0f, Tank::get_Y()-25.0f, 0.0f);	
	}else if (state == RIGHT){
		sTex->RenderEx(Tank::get_X()+25.0f, Tank::get_Y()+25.0f, 3.14f);
	}
}