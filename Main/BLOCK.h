#ifndef BLOCK_H
#define BLOCK_H
#pragma once
#include "HGE_LIB.h"

class Block{
public:
// designers & destructors
	Block() : X(0), Y(0) 
	{
		hge = hgeCreate(HGE_VERSION);
	}
	Block(const float &x, const float &y, HTEXTURE &Texture) : X(x), Y(y) 
	{
		hge = hgeCreate(HGE_VERSION);
		sTex = new hgeSprite(Texture, 0, 0, 50, 50);
	}
	Block(const Block *b) 
	{
		X = b->get_X();
		Y = b->get_Y();
		hge = hgeCreate(HGE_VERSION);
		sTex = new hgeSprite(b->Texture, 0, 0, 50, 50);
	}
	~Block() {}
// Getters
	//float get_health() const;
	float get_X() const;
	float get_Y() const ;
// Setters
	//void set_health(const float &h);
	void set_X(const float &x);
	void set_Y(const float &y);
// Update
	//void update();
	void render();
	HTEXTURE		Texture;
	hgeSprite*      sTex;
	static HGE *hge;
private:
	//float health;
	float X;
	float Y;
};

#endif