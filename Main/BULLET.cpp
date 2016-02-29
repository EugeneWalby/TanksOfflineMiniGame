#include "BULLET.h"

HGE* Bullet::hge = 0;

// Getters
	float Bullet::get_bullet_speed() const { return bullet_speed; }
	float Bullet::get_damage() const { return damage; }
	float Bullet::get_bulletX() const { return bulletX; }
	float Bullet::get_bulletY() const { return bulletY; }
	float Bullet::get_bulletdX() const { return bulletdX; }
	float Bullet::get_bulletdY() const { return bulletdY; }
	Action_Bullet Bullet::get_AB()const { return AB; }
	State Bullet::get_bullet_state()const { return bullet_state; }
// Setters
	void Bullet::set_tank_speed(const float &b_s) { bullet_speed = b_s; }
	void Bullet::set_damage(const float &dam) { damage = dam; }
	void Bullet::set_bulletX(const float &bx) { bulletX = bx; }
	void Bullet::set_bulletY(const float &by) { bulletY = by; }
	void Bullet::set_bulletdX(const float &bdx) { bulletdX = bdx; }
	void Bullet::set_bulletdY(const float &bdy) { bulletdY = bdy; }
	void Bullet::set_bullet_Texture(){  }
	void Bullet::set_AB(const Action_Bullet &ab){ AB = ab; }

// Update
	Action_Bullet Bullet::update() {
		if (Bullet::get_bullet_state()==UP){
			Bullet::set_bulletY(Bullet::get_bulletY()-Bullet::get_bullet_speed());
		}else if (Bullet::get_bullet_state()==DOWN){
			Bullet::set_bulletY(Bullet::get_bulletY()+Bullet::get_bullet_speed());
		}else if (Bullet::get_bullet_state()==LEFT){
			Bullet::set_bulletX(Bullet::get_bulletX()-Bullet::get_bullet_speed());
		}else if (Bullet::get_bullet_state()==RIGHT){
			Bullet::set_bulletX(Bullet::get_bulletX()+Bullet::get_bullet_speed());
		}

		return Bullet::get_AB();
	}

	void Bullet::render()
	{
		sTex->Render(Bullet::get_bulletX(), Bullet::get_bulletY());
	}