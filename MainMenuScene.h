#ifndef __MAINMENU_SCENE_H__
#define __MAINMENU_SCENE_H__

#include "cocos2d.h"

class MainMenu : public cocos2d::Layer
{
private:
    cocos2d::Sprite* backGroundMenu;
	
public:
    // there is no 'id' in cpp so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // method 'init' in cocos2d-x returns bool, instead od returning 'id' in cocos2d-iphone
    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(MainMenu);

    void GoToGameScene(Ref* pSender);
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
};

#endif // __MAINMENU_SCENE_H__
