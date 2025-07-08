#ifndef __GAMEOVER_SCENE_H__
#define __GAMEOVER_SCENE_H__

#include "cocos2d.h"

class GameOver : public cocos2d::Layer
{
public:
    // there is no 'id' in cpp so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // method 'init' in cocos2d-x returns bool, instead od returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameOver);

    void GoToGameScene(Ref* pSender);
    void GoToMainMenuScene(Ref* pSender);
};

#endif // __MAINMENU_SCENE_H__
