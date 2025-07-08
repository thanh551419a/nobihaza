#include "globalVal.h"
#include "cocos2d.h"
globalVal* globalVal::getInstance() {
	static globalVal instance;
	return &instance;
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
// End of globalVal.cpp