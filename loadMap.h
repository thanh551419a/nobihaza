#ifndef __LOADMAP_H__
#define __LOADMAP_H__

#include "cocos2d.h"

class LoadMap: public cocos2d::Node
{
	public:
		static LoadMap* createFromFile(const std::string& filename);
		bool initFromFile(const std::string& filename);
		void reverseRows(std::vector<std::vector<int>>& matrix);
		void update(float dt) override;
		std::vector<std::vector<int>> mapMatrix;
		int sizeMap = 0;
		int playerPosX = 0;
		int playerPosY = 0;
};

#endif // __MAINMENU_SCENE_H__
