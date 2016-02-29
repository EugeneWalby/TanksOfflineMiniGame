#ifndef BULLET_H
#define BULLET_H
#pragma once
#include "HGE_LIB.h"

// Класс Пуля
class Bullet
{
	friend class Tank;
public:
// designers & destructors
	friend bool operator!=(const Bullet &b1, const Bullet &b2){
		if( (b1.bullet_speed != b2.bullet_speed) || (b1.damage != b2.damage) || (b1.bulletX != b2.bulletX) ||
			 (b1.bulletY != b2.bulletY) || (b1.bulletdX != b2.bulletdX) || b1.bulletdY != b2.bulletdY)
			 return false;
		else
			return true;
	}
	Bullet() : bullet_speed(5), damage(5), bulletX(0), bulletY(0), bulletdX(0), bulletdY(0) 
	{ 
		hge = hgeCreate(HGE_VERSION); 
		//set_bullet_Texture(); 
		AB = NOTHING_BULLET; 
		//sTex = new hgeSprite(Texture, 0, 0, 50, 50);
	}
	Bullet(const float &b_s, const float &dam, const float &bx, const float &by, HTEXTURE &Texture, State Bullet_state) : bullet_speed(BULLET_SPEED), damage(dam), bulletX(bx), bulletY(by), bulletdX(0), bulletdY(0) 
	{ 
		hge = hgeCreate(HGE_VERSION);
		//set_bullet_Texture();
		AB = NOTHING_BULLET; 
		sTex = new hgeSprite(Texture, 0, 0, 10, 10);
		bullet_state=Bullet_state;
	}
	~Bullet(){}
// Getters
	float get_bullet_speed() const;
	float get_damage() const;
	float get_bulletX() const;
	float get_bulletY() const;
	float get_bulletdX() const;
	float get_bulletdY() const;
	Action_Bullet get_AB()const;
	State get_bullet_state()const;
// Setters
	void set_tank_speed(const float &b_s);
	void set_damage(const float &dam);
	void set_bulletX(const float &x);
	void set_bulletY(const float &y);
	void set_bulletdX(const float &bdx);
	void set_bulletdY(const float &bdy);
	void set_bullet_Texture();
	void set_AB(const Action_Bullet &ab);
// Update
	Action_Bullet update();
	void render();
private:
	static HGE*		hge;
	float bullet_speed;
	float damage;
	float bulletX, bulletdX;
	float bulletY, bulletdY;
	HTEXTURE		bullet_Texture;
	hgeSprite*      sTex;
	State	bullet_state;
	Action_Bullet AB;
};

#endif