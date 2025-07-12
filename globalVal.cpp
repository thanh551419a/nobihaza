#include "globalVal.h"
#include "cocos2d.h"
globalVal* globalVal::getInstance() {
	static globalVal instance;
	return &instance;
}
void globalVal::init1() {
		// Initialize player position to a default value
	playerPos = cocos2d::Vec2(0, 0);
	sizeMap = 0; // Default size of the map
	tileSize = 32; // Default tile size in pixels
	diThang = 0; // Default vertical movement step
	diNgang = 0; // Default horizontal movement step
}
void globalVal:: setPlayerPos(const cocos2d::Vec2& pos) {
	playerPos = pos;
}
cocos2d::Vec2 globalVal::getPlayerPos() const {
	return playerPos;
}
void globalVal::setPlayerPosX(float x) {
	playerPos.x = x;
}
void globalVal::setPlayerPosY(float y) {
	playerPos.y = y;
}
float globalVal::getPlayerPosX() const {
	return playerPos.x;
}
float globalVal::getPlayerPosY() const {
	return playerPos.y;
}
void globalVal::setSizeMap(int size) {
	sizeMap = size;
}
int globalVal::getSizeMap() const {
	return sizeMap;
}
void globalVal::setTileSize(int size) {
	tileSize = size;
}
int globalVal::getTileSize() const {
	return tileSize;
}
int globalVal::getDiThang() const {
	return diThang;
}
void globalVal::setDiThang(int di) {
	diThang = di;
}
int globalVal::getDiNgang() const {
	return diNgang;
}
void globalVal::setDiNgang(int di) {
	diNgang = di;
}
// End of globalVal.cpp