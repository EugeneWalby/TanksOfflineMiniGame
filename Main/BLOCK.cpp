#include "BLOCK.h"

HGE* Block::hge = 0;

// Getters
	//float get_health() const;
float Block::get_X() const { return X;}
float Block::get_Y() const { return Y;}
// Setters
	//void set_health(const float &h);
void Block::set_X(const float &x) { X=x;}
void Block::set_Y(const float &y) {	Y=y;}
// Update
//void Block::update();
void Block::render(){
	sTex->Render(Block::get_X()-25, Block::get_Y()-25);
}