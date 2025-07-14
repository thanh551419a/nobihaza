#ifndef __LOADMAP_H__
#define __LOADMAP_H__

#include "cocos2d.h"
#include "globalVal.h"
class LoadMap: public cocos2d::Node
{	private:
		std::vector<std::vector<int>> mapMatrix;
		int sizeMap = 0;
		float playerPosX = 0;
		float playerPosY = 0;
		int width = 0;
		int height = 0;
		int tileSize = 0; // Kích thước của mỗi ô trong pixel
		cocos2d::Size frameSize; // Kích thước của khung hiển thị
		cocos2d::Vec2 playerPos; // Vị trí của người chơi
		globalVal* gV = globalVal::getInstance();
	public:
		static LoadMap* createFromFile(const std::string& filename);
		bool initFromFile(const std::string& filename);
		void reverseRows(std::vector<std::vector<int>>& matrix);
		void update(float dt) override;
		

};

#endif // __MAINMENU_SCENE_H__
