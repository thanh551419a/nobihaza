#ifndef __GAMEPAUSE_SCENE_H__
#define __GAMEPAUSE_SCENE_H__

#include "cocos2d.h"
#include<vector>
#include<iostream>
using namespace std;
using namespace cocos2d;
using namespace std;
class GamePause : public cocos2d::Layer
{
    private:
		cocos2d::Sprite* backGroundScene;
        cocos2d::Sprite* boundering;
		int selectedItem = 0;// selected item in menu
		vector <Vec2> menuItem;// positions of menu items
		// key pressed event listener
		void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
public:
    // there is no 'id' in cpp so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // method 'init' in cocos2d-x returns bool, instead od returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(GamePause);

    void Resume(Ref* pSender);
    void GoToMainMenuScene(Ref* pSender);
    void Retry(Ref* pSender);
};

#endif // __MAINMENU_SCENE_H__
