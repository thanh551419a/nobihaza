#ifndef __GLOBALVAL_H__
#define __GLOBALVAL_H__	

#include "cocos2d.h"

class globalVal: public cocos2d::Node
{
	private:
		cocos2d::Vec2 playerPos;
		int sizeMap = 0; // size of map
		int tileSize; // size of each tile in pixels
		int diThang = 0;
		int diNgang = 0;
	public:
		static globalVal* getInstance();
		// setters and getters for player position
		void setPlayerPos(const cocos2d::Vec2& pos);
		cocos2d::Vec2 getPlayerPos() const;
		void setPlayerPosX(float x);
		void setPlayerPosY(float y);
		float getPlayerPosX() const;
		float getPlayerPosY() const;
		
		void setSizeMap(int size);
		int getSizeMap() const;
		// setter getters for tile size
		void setTileSize(int size);
		int getTileSize() const;
		int getDiThang() const;
		int getDiNgang() const;
		void setDiThang(int di);
		void setDiNgang(int di);
		void init(); // Initialize the global values
};

#endif // __MAINMENU_SCENE_H__
